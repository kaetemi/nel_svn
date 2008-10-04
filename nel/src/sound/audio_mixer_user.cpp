/** \file audio_mixer_user.cpp
 * CAudioMixerUser: implementation of UAudioMixer
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

#include <iomanip>

#include "nel/misc/hierarchical_timer.h"
#include "nel/misc/progress_callback.h"
#include "nel/misc/big_file.h"
#include "nel/misc/time_nl.h"
#include "nel/misc/command.h"
#include "nel/misc/file.h"
#include "nel/misc/path.h"

#include "nel/georges/u_form_loader.h"
#include "nel/georges/u_form_elm.h"
#include "nel/georges/load_form.h"
#include "nel/georges/u_form.h"

#include "nel/3d/scene_user.h"
#include "driver/sound_driver.h"
#include "driver/buffer.h"
#include "driver/effect.h"

#include "background_sound_manager.h"
#include "background_sound_manager.h"
#include "music_sound_manager.h"
#include "background_source.h"
#include "clustered_sound.h"
#include "complex_source.h"
#include "simple_source.h"
#include "complex_sound.h"
#include "context_sound.h"
#include "music_source.h"
#include "simple_sound.h"
#include "music_sound.h"
#include "sample_bank.h"
#include "sound_bank.h"

using namespace std;
using namespace NLMISC;

namespace NLSOUND {

#define NL_TRACE_MIXER 0

#if NL_TRACE_MIXER
#define _profile(_a) nldebug ## _a
#else
#define _profile(_a)
#endif

// Return the priority cstring (debug info)
const char *PriToCStr [NbSoundPriorities] = { "XH", "HI", "MD", "LO" };


// ******************************************************************

const char *getPriorityStr( TSoundPriority p )
{
	nlassert( ((uint)p) < NbSoundPriorities );
	return PriToCStr[p];
}


// ******************************************************************

UAudioMixer	*UAudioMixer::createAudioMixer()
{
	return new CAudioMixerUser();
}


// ******************************************************************

CAudioMixerUser::CAudioMixerUser() : _AutoLoadSample(false),
									 _UseADPCM(true),
									 _SoundDriver(NULL), 
									 _BackgroundSoundManager(NULL),
									 _ClusteredSound(0),
									 _ReverbEffect(NULL), 
									 _ListenPosition(CVector::Null),
									 _BackgroundMusicManager(NULL),
									 _PlayingSources(0),
									 _PlayingSourcesMuted(0),
									 _Leaving(false)
{
#if NL_PROFILE_MIXER
		_UpdateTime = 0.0;
		_CreateTime = 0.0;
		_UpdateCount = 0;
		_CreateCount = 0;
#endif

	// init the filter names and short names
	for (uint i=0; i<TBackgroundFlags::NB_BACKGROUND_FLAGS; ++i)
	{
		char tmp[1024];
		sprintf(tmp, "Filter%2u", i);
		_BackgroundFilterNames[i] = tmp;
		sprintf(tmp, "%u", i);
		_BackgroundFilterShortNames[i] = tmp;
	}
}


// ******************************************************************

CAudioMixerUser::~CAudioMixerUser()
{
	//nldebug( "AM: Releasing..." );

	delete _ClusteredSound; _ClusteredSound = NULL;
	delete _BackgroundSoundManager; _BackgroundSoundManager = NULL;
	delete _BackgroundMusicManager; _BackgroundMusicManager = NULL;

	reset();

	_Leaving = true;

	// Release the sound bank
	CSoundBank::release();
	// Release all the SampleBanks
	CSampleBank::releaseAll();

	// Release music channels
	for (uint i = 0; i < _NbMusicChannelFaders; ++i)
		_MusicChannelFaders[i].release();

	// Detete tracks
	for (uint i = 0; i < _Tracks.size(); ++i)
	{
		delete _Tracks[i];
		_Tracks[i] = NULL;
	}

	// Reverb effect
	delete _ReverbEffect; _ReverbEffect = NULL;

	// Sound driver
	delete _SoundDriver; _SoundDriver = NULL;

	//nldebug( "AM: Released" );
}


void CAudioMixerUser::initClusteredSound(NL3D::UScene *uscene, float minGain, float maxDistance, float portalInterpolate)
{
	NL3D::CScene *scene = 0;
	if (uscene) scene = &(static_cast<NL3D::CSceneUser*>(uscene)->getScene());
	
	initClusteredSound(scene, minGain, maxDistance, portalInterpolate);
}

void CAudioMixerUser::initClusteredSound(NL3D::CScene *scene, float minGain, float maxDistance, float portalInterpolate = 20.0f)
{
	if (!_ClusteredSound) _ClusteredSound = new CClusteredSound();
	
	_ClusteredSound->init(scene, portalInterpolate, maxDistance, minGain);
}


void CAudioMixerUser::setPriorityReserve(TSoundPriority priorityChannel, uint reserve)
{
	_PriorityReserve[priorityChannel] = min(_Tracks.size(), reserve);
}

void CAudioMixerUser::setLowWaterMark(uint value)
{
	_LowWaterMark = min(_Tracks.size(), value);
}


// ******************************************************************


void CAudioMixerUser::writeProfile(std::string& out)
{
	// compute number of muted source
	uint nb = 0;

/*	TSourceContainer::iterator first(_Sources.begin()), last(_Sources.end());
	for (; first != last; ++first)
	{
		CSimpleSource *psu = *first;
		if (psu->getTrack() == NULL)
		{
			++nb;
		}
	}
*/
/*	hash_set<CSimpleSource*>::const_iterator ips;
	for ( ips=_Sources.begin(); ips!=_Sources.end(); ++ips )
	{
		CSimpleSource *psu = *ips;
		if (psu->getTrack() == NULL)
		{
			++nb;
		}
	}
*/
	out += "Sound mixer: \n";
	out += "\tPlaying sources: " + toString (getPlayingSourcesCount()) + " \n";
	out += "\tAvailable tracks: " + toString (getAvailableTracksCount()) + " \n";
	out += "\tUsed tracks: " + toString (getUsedTracksCount()) + " \n";
//	out << "\tMuted sources: " << nb << " \n";
//	out << "\tMuted sources: " << max(0, sint(_PlayingSources.size())-sint(_NbTracks)) << " \n";
//	out << "\tMuted sources: " << max(0, sint(_PlayingSources)-sint(_NbTracks)) << " \n";
	out += "\tMuted sources: " + toString ((int)_PlayingSourcesMuted) + "\n";
	out += "\tSources waiting for play: " + toString (_SourceWaitingForPlay.size()) + " \n";
	out += "\tHighestPri: " + toString ((int)_ReserveUsage[HighestPri]) + " / " + toString ((int)_PriorityReserve[HighestPri]) + " \n";
	out += "\tHighPri:    " + toString ((int)_ReserveUsage[HighPri]) + " / " + toString ((int)_PriorityReserve[HighPri]) + "\n";
	out += "\tMidPri:     " + toString ((int)_ReserveUsage[MidPri]) + " / " + toString ((int)_PriorityReserve[MidPri]) + " \n";
	out += "\tLowPri:     " + toString ((int)_ReserveUsage[LowPri]) + " / " + toString ((int)_PriorityReserve[LowPri]) + " \n";
	out += "\tFreeTracks: " + toString (_FreeTracks.size()) + " / " + toString (_Tracks.size()) + " \n";
	out += "\tAverage update time: " + toString (1000.0 * _UpdateTime / iavoid0(_UpdateCount)) + " msec\n";
	out += "\tAverage create time: " + toString (1000.0 * _CreateTime / iavoid0(_CreateCount)) + " msec\n";
	out += "\tEstimated CPU: " + toString ((100.0 * 1000.0 * (_UpdateTime + _CreateTime) / curTime())) + "%%\n";

	if (_SoundDriver)
	{
		out += toString ("Sound driver: \n");
		_SoundDriver->writeProfile(out);
	}
}

// ******************************************************************

void CAudioMixerUser::addSourceWaitingForPlay(CSimpleSource *source)
{
	_SourceWaitingForPlay.push_back(source);
}


// ******************************************************************

void CAudioMixerUser::reset()
{
	_Leaving = true;

	_SourceWaitingForPlay.clear();

	/* TODO: Stop music channels */

	// Stop tracks
	uint i;
	for (i = 0; i < _Tracks.size(); ++i)
	{
		if (_Tracks[i])
		{
			CSimpleSource* src = _Tracks[i]->getSource();

			if (src && src->isPlaying())
			{
				src->stop();
			}
		}
	}

	// Do a first multipass travesal to stop all playing source
	// We can't do the work in 1 pass because stoping a source can lead to
	// destruction of sub source, invalidating the iterators !
	bool again;
	do
	{
		again = false;
		TSourceContainer::iterator first(_Sources.begin()), last(_Sources.end());
		for (; first != last; ++first)
		{
			if ((*first)->isPlaying())
			{
				(*first)->stop();
				again = true;
				break;
			}
		}

	} while (again);

	// Sources
	while (!_Sources.empty())
	{
		//removeSource( _Sources.begin(), true ); // 3D sources, the envsounds were removed above
		CSourceCommon *source = *(_Sources.begin());
		if (source->isPlaying())
			source->stop();
		else
			delete source;
	}

	_Leaving = false;
}

void CAudioMixerUser::setPackedSheetOption(const std::string &path, bool update)
{
	_PackedSheetPath = CPath::standardizePath(path, true);
	_UpdatePackedSheet = update;
}


void CAudioMixerUser::setSamplePath(const std::string& path)
{
	_SamplePath = CPath::standardizePath(path, true);
}


// ******************************************************************

