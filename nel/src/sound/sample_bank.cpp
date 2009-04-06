/** \file sample_bank.cpp
 * CSampleBank: a set of sound samples
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#include "stdsound.h"

#include "sample_bank.h"
#include "driver/sound_driver.h"
#include "driver/buffer.h"
#include "nel/misc/path.h"
#include "nel/misc/file.h"
#include "async_file_manager_sound.h"
#include "background_sound_manager.h"
#include "sound_bank.h"


using namespace std;
using namespace NLMISC;


namespace NLSOUND {

/// Constante for the number of file to load asynchronously at a time.
uint32		ASYNC_LOADING_SPLIT = 10;		// 10 file by 10 file

CSampleBank::TSampleBankContainer	CSampleBank::_Banks;
uint	CSampleBank::_LoadedSize = 0;

CSampleBank::TVirtualBankCont		CSampleBank::_VirtualBanks;




void				CSampleBank::init(NLGEORGES::UFormElm *mixerConfig)
{
	if (mixerConfig == 0)
		return;

	NLGEORGES::UFormElm	*virtualBanks;
	mixerConfig->getNodeByName(&virtualBanks, ".VirtualBanks");
	if (virtualBanks == 0)
		return;

	uint size;
	virtualBanks->getArraySize(size);

	for (uint i=0; i<size; ++i)
	{
		NLGEORGES::UFormElm	*virtualBank;
		virtualBanks->getArrayNode(&virtualBank, i);

		if (virtualBank != 0)
		{
			std::vector<TFilteredBank> vfb;
			std::string virtualName;
			virtualBank->getValueByName(virtualName, ".VirtualName");
			NLGEORGES::UFormElm	*realBanks;
			virtualBank->getNodeByName(&realBanks, ".FilteredBank");
			if (realBanks != 0)
			{
				uint size2;
				realBanks->getArraySize(size2);

				for (uint j=0; j<size2; ++j)
				{
					TFilteredBank fb;
					std::string	bankName;
					NLGEORGES::UFormElm	*realBank;
					realBank->getArrayNode(&realBank, j);

					realBank->getValueByName(bankName, ".SampleBank");
					fb.BankName = CStringMapper::map(bankName);
					realBank->getValueByName(fb.Filter, ".Filter");

					vfb.push_back(fb);
				}
			}

			if (!vfb.empty())
			{
				_VirtualBanks.insert(std::make_pair(NLMISC::CStringMapper::map(virtualName), vfb));
				// create the sample bank
				new CSampleBank(virtualName, NULL);
			}
		}
	}
}




// ********************************************************
CSampleBank *CSampleBank::findSampleBank(const NLMISC::TStringId &filename)
{
	TSampleBankContainer::iterator	it(_Banks.find(filename));

	if (it != _Banks.end())
		return it->second;

	return NULL;
}

// ********************************************************

IBuffer*		CSampleBank::get(const NLMISC::TStringId &name)
{
	IBuffer* buffer;
	TSampleBankContainer::iterator iter;

	for (iter = _Banks.begin(); iter != _Banks.end(); ++iter)
	{
		buffer = iter->second->getSample(name);
		if (buffer != 0)
		{
			return buffer;
		}
	}

	//nlwarning ("Try to get an unknown sample '%s'", name);
	return 0;
}

void	 CSampleBank::reload(bool async)
{
	TSampleBankContainer::iterator first(_Banks.begin()), last(_Banks.end());

	for (; first != last; ++first)
	{
		first->second->unload();
		first->second->load(async);
	}
}


void CSampleBank::getLoadedSampleBankInfo(std::vector<std::pair<std::string, uint> > &result)
{
	result.clear();

	TSampleBankContainer::iterator first(_Banks.begin()), last(_Banks.end());
	for (; first != last; ++first)
	{
		std::pair<std::string, uint> p;
		if (first->second->isLoaded())
		{
			p.first = NLMISC::CStringMapper::unmap(first->first);
			p.second = first->second->getSize();
			result.push_back(p);
		}
	}
}





// ********************************************************

CSampleBank::CSampleBank(const std::string& name, ISoundDriver *sd)
: _SoundDriver(sd), _Name(CStringMapper::map(name)), _Loaded(false), _LoadingDone(true), _ByteSize(0)
{
//	_Name = CFile::getFilenameWithoutExtension(_Path);
	_Banks.insert(make_pair(_Name, this));
}


// ********************************************************

CSampleBank::~CSampleBank()
{
	CAudioMixerUser::instance()->unregisterUpdate(this);
	while (!_LoadingDone)
	{
		// need to wait for loading end.
		nlSleep(100);
	}

	if (_Loaded)
		unload();

	// remove the bank from the list of known banks
	TSampleBankContainer::iterator iter(_Banks.begin()), end(_Banks.end());

	for (; iter != end; ++iter)
	{
		if (iter->second == this)
		{
			_Banks.erase(iter);
			break;
		}
	}


	// delete all the samples.
	while (!_Samples.empty())
	{
		delete _Samples.begin()->second;
		_Samples.erase(_Samples.begin());
	}

	_Samples.clear();
}


// ********************************************************

void				CSampleBank::load(bool async)
{
	// TODO : add async loading support !

	TVirtualBankCont::iterator it(_VirtualBanks.find(_Name));
	if (it != _VirtualBanks.end())
	{
		// this is a virtual sample bank !
		nlinfo("Loading virtual sample bank %s", CStringMapper::unmap(_Name).c_str());

		CAudioMixerUser	*mixer = CAudioMixerUser::instance();
		const CAudioMixerUser::TBackgroundFlags &flags = mixer->getBackgroundFlags();

		for (uint i=0; i<it->second.size(); ++i)
		{
			if (flags.Flags[it->second[i].Filter])
			{
				CSampleBank *bank = findSampleBank(it->second[i].BankName);
				if (bank)
					bank->load(async);
			}
		}
	}

	//nlinfo("Loading sample bank %s %", CStringMapper::unmap(_Name).c_str(), async?"":"Asynchronously");

	vector<string> filenames;
//	vector<string>::iterator iter;

	if (_Loaded)
	{
		nlwarning("Trying to load an already loaded bank : %s", CStringMapper::unmap(_Name).c_str ());
		return;
	}


	// Load the sample bank from the builded sample_bank file.
	string bankName(CStringMapper::unmap(_Name)+".sample_bank");
	string filename = CPath::lookup(bankName, false);
	if (filename.empty())
	{
		nlwarning("Could not find sample bank [%s]", bankName.c_str());
		return;
	}

	try
	{

		CIFile	sampleBank(filename);

		CAudioMixerUser::TSampleBankHeader sbh;
		sampleBank.serial(sbh);
		_LoadingDone = false;

		sint32 seekStart = sampleBank.getPos();


		uint8	*data = 0;
		uint	i;
		for (i=0; i<sbh.Name.size(); ++i)
		{
			IBuffer *ibuffer = _SoundDriver->createBuffer();
			nlassert(ibuffer);

			TStringId	nameId = CStringMapper::map(CFile::getFilenameWithoutExtension(sbh.Name[i]));
			ibuffer->setName(nameId);

	/*		{
				sint16 *data16 = new sint16[sbh.NbSample[i]];
				IBuffer::TADPCMState	state;
				state.PreviousSample = 0;
				state.StepIndex = 0;
				uint count =0;
				for (count=0; count+1024<sbh.NbSample[i]; count+=1024)
				{
					IBuffer::decodeADPCM(data+count/2, data16+count, 1024, state);
				}
				IBuffer::decodeADPCM(data+count/2, data16+count, sbh.NbSample[i]-count, state);

				state.PreviousSample = 0;
				state.StepIndex = 0;
				sint16	*data16_2 = new sint16[sbh.NbSample[i]];
 				IBuffer::decodeADPCM(data, data16_2, sbh.NbSample[i], state);

				for (uint j=0; j<sbh.NbSample[i]; ++j)
				{
					if (data16[j] != data16_2[j])
					{
						nlwarning("Sample differ at %u", j);
					}
				}

				_SoundDriver->readRawBuffer(ibuffer, sbh.Name[i], (uint8*)data16, sbh.NbSample[i]*2, Mono16, sbh.Freq[i]);
				delete [] data16;
				delete [] data16_2;
			}
	*/

			if (CAudioMixerUser::instance()->useAPDCM())
			{
				data = (uint8*) realloc(data, sbh.SizeAdpcm[i]);
				sampleBank.seek(seekStart + sbh.OffsetAdpcm[i], CIFile::begin);
				sampleBank.serialBuffer(data, sbh.SizeAdpcm[i]);
				ibuffer->setFormat(IBuffer::FormatDviAdpcm, 1, 16, sbh.Freq[i]);
				if (!ibuffer->fill(data, sbh.SizeAdpcm[i]))
					nlwarning("AM: ibuffer->fill returned false with FormatADPCM");
			}
			else
			{
				data = (uint8*) realloc(data, sbh.SizeMono16[i]);
				sampleBank.seek(seekStart + sbh.OffsetMono16[i], CIFile::begin);
				sampleBank.serialBuffer(data, sbh.SizeMono16[i]);
				ibuffer->setFormat(IBuffer::FormatPcm, 1, 16, sbh.Freq[i]);
				if (!ibuffer->fill(data, sbh.SizeMono16[i]))
					nlwarning("AM: ibuffer->fill returned false with FormatPCM");
			}

			_ByteSize += ibuffer->getSize();

			_Samples[nameId] = ibuffer;

			// Warn the sound bank that the sample are available.
			CSoundBank::instance()->bufferLoaded(nameId, ibuffer);
		}
		free(data);

		_LoadedSize += _ByteSize;
	}
	catch(Exception &e)
	{
		// loading failed !
		nlwarning("Exception %s during loading of sample bank %s", e.what(), filename.c_str());
		CAudioMixerUser	*mixer = CAudioMixerUser::instance();

		if (mixer->getPackedSheetUpdate())
		{
			nlinfo("Deleting offending sound bank, you need to restart to recreate it!");
			CFile::deleteFile(filename);
		}
	}

	_Loaded = true;
	_LoadingDone = true;



