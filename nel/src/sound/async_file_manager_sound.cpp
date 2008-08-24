/** \file async_file_manager_sound.cpp
 * TODO: File description
 */

/* Copyright, 2000 Nevrax Ltd.
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
#include "nel/misc/file.h"
#include "nel/misc/path.h"
#include "async_file_manager_sound.h"
#include "nel/misc/async_file_manager.h"
#include "driver/sound_driver.h"
#include "audio_mixer_user.h"

using namespace NLMISC;

namespace NLSOUND
{

//CAsyncFileManagerSound	*CAsyncFileManagerSound::_Singleton;
NLMISC_SAFE_SINGLETON_IMPL(CAsyncFileManagerSound);


/*CAsyncFileManagerSound &CAsyncFileManagerSound::getInstance()
{
	if (_Singleton == NULL)
	{
		_Singleton = new CAsyncFileManagerSound();
	}
	return *_Singleton;
}
*/

void	CAsyncFileManagerSound::terminate()
{
	if (_Instance != NULL)
	{
		INelContext::getInstance().releaseSingletonPointer("CAsyncFileManagerSound", _Instance);
		delete _Instance;
		_Instance = NULL;
	}
}

void	CAsyncFileManagerSound::loadWavFile(IBuffer *pdestBuffer, const std::string &filename)
{
	CAsyncFileManager::getInstance().addLoadTask(new CLoadWavFile(pdestBuffer, filename));
}


class CCancelLoadWavFile : public CAsyncFileManager::ICancelCallback
{
	std::string	_Filename;

	bool callback(const NLMISC::IRunnable *prunnable) const
	{
		const CAsyncFileManagerSound::CLoadWavFile *pLWF = dynamic_cast<const CAsyncFileManagerSound::CLoadWavFile*>(prunnable);

		if (pLWF != NULL)
		{
			if (pLWF->_Filename == _Filename)
				return true;
		}
		return false;
	}

public:
	CCancelLoadWavFile (const std::string &filename)
		: _Filename (filename)
	{}
};

void	CAsyncFileManagerSound::cancelLoadWaveFile(const std::string &filename)
{
	nlwarning("CAsyncFileManagerSound::cancelLoadWaveFile : not implemented yet !");
//	CAsyncFileManager::getInstance().cancelLoadTask(CCancelLoadWavFile(filename));
}


// Do not use these methods with the bigfile manager
void CAsyncFileManagerSound::loadFile (const std::string &fileName, uint8 **pPtr)
{
	CAsyncFileManager::getInstance().loadFile(fileName, pPtr);
}

void CAsyncFileManagerSound::loadFiles (const std::vector<std::string> &vFileNames, const std::vector<uint8**> &vPtrs)
{
	if (vFileNames.size() != vPtrs.size())
	{
		nlwarning("CAsyncFileManagerSound::loadFiles : number of filenames and pointer differ ! (%u file, %u ptr)", vFileNames.size(), vPtrs.size());
		// ignore load request...
		return;
	}
	CAsyncFileManager::getInstance().loadFiles(vFileNames, vPtrs);
}

void CAsyncFileManagerSound::signal (bool *pSgn)
{
	if (pSgn == 0)
	{
		nlwarning("CAsyncFileManagerSound::signal : trying to signal with a null pointer !");
		return;
	}
	CAsyncFileManager::getInstance().signal(pSgn);
}

void CAsyncFileManagerSound::cancelSignal (bool *pSgn)
{
	if (pSgn == 0)
	{
		nlwarning("CAsyncFileManagerSound::cancelSignal : trying to remove a signal with a null pointer !");
		return;
	}
	CAsyncFileManager::getInstance().cancelSignal(pSgn);
}


// Load task.
CAsyncFileManagerSound::CLoadWavFile::CLoadWavFile (IBuffer *pdestBuffer, const std::string &filename)
: _pDestbuffer(pdestBuffer), _Filename(filename)
{
	if (_Filename.empty())
	{
		nlwarning("CAsyncFileManagerSound::CLoadWavFile::CLoadWavFile : file name is empty !");
	}
	if (_pDestbuffer == 0)
	{
		nlwarning("CAsyncFileManagerSound::CLoadWavFile::CLoadWavFile : dest buffer ptr is null!");
	}
}

void CAsyncFileManagerSound::CLoadWavFile::run (void)
{
	nldebug("Loading sample %s...", _Filename.c_str());
//	nlSleep(500);
	CAudioMixerUser *mixer = CAudioMixerUser::instance();
	if (mixer == 0)
	{
		nlwarning("CAsyncFileManagerSound::CLoadWavFile::run : mixer is not avalable !");
		return;
	}

	ISoundDriver *sndDrv = mixer->getSoundDriver();
	if (sndDrv == 0)
	{
		nlwarning("CAsyncFileManagerSound::CLoadWavFile::run : sound driver is null !");
		return;
	}

	if (_pDestbuffer == 0)
	{
		nlwarning("CAsyncFileManagerSound::CLoadWavFile::run : dest buffer is null !");
		return;
	}

	if (_Filename.empty())
	{
		nlwarning("CAsyncFileManagerSound::CLoadWavFile::run : filename is empty !");
		return;
	}
	try
	{
		NLMISC::CIFile	ifile(NLMISC::CPath::lookup(_Filename));
		uint size = ifile.getFileSize();
		uint8 *buffer = new uint8[ifile.getFileSize()];
		ifile.serialBuffer(buffer, size);
		sndDrv->readWavBuffer(_pDestbuffer, _Filename, buffer, size);
		delete [] buffer;
	}
	catch(...)
	{
		nlwarning("CAsyncFileManagerSound::CLoadWavFile::run : Exeption detected during IDriver::loadWavFile(%p, %s)", _pDestbuffer, _Filename.c_str());
	}
}



} // NLSOUND