void CAudioMixerUser::init(uint maxTrack, bool useEax, bool useADPCM, IProgressCallback *progressCallBack, bool autoLoadSample, TDriver driverType, bool forceSoftwareBuffer, bool manualRolloff)
{
	nldebug( "AM: Init..." );

	_profile(( "AM: ---------------------------------------------------------------" ));

	_UseEax = useEax;
	_UseADPCM = useADPCM;
	_AutoLoadSample = autoLoadSample;

	// Init sound driver
	try
	{
		// create the wanted driver
		nlctassert(NumDrivers == UAudioMixer::TDriver(ISoundDriver::NumDrivers));
		_SoundDriver = ISoundDriver::createDriver(this, (ISoundDriver::TDriver)driverType);
		if(_SoundDriver)
		{
			_profile(( "AM: DRIVER: %s", _SoundDriver->getDllName().c_str() ));
			
			// the device to use, default for now
			string driverDevice = "";
			
			// the options to init the driver
			uint driverOptions = 0;
			if (_UseEax) driverOptions |= ISoundDriver::OptionEnvironmentEffects;
			if (_UseADPCM) driverOptions |= ISoundDriver::OptionAllowADPCM;
			if (forceSoftwareBuffer) driverOptions |= ISoundDriver::OptionSoftwareBuffer;
			if (manualRolloff) driverOptions |= ISoundDriver::OptionManualRolloff;
			if (_AutoLoadSample) driverOptions |= ISoundDriver::OptionLocalBufferCopy;
			
			// init the driver with selected device and needed options
			_SoundDriver->init(driverDevice, (ISoundDriver::TSoundOptions)driverOptions);
			
			// verify the options
			if (_UseEax && !_SoundDriver->getOption(ISoundDriver::OptionEnvironmentEffects))
			{
				nlwarning("AM: OptionEnvironmentEffects not available, _UseEax = false");
				_UseEax = false;
			}
			if (_UseADPCM && !_SoundDriver->getOption(ISoundDriver::OptionAllowADPCM))
			{
				nlwarning("AM: OptionAllowADPCM not available, _UseADPCM = false");
				_UseADPCM = false;
			}
			if (_AutoLoadSample && !_SoundDriver->getOption(ISoundDriver::OptionLocalBufferCopy))
			{
				nlwarning("AM: OptionLocalBufferCopy not available, _AutoLoadSample = false");
				_AutoLoadSample = false;
			}
			if (forceSoftwareBuffer && !_SoundDriver->getOption(ISoundDriver::OptionSoftwareBuffer))
			{
				nlwarning("AM: OptionSoftwareBuffer not available, forceSoftwareBuffer = false");
				forceSoftwareBuffer = false; // not really needed, but set anyway in case this is still used later in this function
			}
			if (manualRolloff && !_SoundDriver->getOption(ISoundDriver::OptionLocalBufferCopy))
			{
				nlwarning("AM: OptionManualRolloff not available, manualRolloff = false");
				manualRolloff = false; // not really needed, but set anyway in case this is still used later in this function
			}
		}
	}
	catch (ESoundDriver &e)
	{
		nlwarning(e.what());
		delete _SoundDriver; _SoundDriver = NULL;
		// TODO : is this logic to auto destruct this object in case of failing to create the driver ? no it isn't
		delete this;
		throw;
	}
	catch (...)
	{
		delete _SoundDriver; _SoundDriver = NULL;
		// TODO : is this logic to auto destruct this object in case of failing to create the driver ? NO, IT ISN'T, really.
		delete this;
		throw;
	}

	uint i;
		
	// Init registrable classes
	static bool initialized = false;
	if (!initialized)
	{
		initialized = true;
	}

	// Init listener
	_Listener.init(_SoundDriver);

	if (_UseEax)
	{
		if (!(_ReverbEffect = static_cast<IReverbEffect *>(_SoundDriver->createEffect(IEffect::Reverb))))
			{ _UseEax = false; }
		else { nldebug("AM: Reverb OK"); }
	}

	// Init tracks (physical sources)
	changeMaxTrack(maxTrack);

	// Init the reserve stuff.
	_LowWaterMark = 0;
	for (i=0; i<NbSoundPriorities; ++i)
	{
		_PriorityReserve[i] = _Tracks.size();
		_ReserveUsage[i] = 0;
	}

	_StartTime = CTime::getLocalTime();

	// if needed (update == true), build the sample bank list
	if (_UpdatePackedSheet)
	{
		buildSampleBankList();
	}
	

	// Init music channels
	for (i = 0; i < _NbMusicChannelFaders; ++i)
		_MusicChannelFaders[i].init(_SoundDriver);


	// Create the background sound manager.
	_BackgroundSoundManager = new CBackgroundSoundManager();


	// Create the background music manager
	_BackgroundMusicManager = new CMusicSoundManager();


	// Load the sound bank singleton
	CSoundBank::instance()->load();
	nlinfo("AM: Initialized audio mixer with %u voices, %s and %s.",
		(uint32)_Tracks.size(),
		_UseEax ? "with EAX support" : "WITHOUT EAX",
		_UseADPCM ? "with ADPCM sample source" : "with 16 bits PCM sample source");

	// try to load default configuration from george sheet

	NLGEORGES::UFormLoader *formLoader = NULL;

	try
	{
		std::string mixerConfigFile = NLMISC::CPath::lookup("default.mixer_config", false);
		if (!mixerConfigFile.empty())
		{
			formLoader = NLGEORGES::UFormLoader::createLoader();

			NLMISC::CSmartPtr<NLGEORGES::UForm> form;
			form = formLoader->loadForm(mixerConfigFile.c_str());

			NLGEORGES::UFormElm &root = form->getRootNode();


			// read track reserve
			uint32 highestRes, highRes, midRes, lowRes;
			root.getValueByName(highestRes, ".HighestPriorityReserve");
			root.getValueByName(highRes, ".HighPriorityReserve");
			root.getValueByName(midRes, ".MidPriorityReserve");
			root.getValueByName(lowRes, ".LowPriorityReserve");

			setPriorityReserve(HighestPri, highestRes);
			setPriorityReserve(HighPri, highRes);
			setPriorityReserve(MidPri, midRes);
			setPriorityReserve(LowPri, lowRes);

			uint32 lowWater;
			root.getValueByName(lowWater, ".LowWaterMark");
			setLowWaterMark(lowWater);

			// preload sample bank
			NLGEORGES::UFormElm *sampleBanks;
			root.getNodeByName(&sampleBanks, ".SampleBanks");

			if (sampleBanks != NULL)
			{
				uint size;
				sampleBanks->getArraySize(size);
				for (uint i=0; i<size; ++i)
				{
					std::string name;
					sampleBanks->getArrayValue(name, i);

					if (!name.empty())
						loadSampleBank(false, name);

					if (progressCallBack != 0)
						progressCallBack->progress(float(i) / size);
				}
			}

			// configure background flags names, fades and state
			NLGEORGES::UFormElm *bgFlags;
			root.getNodeByName(&bgFlags, ".BackgroundFlags");
			if (bgFlags != NULL)
			{
				TBackgroundFlags		flags;
				TBackgroundFilterFades	fades;

				uint size;
				bgFlags->getArraySize(size);
				uint i;
				for (i=0; i<min(size, (uint)(TBackgroundFlags::NB_BACKGROUND_FLAGS)); ++i)
				{
					NLGEORGES::UFormElm *flag;
					bgFlags->getArrayNode(&flag, i);

					flag->getValueByName(flags.Flags[i], ".InitialState");

					uint32 fadeIn, fadeOut;
					flag->getValueByName(fadeIn, ".FadeIn");
					flag->getValueByName(fadeOut, ".FadeOut");

					fades.FadeIns[i] = fadeIn;
					fades.FadeOuts[i] = fadeOut;

					flag->getValueByName(_BackgroundFilterNames[i], ".Name");
					flag->getValueByName(_BackgroundFilterShortNames[i], ".ShortName");
				}
				for (; i< TBackgroundFlags::NB_BACKGROUND_FLAGS; ++i)
				{
					uint32 fadeIn, fadeOut;
					NLGEORGES::UFormElm::TWhereIsValue where = NLGEORGES::UFormElm::ValueDefaultDfn;
					root.getValueByName(fadeIn, ".BackgroundFlags[0].FadeIn", NLGEORGES::UFormElm::Eval, &where);
					root.getValueByName(fadeOut, ".BackgroundFlags[0].FadeOut", NLGEORGES::UFormElm::Eval, &where);
					root.getValueByName(flags.Flags[i], ".BackgroundFlags[0].InitialState", NLGEORGES::UFormElm::Eval, &where);

					fades.FadeIns[i] = fadeIn;
					fades.FadeOuts[i] = fadeOut;
				}
				setBackgroundFilterFades(fades);
				setBackgroundFlags(flags);
			}

			NLGEORGES::UFormLoader::releaseLoader(formLoader);
		}
	}
	catch(...)
	{
		NLGEORGES::UFormLoader::releaseLoader(formLoader);
	}

	// init the user var bindings
	initUserVar();
}