///////////////////////////////////////// OLD Version //////////////////////////////////////
/*

	std::string list = CPath::lookup(CStringMapper::unmap(_Name)+CAudioMixerUser::SampleBankListExt, false);
	if (list.empty())
	{
		nlwarning("File %s not found to load sample bank %s", (CStringMapper::unmap(_Name)+CAudioMixerUser::SampleBankListExt).c_str(), CStringMapper::unmap(_Name).c_str());
		return;
	}


	NLMISC::CIFile sampleBankList(list);
	sampleBankList.serialCont(filenames);

	for (iter = filenames.begin(); iter != filenames.end(); iter++)
	{
		IBuffer* ibuffer = NULL;
		try
		{
			ibuffer = _SoundDriver->createBuffer();
			nlassert(ibuffer);

//			std::string sampleName(CFile::getFilenameWithoutExtension(*iter));
			NLMISC::TStringId sampleName(CStringMapper::map(CFile::getFilenameWithoutExtension(*iter)));

			if (async)
			{
				ibuffer->presetName(sampleName);
				nldebug("Preloading sample [%s]", CStringMapper::unmap(sampleName).c_str());
			}
			else
			{
				std::string fullName = NLMISC::CPath::lookup(*iter, false);
				if (!fullName.empty())
				{
					NLMISC::CIFile	ifile(fullName);
					uint size = ifile.getFileSize();
					uint8 *buffer = new uint8[ifile.getFileSize()];
					ifile.serialBuffer(buffer, size);

					_SoundDriver->readWavBuffer(ibuffer, fullName, buffer, size);
					_ByteSize += ibuffer->getSize();

					delete [] buffer;
				}
			}
			_Samples[sampleName] = ibuffer ;

			// Warn the sound bank that the sample are available.
			CSoundBank::instance()->bufferLoaded(sampleName, ibuffer);
		}
		catch (ESoundDriver &e)
		{
			if (ibuffer != NULL) {
				delete ibuffer;
				ibuffer = NULL;
			}
			nlwarning("Problem with file '%s': %s", (*iter).c_str(), e.what());
		}
	}

	_Loaded = true;

	if (!async)
	{
		_LoadingDone = true;
		// compute the sample bank size.
		_LoadedSize += _ByteSize;
	}
	else
	{
		// fill the loading list.
		TSampleTable::iterator first(_Samples.begin()), last(_Samples.end());
		for (; first != last; ++first)
		{
			_LoadList.push_back(make_pair(first->second, first->first));
		}
		_SplitLoadDone = false;
		// send the first files
		for (uint i=0; i<ASYNC_LOADING_SPLIT && !_LoadList.empty(); ++i)
		{
			CAsyncFileManagerSound::getInstance().loadWavFile(_LoadList.front().first, CStringMapper::unmap(_LoadList.front().second)+".wav");
			_LoadList.pop_front();
		}
		// add a end loading event...
		CAsyncFileManagerSound::getInstance().signal(&_SplitLoadDone);
		// and register for update on the mixer
		CAudioMixerUser::instance()->registerUpdate(this);
	}
	*/
}

void CSampleBank::onUpdate()
{
	if (_SplitLoadDone)
	{
		nldebug("Some samples have been loaded");
		if (_LoadList.empty())
		{
			// all the samples are loaded, we can compute the bank size.
			TSampleTable::iterator	first(_Samples.begin()), last(_Samples.end());
			for (; first != last; ++first)
			{
				_ByteSize += first->second->getSize();
			}

			_LoadedSize += _ByteSize;

			// stop the update.
			CAudioMixerUser::instance()->unregisterUpdate(this);
			_LoadingDone = true;

			// Force an update in the background manager (can restar stoped sound).
			CAudioMixerUser::instance()->getBackgroundSoundManager()->updateBackgroundStatus();

			nlinfo("Sample bank %s loaded.", CStringMapper::unmap(_Name).c_str());
		}
		else
		{
			_SplitLoadDone = false;
			for (uint i=0; i<ASYNC_LOADING_SPLIT && !_LoadList.empty(); ++i)
			{
				CAsyncFileManagerSound::getInstance().loadWavFile(_LoadList.front().first, CStringMapper::unmap(_LoadList.front().second)+".wav");
				_LoadList.pop_front();
			}
			// add a end loading event...
			CAsyncFileManagerSound::getInstance().signal(&_SplitLoadDone);
		}
	}
}