void CAudioMixerUser::buildSampleBankList()
{
	uint i;
	// regenerate the sample banks list
	const std::string &sp = _SamplePath;

	// build the list of available sample bank directory
	vector<string>	bankDir;
	CPath::getPathContent(sp, false, true, false, bankDir);
	sort(bankDir.begin(), bankDir.end());
	for (i = 0; i < bankDir.size(); ++i)
	{
		if (bankDir[i].empty())
		{
			bankDir.erase(bankDir.begin()+i);
			--i;
		}
	}
	for (i = 0; i < bankDir.size(); ++i)
	{
		nldebug("Found sample bank dir [%s]", bankDir[i].c_str());
	}

	// build the list of available sample bank file
	vector<string>	bankFile;
	CPath::getPathContent(sp, false, false, true, bankFile);
	// filter out any non sample bank file
	for (i = 0; i < bankDir.size(); ++i)
	{
		if (bankFile[i].find(".sample_bank") != bankFile[i].size() - 12)
		{
			bankFile.erase(bankFile.begin()+i);
			--i;
		}
	}
	sort(bankFile.begin(), bankFile.end());
	for (i = 0; i < bankDir.size(); ++i)
	{
		nldebug("Found sample bank file [%s]", bankFile[i].c_str());
	}

	// now, do a one to one comparison on bank file and sample file date
	for (i = 0; i < bankDir.size(); ++i)
	{
		string	bankname = bankDir[i];
		if (bankname[bankname.size()-1] == '/')
			bankname = bankname.substr(0, bankname.size()-1);

		bankname = bankname.substr(bankname.rfind('/')+1);

		if (i >= bankFile.size() || CFile::getFilenameWithoutExtension(bankFile[i]) > bankname)
		{
			nlinfo("Compiling sample bank [%s]", bankname.c_str());
			// need to create a new bank file !
			TSampleBankHeader	hdr;

			vector<string>	sampleList;
			CPath::getPathContent(bankDir[i], false, false, true, sampleList);
			// remove any non wav file
			uint j;
			for (j=0; j<sampleList.size(); ++j)
			{
				if (sampleList[j].find(".wav") != sampleList[j].size()-4)
				{
					sampleList.erase(sampleList.begin()+j);
					--j;
				}
			}
			sort(sampleList.begin(), sampleList.end());

			vector<vector<uint8> >	adpcmBuffers(sampleList.size());
			vector<vector<sint16> >	mono16Buffers(sampleList.size());

			for (j=0; j<sampleList.size(); ++j)
			{
				nldebug("  Adding sample [%s] into bank", CFile::getFilename(sampleList[j]).c_str());
				CIFile sample (sampleList[j]);
				uint8 *data = new uint8[sample.getFileSize()];
				sample.serialBuffer(data, sample.getFileSize());
				IBuffer *buffer = _SoundDriver->createBuffer();
				buffer->presetName(CStringMapper::map(CFile::getFilenameWithoutExtension(sampleList[j])));
				_SoundDriver->readWavBuffer(buffer, CFile::getFilenameWithoutExtension(sampleList[j]), data, sample.getFileSize());
				vector<uint8>	adpcmData;
				uint32 nbSample = buffer->getBufferADPCMEncoded(adpcmData);
				vector<sint16>	mono16Data;
				buffer->getBufferMono16(mono16Data);
				// Sample number MUST be even
				nlassert(nbSample == (nbSample & 0xfffffffe));
				nlassert(adpcmData.size() == nbSample/2);
				adpcmBuffers[j].swap(adpcmData);
				mono16Buffers[j].swap(mono16Data);

				TSampleFormat sf;
				uint		freq;
				buffer->getFormat(sf, freq);

//			hdrAdpcm.addSample(CFile::getFilename(sampleList[j]), freq, nbSample, );
				hdr.addSample(CFile::getFilename(sampleList[j]), freq, nbSample, mono16Buffers[j].size()*2, adpcmBuffers[j].size());
				delete [] data;
			}

			// write the sample bank (if any sample available)
			if (!hdr.Name.empty())
			{
				string filename = sp+bankname+".sample_bank";
				COFile sbf(filename);
				sbf.serial(hdr);
//				nldebug("Header seeking = %i", sbf.getPos());
				nlassert(mono16Buffers.size() == adpcmBuffers.size());
				for (j=0; j<mono16Buffers.size(); ++j)
				{
					sbf.serialBuffer((uint8*)(&mono16Buffers[j][0]), mono16Buffers[j].size()*2);
					sbf.serialBuffer((uint8*)(&adpcmBuffers[j][0]), adpcmBuffers[j].size());
//					sbf.serialCont(mono16Buffers[j]);
//					sbf.serialCont(adpcmBuffers[j]);
				}
				// NB : the next commented line replaced by the next two line.
				//		The first generate an access violation at the 64th insert !
				// bankFile.insert(bankFile.begin()+i, filename);
				// NB REPLY : the next commented line, which was actually the line
				//            that replaced the line above this note, crashed too !
				//            (don't ask me why this happens, but this seems to fix it)
				// bankFile.insert(bankFile.begin()+i, NULL);
				if (bankFile.size() < i + 1) bankFile.resize(i + 1);
				else bankFile.insert(bankFile.begin() + i, NULL);
				bankFile[i] = filename;
			}
		}
		else if (bankname < CFile::getFilenameWithoutExtension(bankDir[i]))
		{
			nlinfo("Removing sample bank file [%s]", bankname.c_str());
			// remove an out of date bank file
			CFile::deleteFile(bankFile[i]);
			bankFile.erase(bankFile.begin()+i);
			// recheck on this index
			--i;
		}
		else
		{
			bool	upToDate = true;
			// check file list and date
			nlassert(bankname == CFile::getFilenameWithoutExtension(bankFile[i]));

			// read the sample bank file header.
			try
			{
				CIFile	sbf(bankFile[i]);
				TSampleBankHeader	hdr;
				sbf.serial(hdr);

				vector<string>	sampleList;
				CPath::getPathContent(bankDir[i], false, false, true, sampleList);
				sort(sampleList.begin(), sampleList.end());
				if (sampleList.size() == hdr.Name.size())
				{
					for (uint j=0; j<sampleList.size(); ++j)
					{
						// check same filename
						if (CFile::getFilename(sampleList[j]) != hdr.Name[j])
						{
							upToDate = false;
							break;
						}
						// check modification date
						if (CFile::getFileModificationDate(sampleList[j]) >= CFile::getFileModificationDate(bankFile[i]))
						{
							upToDate = false;
							break;
						}
					}
				}
			}
			catch(Exception e)
			{
				upToDate = false;
			}

			if (!upToDate)
			{
				nlinfo("Need to update bank file [%s]", bankname.c_str());
				CFile::deleteFile(bankFile[i]);
				bankFile.erase(bankFile.begin()+i);
				// recheck on this index
				--i;
			}
		}
	}
	// clear any out of date bank file
	for (; i<bankFile.size(); ++i)
	{
		CFile::deleteFile(bankFile[i]);
	}


/*
	// clear the exisiting list file
	{
		vector<string>	fileList;
		CPath::getPathContent(sp, false, false, true, fileList);

		for (uint i=0; i<fileList.size(); ++i)
		{
			if (fileList[i].find(".sample_bank_list") == fileList[i].size() - 17)
			{
				CFile::deleteFile(fileList[i]);
			}
		}
	}

	std::vector <std::string> dirList;
	if(!sp.empty())
		CPath::getPathContent(sp, false, true, false, dirList);

	while (!dirList.empty())
	{
		nldebug("Generating sample bank list for %s", dirList.back().c_str());
		std::vector<std::string> sampleList;
		CPath::getPathContent(dirList.back(), true, false, true, sampleList);

		for (uint i=0; i< sampleList.size(); ++i)
		{
			sampleList[i] = CFile::getFilename(sampleList[i]);
			nldebug("+- Adding sample %s to bank", sampleList[i].c_str());
		}

		std::vector<std::string> temp;
		NLMISC::explode(dirList.back(), "/", temp, true);
		nlassert(!temp.empty());
		std::string listName(temp.back());

		COFile file(_SamplePath+listName+SampleBankListExt);
		file.serialCont(sampleList);
		dirList.pop_back();
	}
*/
	// update the searh path content
	bool compressed = CPath::isMemoryCompressed();
	if (!compressed)
		CPath::addSearchPath(_SamplePath);
}


void				CAudioMixerUser::setBackgroundFlagName(uint flagIndex, const std::string &flagName)
{
	if (flagIndex < TBackgroundFlags::NB_BACKGROUND_FLAGS)
		_BackgroundFilterNames[flagIndex] = flagName;
}
void				CAudioMixerUser::setBackgroundFlagShortName(uint flagIndex, const std::string &flagShortName)
{
	if (flagIndex < TBackgroundFlags::NB_BACKGROUND_FLAGS)
		_BackgroundFilterShortNames[flagIndex] = flagShortName;
}
const std::string	&CAudioMixerUser::getBackgroundFlagName(uint flagIndex)
{
	static std::string bad("");
	if (flagIndex < TBackgroundFlags::NB_BACKGROUND_FLAGS)
		return _BackgroundFilterNames[flagIndex];
	else
		return bad;
}
const std::string	&CAudioMixerUser::getBackgroundFlagShortName(uint flagIndex)
{
	static std::string bad("");
	if (flagIndex < TBackgroundFlags::NB_BACKGROUND_FLAGS)
		return _BackgroundFilterShortNames[flagIndex];
	else
		return bad;
}

const UAudioMixer::TBackgroundFlags		&CAudioMixerUser::getBackgroundFlags()
{
	return _BackgroundSoundManager->getBackgroundFlags();
}
const UAudioMixer::TBackgroundFilterFades &CAudioMixerUser::getBackgroundFilterFades()
{
	return _BackgroundSoundManager->getBackgroundFilterFades();
}


class CUserVarSerializer
{
public:
	std::vector<CAudioMixerUser::CControledSources>		Controlers;
	void readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const std::string &name)
	{
		try
		{
			std::string varname, soundName, paramId;
			NLGEORGES::UFormElm &root = form->getRootNode();
			NLGEORGES::UFormElm *items;
			uint size;

			CAudioMixerUser::CControledSources	cs;

			// preset the default value
			cs.Value = 0.0f;

			root.getValueByName(varname, ".Name");
			root.getValueByName(paramId, ".ParamId");

			cs.Name = CStringMapper::map(varname);
			if (paramId == "Gain")
				cs.ParamId = CAudioMixerUser::gain_control;
			else if (paramId == "Pitch")
				cs.ParamId = CAudioMixerUser::pitch_control;
			else
				return;

			root.getNodeByName(&items, ".Sounds");
			items->getArraySize(size);

			for (uint i=0; i<size; ++i)
			{
				items->getArrayValue(soundName, i);
				soundName = soundName.substr(0, soundName.find(".sound"));

				cs.SoundNames.push_back(CStringMapper::map(soundName));
			}

			if (!cs.SoundNames.empty())
				Controlers.push_back(cs);
		}
		catch(...)
		{}
	}

	void serial (NLMISC::IStream &s)
	{
		s.serialCont(Controlers);
	}

	void removed()
	{}

	static uint getVersion () { return 2; }


};

void CAudioMixerUser::initUserVar()
{
	_UserVarControls.clear();
	/// Temporary container.
	std::map<std::string, CUserVarSerializer> Container;

	// read all *.user_var_binding sheet in data/sound/user_var folder

	// load the sound_group sheets
	::loadForm("user_var_binding", _PackedSheetPath+"user_var_binding.packed_sheets", Container, _UpdatePackedSheet, false);
	// fill the real container.
	std::map<std::string, CUserVarSerializer>::iterator first(Container.begin()), last(Container.end());
	for (; first != last; ++first)
	{
		for (uint i=0; i<first->second.Controlers.size(); ++i)
		{
			_UserVarControls.insert(make_pair(first->second.Controlers[i].Name, first->second.Controlers[i]));
		}
	}

	// update all the sounds to refer to the controler.
	{
		TUserVarControlsContainer::iterator first(_UserVarControls.begin()), last(_UserVarControls.end());
		for(;  first != last; ++first)
		{
			std::vector<NLMISC::TStringId>::iterator first2(first->second.SoundNames.begin()), last2(first->second.SoundNames.end());
			for (; first2 != last2; ++first2)
			{
				CSound *sound = getSoundId(*first2);
				if (sound != 0)
				{
					// ok, the sound exist !
					sound->_UserVarControler = first->second.Name;
				}
			}
		}
	}

}

void CAudioMixerUser::CControledSources::serial(NLMISC::IStream &s)
{
	std::string name, soundName;
	if (s.isReading())
	{
		s.serial(name);
		Name = CStringMapper::map(name);
		s.serialEnum(ParamId);

		uint32 size;
		s.serial(size);
		for (uint i=0; i<size; ++i)
		{
			s.serial(soundName);
			SoundNames.push_back(CStringMapper::map(soundName));
		}
	}
	else
	{
		name = CStringMapper::unmap(Name);
		s.serial(name);
		s.serialEnum(ParamId);

		uint32 size = SoundNames.size();
		s.serial(size);

		for (uint i=0; i<size; ++i)
		{
			soundName = CStringMapper::unmap(SoundNames[i]);
			s.serial(soundName);
		}
	}

	// Default value to 0.
	Value = 0.0f;
}




void CAudioMixerUser::setUserVar(NLMISC::TStringId varName, float value)
{
	TUserVarControlsContainer::iterator it(_UserVarControls.find(varName));
	if (it != _UserVarControls.end())
	{
		// ok we found the var !
		// do some work only if the value is different (we don't trust client for
		// being smart ;) )
//		if (it->second.Value != value)
		{
			it->second.Value = value;
			// update all sources
			std::set<CSourceCommon*>::iterator first(it->second.Sources.begin()), last(it->second.Sources.end());
			for (; first != last; ++first)
			{
				if (it->second.ParamId == gain_control)
				{
					float relGain = (*first)->getRelativeGain();
					float gain = (*first)->getSound()->getGain();
					(*first)->setGain(gain * value);
					(*first)->setRelativeGain(relGain);
				}
				else
				{
					(*first)->setPitch(value);
				}
			}
		}
	}
}

float CAudioMixerUser::getUserVar(NLMISC::TStringId varName)
{
	TUserVarControlsContainer::iterator it(_UserVarControls.find(varName));
	if (it != _UserVarControls.end())
	{
		return it->second.Value;
	}
	// return a default value.
	return 1.0f;
}

void CAudioMixerUser::addUserControledSource(CSourceCommon *source, NLMISC::TStringId varName)
{
	TUserVarControlsContainer::iterator it(_UserVarControls.find(varName));
	if (it != _UserVarControls.end())
	{
		// ok, the var exist, insert this source
		it->second.Sources.insert(source);
		// update the controled parameter
		if (it->second.ParamId == gain_control)
		{
			float relGain = source->getRelativeGain();
			float gain = source->getSound()->getGain();
			source->setGain(gain * it->second.Value);
			source->setRelativeGain(relGain);
		}
		else
		{
			source->setPitch(it->second.Value);
		}
	}
}

void CAudioMixerUser::removeUserControledSource(CSourceCommon *source, NLMISC::TStringId varName)
{
	TUserVarControlsContainer::iterator it(_UserVarControls.find(varName));
	if (it != _UserVarControls.end())
	{
		// ok, the var exist, remove this source
		it->second.Sources.erase(source);
	}
}



// ******************************************************************
void	CAudioMixerUser::bufferUnloaded(IBuffer *buffer)
{
	// check all track to find a track playing this buffer.
	for (uint i = 0; i < _Tracks.size(); ++i)
	{
		CTrack *track = _Tracks[i];
		if (track && track->getSource())
		{
			if (track->getSource()->getBuffer() == buffer)
			{
				track->getSource()->stop();
			}
		}
	}
}


// ******************************************************************

void				CAudioMixerUser::enable( bool b )
{
	// TODO :  rewrite this method

	nlassert(false);
/*	if ( b )
	{
		// Reenable
		_NbTracks = _MaxNbTracks;
	}
	else
	{
		// Disable
		uint i;
		for ( i=0; i!=_NbTracks; i++ )
		{
			if ( _Tracks[i] && ! _Tracks[i]->isAvailable() )
			{
				_Tracks[i]->getSource()->leaveTrack();
//				nlassert(_PlayingSources.find(_Tracks[i]->getSource()) != _PlayingSources.end());
//				_PlayingSources.erase(_Tracks[i]->getSource());
			}
		}
		_NbTracks = 0;
	}
*/
}

// ******************************************************************

ISoundDriver*		CAudioMixerUser::getSoundDriver()
{
	return _SoundDriver;
}

// ******************************************************************

void				CAudioMixerUser::getFreeTracks( uint nb, CTrack **tracks )
{
	std::vector<CTrack*>::iterator first(_FreeTracks.begin()), last(_FreeTracks.end());
	for (nb =0; first != last; ++first, ++nb)
	{
		tracks[nb] = *first;
	}
}


// ******************************************************************

void				CAudioMixerUser::applyListenerMove( const NLMISC::CVector& listenerpos )
{
	// Store position
	_ListenPosition = listenerpos;

	_BackgroundSoundManager->updateBackgroundStatus();

	// Environmental effect
//	computeEnvEffect( listenerpos );

/*	// Environment sounds
	if ( _EnvSounds != NULL )
	{
		_EnvSounds->recompute();
	}
*/
}

// ******************************************************************

void				CAudioMixerUser::reloadSampleBanks(bool async)
{
	CPath::addSearchPath(_SamplePath, true, false);
	if (_UpdatePackedSheet)
		buildSampleBankList();
	CSampleBank::reload(async);
}

// ******************************************************************

CTrack *CAudioMixerUser::getFreeTrackWithoutSource(bool steal)
{
	if (!_FreeTracks.empty())
	{
		CTrack *free_track = _FreeTracks.back();
		_FreeTracks.pop_back();
		nlassert(!free_track->getSource());		
		++_ReserveUsage[HighestPri];
		if (_UseEax) free_track->DrvSource->setEffect(NULL); // no reverb!
		return free_track;
	}
	else if (steal) for (uint i = 0; i < _Tracks.size(); ++i)
	{
		CSimpleSource *src2 = _Tracks[i]->getSource();
		if (src2)
		{
			src2->stop();
			if (_FreeTracks.empty())
			{
				nlwarning("No free track after cutting a playing sound source !");
			}
			else
			{
				CTrack *free_track = _FreeTracks.back();
				_FreeTracks.pop_back();
				nlassert(!free_track->getSource());
				++_ReserveUsage[HighestPri];
				if (_UseEax) free_track->DrvSource->setEffect(NULL); // no reverb!
				return free_track;
			}
		}
	}
	return NULL;
}

CTrack *CAudioMixerUser::getFreeTrack(CSimpleSource *source)
{
//	nldebug("There are %d free tracks", _FreeTracks.size() );
	// at least some track free ?
	if	(!_FreeTracks.empty())
	{
		// under the low water mark or  under the reserve
		if (_FreeTracks.size() > _LowWaterMark
				|| _ReserveUsage[source->getPriority()] < _PriorityReserve[source->getPriority()] )
		{
			// non discardable track  or not too many waiting source
			if (source->getPriority() == HighestPri
				|| _FreeTracks.size() > _SourceWaitingForPlay.size())
			{
				CTrack *ret = _FreeTracks.back();
				_FreeTracks.pop_back();
				ret->setSource(source);
				_ReserveUsage[source->getPriority()]++;
//				nldebug("Track %p assign to source %p", ret, ret->getSource());
				return ret;
			}
		}
	}
	// try to find a track with a source cuttable
	{
		float d1, d2, t1, t2;
		d1 = (source->getPos() - _ListenPosition).norm();
		t1 = max(0.0f, 1-((d1-source->getSimpleSound()->getMinDistance()) / (source->getSimpleSound()->getMaxDistance() - source->getSimpleSound()->getMinDistance())));

		for (uint i = 0; i < _Tracks.size(); ++i)
		{
			CSimpleSource *src2 = _Tracks[i]->getSource();
			if (src2)
			{
				d2 = (src2->getPos() - _ListenPosition).norm();
				t2 = max(0.0f, 1-((d2-src2->getSimpleSound()->getMinDistance()) / (src2->getSimpleSound()->getMaxDistance() - src2->getSimpleSound()->getMinDistance())));

				const float tfactor = 1.3f;
				if (t1 > t2 * tfactor)
//				if (d1 < d2)
				{
//					nldebug("Cutting source %p with source %p (%f > %f*%f)", src2, source, t1, tfactor, t2);
					// on peut cuter cette voie !
					src2->stop();
					if (_FreeTracks.empty())
					{
						nlwarning("No free track after cutting a playing sound source !");
					}
					else
					{
						CTrack *ret = _FreeTracks.back();
						_FreeTracks.pop_back();
						ret->setSource(source);
						_ReserveUsage[source->getPriority()]++;
//						nldebug("Track %p assign to source %p", ret, ret->getSource());
						return ret;
					}
				}
			}
		}
	}

	return 0;
}