// ********************************************************

bool				CSampleBank::unload()
{
	vector<IBuffer*> vec;
	TSampleTable::iterator it;

	if (!_Loaded)
	{
		nlwarning("Trying to unload an already unloaded bank : %s", CStringMapper::unmap(_Name).c_str ());
		return  true;
	}

	// need to wait end of load ?
	if (!_LoadingDone)
		return false;

	//nlinfo("Unloading sample bank %s", CStringMapper::unmap(_Name).c_str());

	for (it = _Samples.begin(); it != _Samples.end(); ++it)
	{
		IBuffer *buffer = it->second;
		if (buffer)
		{
			const NLMISC::TStringId & bufferName = buffer->getName();

			// Warn the mixer to stop any track playing this buffer.
			CAudioMixerUser::instance()->bufferUnloaded(buffer);
			// Warn the sound banks abount this buffer.
			CSoundBank::instance()->bufferUnloaded(bufferName);

			// delete
			it->second = NULL;
			delete buffer;
		}
	}

	_Loaded = false;

	_LoadedSize -= _ByteSize;
	_ByteSize = 0;

	return true;
}

// ********************************************************

bool				CSampleBank::isLoaded()
{
	return _Loaded;
}

// ********************************************************

IBuffer*			CSampleBank::getSample(const NLMISC::TStringId &name)
{
	{
/*		// dump the sample list.
		TSampleTable::iterator it (_Samples.begin()), last(_Samples.end());
		std::string s;

//		while (first != last)
		for (it = _Samples.begin(); it != _Samples.end(); ++it)
		{
			s += std::string(" [")+it->first+"] ";
			//first++;
		}

		nldebug("getSample(%s) : sample list = [%s]", name, s.c_str());
*/
	}

	// Find sound
	TSampleTable::iterator iter = _Samples.find(name);
	if ( iter == _Samples.end() )
	{
		return 0;
	}
	else
	{
		return (*iter).second;
	}
}

// ********************************************************

uint				CSampleBank::countSamples()
{
	return _Samples.size();
}

// ********************************************************

uint				CSampleBank::getSize()
{
	uint size = 0;

	TSampleTable::const_iterator iter;
	for (iter = _Samples.begin(); iter != _Samples.end(); iter++)
	{
		size +=	(*iter).second->getSize();
	}

	return size;
}

void				CSampleBank::releaseAll()
{
	//nldebug( "SampleBanks: Releasing..." );

	while (!_Banks.empty())
	{
		delete _Banks.begin()->second;
	}
	//nldebug( "SampleBanks: Released" );
}



} // namespace NLSOUND