// ******************************************************************

void CAudioMixerUser::freeTrackWithoutSource(CTrack *track)
{
	nlassert(track);

	if (_UseEax) track->DrvSource->setEffect(_ReverbEffect); // return reverb!
	--_ReserveUsage[HighestPri];
	_FreeTracks.push_back(track);
}

void CAudioMixerUser::freeTrack(CTrack *track)
{
	nlassert(track != 0);
	nlassert(track->getSource() != 0);

//	nldebug("Track %p free by source %p", track, track->getSource());

	_ReserveUsage[track->getSource()->getPriority()]--;
	track->setSource(0);
	_FreeTracks.push_back(track);
}

// ******************************************************************

void CAudioMixerUser::getPlayingSoundsPos(bool virtualPos, std::vector<std::pair<bool, NLMISC::CVector> > &pos)
{
	int nbplay = 0;
	int	nbmute = 0;
	int	nbsrc = 0;

	TSourceContainer::iterator first(_Sources.begin()), last(_Sources.end());
	for (; first != last; ++first)
	{
		CSourceCommon *ps = *first;
		if (ps->getType() == CSourceCommon::SOURCE_SIMPLE)
		{
			CSimpleSource *source = static_cast<CSimpleSource*>(*first);
			nbsrc++;

			if (source->isPlaying())
			{
				if (virtualPos)
					pos.push_back(make_pair(source->getTrack() == 0, source->getVirtualPos()));
				else
					pos.push_back(make_pair(source->getTrack() == 0, source->getPos()));

				if (source->getTrack() == 0)
					nbmute++;
				else
				{
//					nldebug ("Source %p playing on track %p", source, source->getTrack());
					nbplay ++;
				}
			}
		}
	}

//	nldebug("Total source : %d, playing : %d, muted : %d", nbsrc, nbplay, nbmute);
}



void				CAudioMixerUser::update()
{
	H_AUTO(NLSOUND_AudioMixerUpdate)
/*	static NLMISC::TTime lastUpdate = NLMISC::CTime::getLocalTime();
	NLMISC::TTime now = NLMISC::CTime::getLocalTime();

	nldebug("Mixer update : %u ms", uint(now - lastUpdate));
	lastUpdate = now;
*/
#if NL_PROFILE_MIXER
	TTicks start = CTime::getPerformanceTime();
#endif

	// update the object.
	{
		H_AUTO(NLSOUND_AudioMixerUpdateObjet)
		// 1st, update the event list
		{
			std::vector<std::pair<IMixerUpdate*, bool> >::iterator first(_UpdateEventList.begin()), last(_UpdateEventList.end());
			for (; first != last; ++first)
			{
				if (first->second)
				{
//					nldebug("Inserting update %p", first->first);
					_UpdateList.insert(first->first);
				}
				else
				{
//					nldebug("Removing update %p", first->first);
					_UpdateList.erase(first->first);
				}
			}
			_UpdateEventList.clear();
		}
		// 2nd, do the update
		{
			TMixerUpdateContainer::iterator first(_UpdateList.begin()), last(_UpdateList.end());
			for (; first != last; ++first)
			{
				if( *first == 0)
				{
					nlwarning("NULL pointeur in update list !");
				}
				else
				{
					// call the update method.
					const IMixerUpdate	*update = *first;
					const_cast<IMixerUpdate*>(update)->onUpdate();
				}
			}
		}
	}
	// send the event.
	{
		H_AUTO(NLSOUND_AudioMixerUpdateSendEvent)

		// **** 1st, update the event list
		{
			std::list<std::pair<NLMISC::TTime, IMixerEvent*> >::iterator first(_EventListUpdate.begin()), last(_EventListUpdate.end());
			for (; first != last; ++first)
			{
				// add an event
//				nldebug ("Add event %p", first->second);
				TTimedEventContainer::iterator it(_EventList.insert(make_pair(first->first, NLMISC::CDbgPtr<IMixerEvent>(first->second))));
				_Events.insert(make_pair(first->second, it));
			}

			_EventListUpdate.clear();
		}

		// **** 2nd, call the events
		TTime now = NLMISC::CTime::getLocalTime();
		while (!_EventList.empty() && _EventList.begin()->first <= now)
		{
			// get the event
			CAudioMixerUser::IMixerEvent	*currentEvent = _EventList.begin()->second;

			// remove the right entry in the _Events multimap.
			TEventContainer::iterator it(_Events.lower_bound(_EventList.begin()->second));
			while (it->first == _EventList.begin()->second.ptr())
			{
				if (it->second == _EventList.begin())
				{
					_Events.erase(it);
					break;
				}
				it++;
			}

			// remove from the _EventList
			_EventList.erase(_EventList.begin());

			// now, run the event
//			nldebug("Sending Event %p", _EventList.begin()->second);
			nlassert(currentEvent);
			currentEvent->onEvent();

#if defined(NL_DEBUG) || defined(NL_DEBUG_FAST)
			currentEvent = 0;
#endif
		}

	}

	// update the background sound
	_BackgroundSoundManager->updateBackgroundStatus();

	// update the background music
	_BackgroundMusicManager->update();

	uint i;
	// update music channels
	for (i = 0; i < _NbMusicChannelFaders; ++i)
		_MusicChannelFaders[i].update();

	// Check all playing track and stop any terminated buffer.
	for (i=0; i<_Tracks.size(); ++i)
	{
		if (!_Tracks[i]->isPlaying())
		{
			if (_Tracks[i]->getSource() != 0)
			{
				CSimpleSource *source = _Tracks[i]->getSource();
				source->stop();
			}

			// try to play any waiting source.
			if (!_SourceWaitingForPlay.empty())
			{
				// check if the source still exist before trying to play it
				if (_Sources.find(_SourceWaitingForPlay.front()) != _Sources.end())
					_SourceWaitingForPlay.front()->play();
//				nldebug("Before POP Sources waiting : %u", _SourceWaitingForPlay.size());
				_SourceWaitingForPlay.pop_front();
//				nldebug("After POP Sources waiting : %u", _SourceWaitingForPlay.size());
			}
		}
	}

	if (_ClusteredSound)
	{
		H_AUTO(NLSOUND_UpdateClusteredSound)
		// update the clustered sound...
		CVector view, up;
		_Listener.getOrientation(view, up);
		_ClusteredSound->update(_ListenPosition, view, up);

		// update all playng track according to there cluster status
		for (i=0; i<_Tracks.size(); ++i)
		{
			if (_Tracks[i]->isPlaying())
			{
				if (_Tracks[i]->getSource() != 0)
				{
					CSimpleSource *source = _Tracks[i]->getSource();
					if (source->getCluster() != 0)
					{
						// need to check the cluster status
						const CClusteredSound::CClusterSoundStatus *css = _ClusteredSound->getClusterSoundStatus(source->getCluster());
						if (css != 0)
						{
							// there is some data here, update the virtual position of the sound.
							float dist = (css->Position - source->getPos()).norm();
							CVector vpos(_ListenPosition + css->Direction * (css->Dist + dist));
//							_Tracks[i]->DrvSource->setPos(source->getPos() * (1-css->PosAlpha) + css->Position*(css->PosAlpha));
							_Tracks[i]->DrvSource->setPos(source->getPos() * (1-css->PosAlpha) + vpos*(css->PosAlpha));
							// update the relative gain
							_Tracks[i]->DrvSource->setGain(source->getRelativeGain()*source->getGain()*css->Gain);
#if EAX_AVAILABLE == 1
							if (_UseEax)
							{
								H_AUTO(NLSOUND_SetEaxProperties)
								// update the occlusion parameters
								_Tracks[i]->DrvSource->setEAXProperty(DSPROPERTY_EAXBUFFER_OCCLUSION, (void*)&css->Occlusion, sizeof(css->Occlusion));
								_Tracks[i]->DrvSource->setEAXProperty(DSPROPERTY_EAXBUFFER_OCCLUSIONLFRATIO, (void*)&css->OcclusionLFFactor, sizeof(css->OcclusionLFFactor));
	//							if (lastRatio[i] != css->OcclusionRoomRatio)
	//							{
									_Tracks[i]->DrvSource->setEAXProperty(DSPROPERTY_EAXBUFFER_OCCLUSIONROOMRATIO, (void*)&css->OcclusionRoomRatio, sizeof(css->OcclusionRoomRatio));
	//								lastRatio[i] = css->OcclusionRoomRatio;
	//								nldebug("Setting room ration.");
	//							}
								_Tracks[i]->DrvSource->setEAXProperty(DSPROPERTY_EAXBUFFER_OBSTRUCTION, (void*)&css->Obstruction, sizeof(css->Obstruction));
							}
#endif
						}
					}
				}
			}
		}
	}


	// Debug info
	/*uint32 i;
	nldebug( "List of the %u tracks", _NbTracks );
	for ( i=0; i!=_NbTracks; i++ )
	{
		CSimpleSource *su;
		if ( su = _Tracks[i]->getSource() )
		{
			nldebug( "%u: %p %s %s %s %s, vol %u",
				    i, &_Tracks[i]->DrvSource, _Tracks[i]->isAvailable()?"FREE":"USED",
					_Tracks[i]->isAvailable()?"":(su->isPlaying()?"PLAYING":"STOPPED"),
					_Tracks[i]->isAvailable()?"":PriToCStr[su->getPriority()],
					_Tracks[i]->isAvailable()?"":(su->getSound()?su->getSound()->getFilename().c_str():""),
					(uint)(su->getGain()*100.0f) );
		}
	}*/

	_SoundDriver->commit3DChanges();

#if NL_PROFILE_MIXER
	_UpdateTime = CTime::ticksToSecond(CTime::getPerformanceTime() - start);
	_UpdateCount++;
#endif

/*	// display the track using...
	{
		char tmp[2048] = "";
		string str;

		for (uint i=0; i<_NbTracks/2; ++i)
		{
			sprintf(tmp, "[%2u]%8p ", i, _Tracks[i]->getSource());
			str += tmp;
		}
		nldebug((string("Status1: ")+str).c_str());
		str = "";
		for (i=_NbTracks/2; i<_NbTracks; ++i)
		{
			sprintf(tmp, "[%2u]%8p ", i, _Tracks[i]->getSource());
			str += tmp;
		}
//		nldebug((string("Status2: ")+str).c_str());
	}
*/
}


// ******************************************************************

TSoundId			CAudioMixerUser::getSoundId( const NLMISC::TStringId &name )
{
	return CSoundBank::instance()->getSound(name);
}

// ******************************************************************

void				CAudioMixerUser::addSource( CSourceCommon *source )
{
	nlassert(_Sources.find(source) == _Sources.end());
	_Sources.insert( source );

//	_profile(( "AM: ADDSOURCE, SOUND: %d, TRACK: %p, NAME=%s", source->getSound(), source->getTrack(),
//			source->getSound() && (source->getSound()->getName()!="") ? source->getSound()->getName().c_str() : "" ));

}


static bool checkSound(CSound *sound, const vector<pair<string, CSound*> > &subsounds, vector<string> &missingFiles)
{
	vector<pair<string, CSound*> >::const_iterator first(subsounds.begin()), last(subsounds.end());

	for (; first != last; ++first)
	{
		if (first->second == sound)
			return false;

		if (first->second == 0 && !first->first.empty())
			missingFiles.push_back(first->first);
		else if (first->second != 0)
		{
			vector<pair<string, CSound*> > v2;
			first->second->getSubSoundList(v2);

			if (!checkSound(sound, v2, missingFiles))
				return false;
		}
	}
	return true;
}


bool CAudioMixerUser::tryToLoadSoundBank(const std::string &sampleName)
{
	string path = CPath::lookup(sampleName, false, false, false);
	if (!path.empty())
	{
		// extract samplebank name
		path = NLMISC::CFile::getPath(path);
		vector<string> rep;
		explode(path, string("/"), rep, true);

		loadSampleBank(false, rep.back());

		return true;
	}
	else
	{
		nlwarning("tryToLoadSoundBank : can't find sample bank for '%s'", sampleName.c_str());
		return false;
	}
}


// ******************************************************************

USource				*CAudioMixerUser::createSource( TSoundId id, bool spawn, TSpawnEndCallback cb, void *userParam, NL3D::CCluster *cluster, CSoundContext *context )
{
#if NL_PROFILE_MIXER
	TTicks start = CTime::getPerformanceTime();
#endif

	_profile(( "AM: [%u]---------------------------------------------------------------", curTime() ));
	_profile(( "AM: CREATESOURCE: SOUND=%p, NAME=%s, TIME=%d", id, id->getName().c_str(), curTime() ));
	_profile(( "AM: SOURCES: %d, PLAYING: %d, TRACKS: %d", getSourcesNumber(), getPlayingSourcesNumber(), getNumberAvailableTracks() ));

	if ( id == NULL )
	{
		_profile(("AM: FAILED CREATESOURCE"));
//		nldebug( "AM: Sound not created: invalid sound id" );
		return NULL;
	}

	USource *ret = NULL;

	if (_AutoLoadSample)
	{
		if (id->getSoundType() == CSound::SOUND_SIMPLE)
		{
			CSimpleSound *ss = (CSimpleSound*)id;
			if (ss->getBuffer() == NULL)
			{
				const string sampleName = CStringMapper::unmap(ss->getBuffername()) + ".wav";

				tryToLoadSoundBank(sampleName);
			}
		}
		else
		{
			uint32 count = 0;
retrySound:
			++count;
			vector<pair<string, CSound*> > subsounds;
			id->getSubSoundList(subsounds);
			vector<string> missingFiles;
			// check the sound before anythink else
			bool invalid = !checkSound(id, subsounds, missingFiles);

			if (invalid)
			{
				nlwarning("The sound %s contain an infinite recursion !", CStringMapper::unmap(id->getName()).c_str());
				return NULL;
			}

			if (!missingFiles.empty()/* && count <= missingFiles.size()*/)
			{
				// try to load missing sample bank
				for (uint i=0; i<missingFiles.size(); ++i)
				{
					if (missingFiles[i].find(" (sample)") != string::npos)
					{
						// try to find the sample bank
						string sample = missingFiles[i].substr(0, missingFiles[i].find(" (sample)")) + ".wav";

						if (tryToLoadSoundBank(sample))
							goto retrySound;
					}
				}
			}
		}
	}

	if (id->getSoundType() == CSound::SOUND_SIMPLE)
	{
		CSimpleSound	*simpleSound = static_cast<CSimpleSound	*>(id);
		// This is a simple sound
		if (simpleSound->getBuffer() == NULL)
		{
			static std::set<std::string> warned;

			const std::string &name = CStringMapper::unmap(simpleSound->getBuffername());
			if (warned.find(name) == warned.end())
			{
				nlwarning ("Can't create the sound '%s'", name.c_str());
				warned.insert(name);
			}
			return NULL;
		}

		// Create source
		CSimpleSource *source = new CSimpleSource( simpleSound, spawn, cb, userParam, cluster);

//		nldebug("Mixer : source %p created", source);

		if (source->getBuffer() != 0)
		{
			// Link the position to the listener position if it'a stereo source
			if ( source->getBuffer()->isStereo() )
			{
				source->set3DPositionVector( &_ListenPosition );
			}
		}
		else
		{
			nlassert(false); // FIXME
		}
		ret = source;
	}
	else if (id->getSoundType() == CSound::SOUND_COMPLEX)
	{
		CComplexSound	*complexSound = static_cast<CComplexSound*>(id);
		// This is a pattern sound.
		ret =  new CComplexSource(complexSound, spawn, cb, userParam, cluster);
	}
	else if (id->getSoundType() == CSound::SOUND_BACKGROUND)
	{
		// This is a background sound.
		CBackgroundSound	*bgSound = static_cast<CBackgroundSound	*>(id);
		ret = new CBackgroundSource(bgSound, spawn, cb, userParam, cluster);
	}
	else if (id->getSoundType() == CSound::SOUND_MUSIC)
	{
		// This is a background music sound
		CMusicSound *music_sound= static_cast<CMusicSound*>(id);
		ret = new CMusicSource(music_sound, spawn, cb, userParam, cluster);
	}
	else if (id->getSoundType() == CSound::SOUND_CONTEXT)
	{
		static CSoundContext	defaultContext;
		// This is a context sound.
		if (context == 0)
			context = &defaultContext;

		CContextSound	*ctxSound = static_cast<CContextSound	*>(id);
		CSound			*sound = ctxSound->getContextSound(*context);
		if (sound != 0)
		{
			ret = createSource(sound, spawn, cb, userParam, cluster);
			// Set the volume of the source according to the context volume
			if (ret != 0)
			{
				ret->setGain(ret->getGain() * ctxSound->getGain());
				float pitch = ret->getPitch() * ctxSound->getPitch();
				ret->setPitch(pitch);
			}
		}
		else
			ret = 0;
	}
	else
	{
//		nlassertex(false, ("Unknown sound class !"));
		nlwarning("Unknow sound class : %u", id->getSoundType());
	}

#if NL_PROFILE_MIXER
	_CreateTime = CTime::ticksToSecond(CTime::getPerformanceTime() - start);
	_CreateCount++;
#endif

	//nldebug( "AM: Source created" );
	return ret;
}


// ******************************************************************

USource				*CAudioMixerUser::createSource( const NLMISC::TStringId &name, bool spawn, TSpawnEndCallback cb, void *userParam, NL3D::CCluster *cluster, CSoundContext *context)
{
	return createSource( getSoundId( name ), spawn, cb, userParam, cluster, context);
}


// ******************************************************************

void				CAudioMixerUser::removeSource( CSourceCommon *source )
{
	nlassert( source != NULL );

	size_t n = _Sources.erase(source);
	nlassert(n == 1);
}


// ******************************************************************

void				CAudioMixerUser::selectEnvEffects( const std::string &tag )
{
	nlassertex(false, ("Not implemented yet"));
/*	// Select Env
	vector<CEnvEffect*>::iterator ipe;
	for ( ipe=_EnvEffects.begin(); ipe!=_EnvEffects.end(); ++ipe )
	{
		(*ipe)->selectEnv( tag );
	}

	// Compute
	CVector pos;
	_Listener.getPos( pos );
	computeEnvEffect( pos, true );
*/
}


// ******************************************************************

/*
void				CAudioMixerUser::loadEnvEffects( const char *filename )
{
	nlassert( filename != NULL );
	nlinfo( "Loading environmental effects from %s...", filename );

	// Unload previous env effects
	vector<CEnvEffect*>::iterator ipe;
	for ( ipe=_EnvEffects.begin(); ipe!=_EnvEffects.end(); ++ipe )
	{
		delete (*ipe);
	}
	_EnvEffects.clear();

	string str = CPath::lookup( filename, false );

	// Load env effects
	CIFile file;
	if ( !str.empty() && file.open(str) )
	{
		uint32 n = CEnvEffect::load( _EnvEffects, file );
		nldebug( "AM: Loaded %u environmental effects", n );
	}
	else
	{
		nlwarning( "AM: Environmental effects file not found" );
	}
}
*/

// ******************************************************************

uint32			CAudioMixerUser::loadSampleBank(bool async, const std::string &name, std::vector<std::string> *notfoundfiles )
{
//	nlassert( filename != NULL );

//	string path = _SamplePath;
//	path.append("/").append(filename);

	//nldebug( "Loading samples bank %s...", name.c_str() );

	CSampleBank* bank = CSampleBank::findSampleBank(CStringMapper::map(name));
	if (bank == NULL)
	{
		// create a new sample bank
		bank = new CSampleBank(name, _SoundDriver);
	}

	try
	{
		bank->load(async);
	}
	catch (Exception& e)
	{
		if (notfoundfiles)
		{
			notfoundfiles->push_back(name);
		}
		string reason = e.what();
		nlwarning( "AM: Failed to load the samples: %s", reason.c_str() );
	}


	return bank->countSamples();
}

bool CAudioMixerUser::unloadSampleBank( const std::string &name)
{
//	string path = _SamplePath;
//	path.append("/").append(filename);

	//nldebug( "Unloading samples bank %s...", name.c_str() );
	CSampleBank *pbank = CSampleBank::findSampleBank(CStringMapper::map(name));

	if (pbank != NULL)
	{
		// ok, the bank exist.
		return pbank->unload();
	}
	else
		return false;

}

// ******************************************************************

void			CAudioMixerUser::getSoundNames( std::vector<NLMISC::TStringId> &names ) const
{
	CSoundBank::instance()->getNames(names);
}


// ******************************************************************

uint			CAudioMixerUser::getPlayingSourcesCount() const
{
	return _PlayingSources;
}

// ******************************************************************

uint			CAudioMixerUser::getAvailableTracksCount() const
{
	return _FreeTracks.size();
}

uint			CAudioMixerUser::getUsedTracksCount() const
{
	return _Tracks.size() - _FreeTracks.size();
}



// ******************************************************************

string			CAudioMixerUser::getSourcesStats() const
{
	// TODO : rewrite log output

	string s;
	TSourceContainer::const_iterator ips;
	for ( ips=_Sources.begin(); ips!=_Sources.end(); ++ips )
	{
		if ( (*ips)->isPlaying() )
		{
//			char line [80];

/*			nlassert( (*ips)->getSound() && (*ips)->getSimpleSound()->getBuffer() );
			smprintf( line, 80, "%s: %u%% %s %s",
					  (*ips)->getSound()->getName().c_str(),
					  (uint32)((*ips)->getGain()*100.0f),
					  (*ips)->getBuffer()->isStereo()?"ST":"MO",
					  PriToCStr[(*ips)->getPriority()] );
			s += string(line) + "\n";
*/		}
	}
	return s;

}

// ******************************************************************
/*
void			CAudioMixerUser::loadEnvSounds( const char *filename, UEnvSound **treeRoot )
{
	nlassert( filename != NULL );
	nlinfo( "Loading environment sounds from %s...", filename );

	string str = CPath::lookup( filename, false );

	CIFile file;
	if ( !str.empty() && file.open( str ) )
	{
		uint32 n = 0; //CEnvSoundUser::load( _EnvSounds, file );
		nldebug( "AM: Loaded %u environment sounds", n );
	}
	else
	{
		nlwarning( "AM: Environment sounds file not found: %s", filename );
	}
	if ( treeRoot != NULL )
	{
		*treeRoot = _EnvSounds;
	}
}
*/

// ******************************************************************

struct CompareSources : public binary_function<const CSimpleSource*, const CSimpleSource*, bool>
{
	// Constructor
	CompareSources( const CVector &pos ) : _Pos(pos) {}

	// Operator()
	bool operator()( const CSimpleSource *s1, const CSimpleSource *s2 )
	{
		if (s1->getPriority() < s2->getPriority())
		{
			return true;
		}
		else if (s1->getPriority() == s2->getPriority())
		{
			// Equal priority, test distances to the listener
			const CVector &src1pos = s1->getPos();
			const CVector &src2pos = s2->getPos();;
			return ( (src1pos-_Pos).sqrnorm() < (src2pos-_Pos).sqrnorm() );
		}
		else
		{
			return false;
		}
	}

	// Listener pos
	const CVector &_Pos;
};


// ******************************************************************
uint32			CAudioMixerUser::getLoadedSampleSize()
{
	return CSampleBank::getTotalByteSize();
}

void			CAudioMixerUser::getLoadedSampleBankInfo(std::vector<std::pair<std::string, uint> > &result)
{
	CSampleBank::getLoadedSampleBankInfo(result);
}



void CAudioMixerUser::setListenerPos (const NLMISC::CVector &pos)
{
	_Listener.setPos(pos);
	_BackgroundSoundManager->setListenerPosition(pos);
}

NLMISC_CATEGORISED_COMMAND(nel, displaySoundInfo, "Display information about the audio mixer", "")
{
	if(args.size() != 0) return false;

	if (CAudioMixerUser::instance() == NULL)
	{
		log.displayNL ("No audio mixer available");
		return true;
	}

	log.displayNL ("%d tracks, MAX_TRACKS = %d, contains:", CAudioMixerUser::instance()->_Tracks.size(), CAudioMixerUser::instance()->getSoundDriver()->countMaxSources());

	for (uint i = 0; i < CAudioMixerUser::instance()->_Tracks.size(); i++)
	{
		if (CAudioMixerUser::instance()->_Tracks[i] == NULL)
		{
			log.displayNL ("Track %d is NULL", i);
		}
		else
		{
			log.displayNL ("Track %d %s available and %s playing.", i, (CAudioMixerUser::instance()->_Tracks[i]->isAvailable()?"is":"is not"), (CAudioMixerUser::instance()->_Tracks[i]->isPlaying()?"is":"is not"));
			if (CAudioMixerUser::instance()->_Tracks[i]->getSource() == NULL)
			{
				log.displayNL ("    CUserSource is NULL");
			}
			else
			{
				const CVector &pos = CAudioMixerUser::instance()->_Tracks[i]->getSource()->getPos();
				string bufname;
				if (CAudioMixerUser::instance()->_Tracks[i]->getSource()->getBuffer())
					bufname = CStringMapper::unmap(CAudioMixerUser::instance()->_Tracks[i]->getSource()->getBuffer()->getName());
				log.displayNL ("    CUserSource is id %d buffer name '%s' pos %f %f %f", CAudioMixerUser::instance()->_Tracks[i]->getSource()->getSound(), bufname.c_str(), pos.x, pos.y, pos.z);
			}
		}
	}

	return true;
}

void CAudioMixerUser::registerBufferAssoc(CSound *sound, IBuffer *buffer)
{
	_BufferToSources[buffer].push_back(sound);
}

void CAudioMixerUser::unregisterBufferAssoc(CSound *sound, IBuffer *buffer)
{
	TBufferToSourceContainer::iterator it(_BufferToSources.find(buffer));
	if (it != _BufferToSources.end())
	{
		std::vector<CSound*>::iterator first(it->second.begin()), last(it->second.end());

		for (; first != last; ++first)
		{
			if (*first == sound)
			{
				it->second.erase(first);
				break;
			}
		}
	}
}


/// Register an object in the update list.
void CAudioMixerUser::registerUpdate(CAudioMixerUser::IMixerUpdate *pmixerUpdate)
{
//	nldebug("Registering update %p", pmixerUpdate);
	nlassert(pmixerUpdate != 0);
	_UpdateEventList.push_back(make_pair(pmixerUpdate, true));
}
/// Unregister an object from the update list.
void CAudioMixerUser::unregisterUpdate(CAudioMixerUser::IMixerUpdate *pmixerUpdate)
{
//	nldebug("Unregistering update %p", pmixerUpdate);
	nlassert(pmixerUpdate != 0);
	_UpdateEventList.push_back(make_pair(pmixerUpdate, false));
}

/// Add an event in the future.
void CAudioMixerUser::addEvent( CAudioMixerUser::IMixerEvent *pmixerEvent, const NLMISC::TTime &date)
{
	nlassert(pmixerEvent != 0);
	//	nldebug("Adding event %p", pmixerEvent);
	_EventListUpdate.push_back(make_pair(date, pmixerEvent));
}

/// Remove any event programmed for this object.
void CAudioMixerUser::removeEvents( CAudioMixerUser::IMixerEvent *pmixerEvent)
{
	nlassert(pmixerEvent != 0);
	//	nldebug("Removing event %p", pmixerEvent);

	// we have to remove from the _EventListUpdate, in the case a IMixerEvent is
	// added/removed during the same frame!!!
	// Slow O(N) but _EventListUpdate should be small, cause cleared each frame and not so
	// many events are added/removed.
	std::list<std::pair<NLMISC::TTime, IMixerEvent*> >::iterator	itUp;
	for(itUp=_EventListUpdate.begin(); itUp!=_EventListUpdate.end();)
	{
		if(itUp->second == pmixerEvent)
			itUp= _EventListUpdate.erase(itUp);
		else
			itUp++;
	}

	// remove from the both _EventList and _Events multimap
	pair<TEventContainer::iterator, TEventContainer::iterator> range = _Events.equal_range(pmixerEvent);
	TEventContainer::iterator first(range.first), last(range.second);
	for (; first != last; ++first)
	{
		_EventList.erase(first->second);
	}
	_Events.erase(range.first, range.second);
}

void CAudioMixerUser::setBackgroundFlags(const TBackgroundFlags &backgroundFlags)
{
	_BackgroundSoundManager->setBackgroundFlags(backgroundFlags);
}

void CAudioMixerUser::setBackgroundFilterFades(const TBackgroundFilterFades &backgroundFilterFades)
{
	_BackgroundSoundManager->setBackgroundFilterFades(backgroundFilterFades);
}


//void CAudioMixerUser::loadBackgroundSoundFromRegion (const NLLIGO::CPrimRegion &region)
//{
//	_BackgroundSoundManager->loadSoundsFromRegion(region);
//}

//void CAudioMixerUser::loadBackgroundEffectsFromRegion (const NLLIGO::CPrimRegion &region)
//{
//	_BackgroundSoundManager->loadEffecsFromRegion(region);
//}
//void CAudioMixerUser::loadBackgroundSamplesFromRegion (const NLLIGO::CPrimRegion &region)
//{
//	_BackgroundSoundManager->loadSamplesFromRegion(region);
//}

void CAudioMixerUser::loadBackgroundAudioFromPrimitives(const NLLIGO::IPrimitive &audioRoot)
{
	_BackgroundSoundManager->loadAudioFromPrimitives(audioRoot);
}

void CAudioMixerUser::playBackgroundSound ()
{
	_BackgroundSoundManager->play ();
}

void CAudioMixerUser::stopBackgroundSound ()
{
	_BackgroundSoundManager->stop ();
}

void CAudioMixerUser::loadBackgroundSound (const std::string &continent, NLLIGO::CLigoConfig &config)
{
	_BackgroundSoundManager->load (continent, config);
}

void CAudioMixerUser::startDriverBench()
{
	if (_SoundDriver)
		_SoundDriver->startBench();
}

void CAudioMixerUser::endDriverBench()
{
	if (_SoundDriver)
		_SoundDriver->endBench();
}

void CAudioMixerUser::displayDriverBench(CLog *log)
{
	if (_SoundDriver)
		_SoundDriver->displayBench(log);
}

// ***************************************************************************
void CAudioMixerUser::changeMaxTrack(uint maxTrack)
{
	uint max_track_old = maxTrack;
	maxTrack = min(maxTrack, _SoundDriver->countMaxSources());
	if (maxTrack != max_track_old) nlwarning("AM: MaxTrack limited from %u to %u", (uint32)max_track_old, (uint32)maxTrack);
	
	// if same, no op
	if (maxTrack == _Tracks.size())
		return;
	
	uint prev_track_nb = (uint)_Tracks.size();
	// **** if try to add new tracks, easy
	if (maxTrack > prev_track_nb)
	{
		uint i;
		_Tracks.resize(maxTrack, NULL);
		try
		{
			for (i = prev_track_nb; i < maxTrack; ++i)
			{
				nlassert(!_Tracks[i]);

				_Tracks[i] = new CTrack();
				_Tracks[i]->init(_SoundDriver);
				if (_UseEax) _Tracks[i]->DrvSource->setEffect(_ReverbEffect);
				// insert in front because the last inserted wan be sofware buffer...
				_FreeTracks.insert(_FreeTracks.begin(), _Tracks[i]);
			}
		}
		catch ( ESoundDriver & )
		{
			delete _Tracks[i];
			// If the source generation failed, keep only the generated number of sources
			maxTrack = i;
			_Tracks.resize(maxTrack);
			nlwarning("AM: Failed to create another track, MaxTrack is %u now", (uint32)maxTrack);
		}
	}
	// **** else must delete some tracks
	else
	{
		vector<CTrack *> non_erasable;
		while (_Tracks.size() + non_erasable.size() > maxTrack && _Tracks.size() > 0)
		{
			CTrack *track = _Tracks.back();
			_Tracks.pop_back();
			nlassert(track);
			if (track->isAvailable())
			{
				_FreeTracks.erase(find(_FreeTracks.begin(), _FreeTracks.end(), track));
				delete track;
			}
			else if (track->getSource())
			{
				track->getSource()->stop();
				if (track->getSource())
				{
					nlwarning("AM: cant stop a track");
					non_erasable.push_back(track);
				}
				else
				{
					_FreeTracks.erase(find(_FreeTracks.begin(), _FreeTracks.end(), track));
					delete track;
				}
			}
			else /* music track or something */
			{
				non_erasable.push_back(track);
			}
		}
		while (non_erasable.size() > 0)
		{
			// put non erasable back into track list
			_Tracks.push_back(non_erasable.back());
			non_erasable.pop_back();
		}
		if (maxTrack != _Tracks.size())
			nlwarning("AM: Failed to reduce number of tracks; MaxTrack is now %u instead of the requested %u", (uint32)_Tracks.size(), (uint32)maxTrack);
	}
}

// ***************************************************************************
// insert calls of this where you want to debug events
void CAudioMixerUser::debugLogEvent(const char *reason)
{
	nlinfo("****** EVENTLOG: end of %s", reason);
	nlinfo("****** _EventListUpdate: %d", _EventListUpdate.size());
	std::list<std::pair<NLMISC::TTime, IMixerEvent*> >::const_iterator	itUp;
	for(itUp=_EventListUpdate.begin();itUp!=_EventListUpdate.end();itUp++)
	{
		nlinfo("\t: %d - %x", (uint32)itUp->first, itUp->second);
	}
	nlinfo("****** _EventList: %d", _EventList.size());
	TTimedEventContainer::const_iterator	it;
	for(it=_EventList.begin();it!=_EventList.end();it++)
	{
		nlinfo("\t: %d - %x", (uint32)it->first, it->second.ptr());
	}
	nlinfo("****** _Events: %d", _Events.size());
	TEventContainer::const_iterator			itEv;
	for(itEv=_Events.begin();itEv!=_Events.end();itEv++)
	{
		nlinfo("\t: %x - (%d,%x)", itEv->first, (uint32)itEv->second->first, itEv->second->second.ptr());
	}
}


// ***************************************************************************
bool	CAudioMixerUser::playMusicChannel(TMusicChannel chan, const std::string &fileName, uint xFadeTime, bool async, bool loop)
{
	if (_MusicChannelFaders[chan].isInitOk())
		return _MusicChannelFaders[chan].play(fileName, xFadeTime, async, loop);
	return false;
}

// ***************************************************************************
bool	CAudioMixerUser::playMusic(const std::string &fileName, uint xFadeTime, bool async, bool loop)
{
	return playMusicChannel(GeneralMusicChannel, fileName, xFadeTime, async, loop);
}

// ***************************************************************************
void	CAudioMixerUser::stopMusic(uint xFadeTime)
{
	if (_MusicChannelFaders[GeneralMusicChannel].isInitOk())
		_MusicChannelFaders[GeneralMusicChannel].stop(xFadeTime);
}

// ***************************************************************************
void	CAudioMixerUser::pauseMusic()
{
	if (_MusicChannelFaders[GeneralMusicChannel].isInitOk())
		_MusicChannelFaders[GeneralMusicChannel].pause();
}

// ***************************************************************************
void	CAudioMixerUser::resumeMusic()
{
	if (_MusicChannelFaders[GeneralMusicChannel].isInitOk())
		_MusicChannelFaders[GeneralMusicChannel].resume();
}

// ***************************************************************************
bool	CAudioMixerUser::isMusicEnded()
{
	if (_MusicChannelFaders[GeneralMusicChannel].isInitOk())
		return _MusicChannelFaders[GeneralMusicChannel].isEnded();
	return true;
}

// ***************************************************************************
void	CAudioMixerUser::setMusicVolume(float gain)
{
	if (_MusicChannelFaders[GeneralMusicChannel].isInitOk())
		 _MusicChannelFaders[GeneralMusicChannel].setVolume(gain);
}

// ***************************************************************************
float	CAudioMixerUser::getMusicLength()
{
	if (_MusicChannelFaders[GeneralMusicChannel].isInitOk())
		return _MusicChannelFaders[GeneralMusicChannel].getLength();
	return 0.0f;
}

// ***************************************************************************
bool	CAudioMixerUser::getSongTitle(const std::string &filename, std::string &result)
{
	if (_SoundDriver)
	{
		std::string artist;
		std::string title;
		if (_SoundDriver->getMusicInfo(filename, artist, title))
		{
			if (!title.empty())
			{
				if (!artist.empty()) result = artist + " - " + title;
				else result = title;
			}
			else if (!artist.empty())
			{
				result = artist + " - " + CFile::getFilename(filename);
			}
			else result = CFile::getFilename(filename);
			return true;
		}
	}
	result = "???";
	return false;
}

// ***************************************************************************
void	CAudioMixerUser::enableBackgroundMusic(bool enable)
{
	getBackgroundMusicManager()->enable(enable);
}

// ***************************************************************************
void	CAudioMixerUser::enableBackgroundMusicTimeConstraint(bool enable)
{
	getBackgroundMusicManager()->enableTimeConstraint(enable);
}

// ***************************************************************************
bool	CAudioMixerUser::playEventMusic(const std::string &fileName, uint xFadeTime, bool async, bool loop)
{
	return playMusicChannel(EventMusicChannel, fileName, xFadeTime, async, loop);
}

// ***************************************************************************
void	CAudioMixerUser::stopEventMusic(uint xFadeTime)
{
	if (_MusicChannelFaders[EventMusicChannel].isInitOk())
		_MusicChannelFaders[EventMusicChannel].stop();
}

// ***************************************************************************
void	CAudioMixerUser::setEventMusicVolume(float gain)
{
	if (_MusicChannelFaders[EventMusicChannel].isInitOk())
		_MusicChannelFaders[EventMusicChannel].setVolume(gain);
}

// ***************************************************************************
bool	CAudioMixerUser::isEventMusicEnded()
{
	if (_MusicChannelFaders[EventMusicChannel].isInitOk())
		_MusicChannelFaders[EventMusicChannel].isEnded();
	return true;
}

#if !FINAL_VERSION

NLMISC_CATEGORISED_COMMAND(nel, displaySoundProfile, "Display information on sound driver", "")
{
	string performance;
	CAudioMixerUser::getInstance()->writeProfile(performance);
	vector<string> pv;
	explode<string>(performance, "\n", pv, true);
	vector<string>::iterator it(pv.begin()), end(pv.end());
	for (; it != end; ++it) log.displayNL((*it).c_str());
	return true;
}

#endif /* !FINAL_VERSION */


} // NLSOUND


