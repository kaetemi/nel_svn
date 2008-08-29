/** \file sound_driver_fmod.cpp
 * DirectSound driver
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


#include "stdfmod.h"
#include "../sound_driver.h"

#include <cmath>

#ifdef NL_OS_WINDOWS
#	include <eax.h>
#endif

#include "nel/misc/hierarchical_timer.h"
#include "nel/misc/path.h"
#include "nel/misc/file.h"
#include "nel/misc/dynloadlib.h"
#include "sound_driver_fmod.h"
#include "listener_fmod.h"

#include <fmod.h>


using namespace std;
using namespace NLMISC;


namespace NLSOUND {

#ifndef NL_STATIC

class CSoundDriverFModNelLibrary : public NLMISC::INelLibrary {
	void onLibraryLoaded(bool firstTime) { }
	void onLibraryUnloaded(bool lastTime) { }
};
NLMISC_DECL_PURE_LIB(CSoundDriverFModNelLibrary)

#endif /* #ifndef NL_STATIC */

CSoundDriverFMod* CSoundDriverFMod::_Instance = NULL;

#ifdef NL_OS_WINDOWS
#ifndef NL_STATIC

HINSTANCE CSoundDriverDllHandle = 0;

// ******************************************************************
// The main entry of the DLL. It's used to get a hold of the hModule handle.
BOOL WINAPI DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  CSoundDriverDllHandle = (HINSTANCE) hModule;
  return TRUE;
}

#endif /* #ifndef NL_STATIC */

// ***************************************************************************

#ifdef NL_STATIC
ISoundDriver* createISoundDriverInstance
#else
__declspec(dllexport) ISoundDriver *NLSOUND_createISoundDriverInstance
#endif
	(bool useEax, ISoundDriver::IStringMapperProvider *stringMapper, bool forceSoftwareBuffer)
{

	CSoundDriverFMod *driver = new CSoundDriverFMod();
	driver->init(stringMapper, forceSoftwareBuffer);
	return driver;
}

// ******************************************************************

#ifdef NL_STATIC
uint32 interfaceVersion()
#else
__declspec(dllexport) uint32 NLSOUND_interfaceVersion()
#endif
{
	return ISoundDriver::InterfaceVersion;
}

// ******************************************************************

#ifdef NL_STATIC
void outputProfile
#else
__declspec(dllexport) void NLSOUND_outputProfile
#endif
	(string &out)
{
	CSoundDriverFMod::instance()->writeProfile(out);
}

// ******************************************************************

#ifdef NL_STATIC
ISoundDriver::TDriver getDriverType()
#else
__declspec(dllexport) ISoundDriver::TDriver NLSOUND_getDriverType()
#endif
{
	return ISoundDriver::DriverFMod;
}

#elif defined (NL_OS_UNIX)
extern "C"
{
ISoundDriver *NLSOUND_createISoundDriverInstance(bool useEax, ISoundDriver::IStringMapperProvider *stringMapper, bool forceSoftwareBuffer)
{
	CSoundDriverFMod *driver = new CSoundDriverFMod();
	driver->init(stringMapper, forceSoftwareBuffer);

	return driver;
}
uint32 NLSOUND_interfaceVersion ()
{
	return ISoundDriver::InterfaceVersion;
}
} // EXTERN "C"
#endif // NL_OS_UNIX

// ******************************************************************
#ifdef NL_OS_WINDOWS
#	pragma warning( push )
#	pragma warning( disable : 4355 )
#endif
CSoundDriverFMod::CSoundDriverFMod()
:	_StringMapper(0)
{
	if ( _Instance == NULL )
	{
		_Instance = this;
		_FModOk= false;
		_MasterGain= 1.f;
		_ForceSoftwareBuffer= false;
		_LastXFadeTime= 0;
    }
	else
	{
		nlerror("Sound driver singleton instantiated twice");
	}
}
#ifdef NL_OS_WINDOWS
#	pragma warning( pop )
#endif

// ******************************************************************

void	CSoundDriverFMod::init(IStringMapperProvider *stringMapper, bool forceSoftwareBuffer)
{
	uint initFlags=0;
#ifdef NL_OS_WINDOWS
	initFlags=FSOUND_INIT_DSOUND_DEFERRED;
#endif
	_StringMapper = stringMapper;

	// Init with 32 channels, and deferred sound
	if(!FSOUND_Init(22050, 32, initFlags))
	{
		throw ESoundDriver("Failed to create the FMod driver object");
	}

	// succeed
	_FModOk= true;

	// Allocate buffer in software?
	_ForceSoftwareBuffer= forceSoftwareBuffer;

	// Display Hardware Support
	int		num2D, num3D, numTotal;
	FSOUND_GetNumHWChannels(&num2D, &num3D, &numTotal);
	nlinfo("FMod Hardware Support: %d 2D channels, %d 3D channels, %d Total Channels", num2D, num3D, numTotal);
}

// ******************************************************************

CSoundDriverFMod::~CSoundDriverFMod()
{
	//nldebug("Destroying FMOD");

	// Stop any played music
	for(uint i= 0;i<NumMusicChannel;i++)
		stopMusic(i, 0);


	// Assure that the remaining sources have released all their channels before closing
	set<CSourceFMod*>::iterator iter;
	for (iter = _Sources.begin(); iter != _Sources.end(); iter++)
	{
		(*iter)->release();
	}


	// Assure that the listener has released all resources before closing down FMod
	if (CListenerFMod::instance() != 0)
	{
		CListenerFMod::instance()->release();
	}

	// Close FMod
	if(_FModOk)
	{
		FSOUND_Close();
		_FModOk= false;
	}

	_Instance = 0;
}
// ******************************************************************

uint CSoundDriverFMod::countMaxSources()
{
	int		num2D, num3D, numTotal;
	FSOUND_GetNumHWChannels(&num2D, &num3D, &numTotal);

	// Try the hardware 3d buffers first
	if (num3D > 0)
	{
		return num3D;
	}

	// If not, try the hardware 2d buffers first
	if (num2D > 0)
	{
		return num2D;
	}

	// Okay, we'll use 32 software buffers
	return 32;
}

// ******************************************************************

void CSoundDriverFMod::writeProfile(string& out)
{
	out+= "\tFMod Driver\n";

    // Write the number of hardware buffers
	int		num2D, num3D, numTotal;
	FSOUND_GetNumHWChannels(&num2D, &num3D, &numTotal);

    out += "\t3d hw buffers: " + toString ((uint32)num3D) + "\n";
	out += "\t2d hw buffers: " + toString ((uint32)num2D) + "\n";
}


// ******************************************************************

void CSoundDriverFMod::update()
{
	H_AUTO(NLSOUND_FModUpdate)
	NLMISC::TTime now = NLMISC::CTime::getLocalTime();

	set<CSourceFMod*>::iterator first(_Sources.begin()), last(_Sources.end());
	for (;first != last; ++first)
	{
		if ((*first)->needsUpdate())
		{
			(*first)->update();
		}
	}
}

// ******************************************************************

IListener *CSoundDriverFMod::createListener()
{

    if (CListenerFMod::instance() != NULL)
    {
        return CListenerFMod::instance();
    }

    if ( !_FModOk )
        throw ESoundDriver("Corrupt driver");

    return new CListenerFMod();
}

// ******************************************************************

IBuffer *CSoundDriverFMod::createBuffer()
{

    if ( !_FModOk )
        throw ESoundDriver("Corrupt driver");

    return new CBufferFMod();
}

// ******************************************************************

void CSoundDriverFMod::removeBuffer(IBuffer *buffer)
{
}

// ***************************************************************************
bool CSoundDriverFMod::readWavBuffer( IBuffer *destbuffer, const std::string &name, uint8 *wavData, uint dataSize)
{
	return ((CBufferFMod*) destbuffer)->readWavBuffer(name, wavData, dataSize);
}

bool CSoundDriverFMod::readRawBuffer( IBuffer *destbuffer, const std::string &name, uint8 *rawData, uint dataSize, TSampleFormat format, uint32 frequency)
{
	return ((CBufferFMod*) destbuffer)->readRawBuffer(name, rawData, dataSize, format, frequency);
}


// ******************************************************************

ISource *CSoundDriverFMod::createSource()
{

    if ( !_FModOk )
        throw ESoundDriver("Corrupt driver");

	CSourceFMod* src = new CSourceFMod(0);
	src->init();
	_Sources.insert(src);

	return src;
}


// ******************************************************************

void CSoundDriverFMod::removeSource(ISource *source)
{
	_Sources.erase((CSourceFMod*) source);
}

// ******************************************************************

void CSoundDriverFMod::commit3DChanges()
{
    if ( !_FModOk )
		return;

#if MANUAL_ROLLOFF == 1
	// We handle the volume of the source according to the distance
	// ourselves. Call updateVolume() to, well..., update the volume
	// according to, euh ..., the new distance!
	CListenerFMod* listener = CListenerFMod::instance();
	if(listener)
	{
		const CVector &origin = listener->getPos();
		set<CSourceFMod*>::iterator iter;
		for (iter = _Sources.begin(); iter != _Sources.end(); iter++)
		{
			if ((*iter)->isPlaying())
			{
				(*iter)->updateVolume(origin);
			}
		}
	}
#endif

	// We handle the "SourceRelative state" ourselves. Updates sources according to current listener position/velocity
	set<CSourceFMod*>::iterator iter;
	for (iter = _Sources.begin(); iter != _Sources.end(); iter++)
	{
		(*iter)->updateFModPosIfRelative();
	}

	// update sources state each frame though
	update();

	// update the music (XFade etc...)
	updateMusic();

	// update 3D change in FMod
	FSOUND_Update();
}


// ******************************************************************

uint CSoundDriverFMod::countPlayingSources()
{
    uint n = 0;
	set<CSourceFMod*>::iterator iter;

	for (iter = _Sources.begin(); iter != _Sources.end(); iter++)
	{
		if ((*iter)->isPlaying())
		{
			n++;
		}
	}

    return n;
}


// ******************************************************************

void CSoundDriverFMod::setGain( float gain )
{
	clamp(gain, 0.f, 1.f);
	_MasterGain= gain;

	// set FMod volume
    if ( _FModOk )
	{
		uint	volume255= (uint)floor(_MasterGain*255);
		FSOUND_SetSFXMasterVolume(volume255);
	}
}

// ******************************************************************

float CSoundDriverFMod::getGain()
{
	return _MasterGain;
}


// ***************************************************************************
void	CSoundDriverFMod::startBench()
{
	NLMISC::CHTimer::startBench();
}
void	CSoundDriverFMod::endBench()
{
	NLMISC::CHTimer::endBench();
}
void	CSoundDriverFMod::displayBench(CLog *log)
{
	NLMISC::CHTimer::displayHierarchicalByExecutionPathSorted(log, CHTimer::TotalTime, true, 48, 2);
	NLMISC::CHTimer::displayHierarchical(log, true, 48, 2);
	NLMISC::CHTimer::displayByExecutionPath(log, CHTimer::TotalTime);
	NLMISC::CHTimer::display(log, CHTimer::TotalTime);
}


// ***************************************************************************
void	CSoundDriverFMod::toFModCoord(const CVector &in, float out[3])
{
	out[0]= in.x;
	out[1]= in.z;
	out[2]= in.y;
}

// ***************************************************************************
bool	CSoundDriverFMod::playMusic(uint channel, NLMISC::CIFile &fileIn, uint xFadeTime, bool loop)
{
	if(!_FModOk || channel>=NumMusicChannel)
		return false;

	return _MusicChannel[channel].playMusic(fileIn, xFadeTime, loop);
}

// ***************************************************************************
bool	CSoundDriverFMod::playMusicAsync(uint channel, const std::string &path, uint xFadeTime, uint fileOffset, uint fileSize, bool loop)
{
	if(!_FModOk || channel>=NumMusicChannel)
		return false;

	return _MusicChannel[channel].playMusicAsync(path, xFadeTime, fileOffset, fileSize, loop);
}

// ***************************************************************************
void	CSoundDriverFMod::stopMusic(uint channel, uint xFadeTime)
{
	if(!_FModOk || channel>=NumMusicChannel)
		return;

	_MusicChannel[channel].stopMusic(xFadeTime);
}

// ***************************************************************************
void	CSoundDriverFMod::pauseMusic(uint channel)
{
	if(!_FModOk || channel>=NumMusicChannel)
		return;

	_MusicChannel[channel].pauseMusic();
}

// ***************************************************************************
void	CSoundDriverFMod::resumeMusic(uint channel)
{
	if(!_FModOk || channel>=NumMusicChannel)
		return;

	_MusicChannel[channel].resumeMusic();
}

// ***************************************************************************
bool	CSoundDriverFMod::isMusicEnded(uint channel)
{
	if(!_FModOk || channel>=NumMusicChannel)
		return false;

	return _MusicChannel[channel].isMusicEnded();
}

// ***************************************************************************
float	CSoundDriverFMod::getMusicLength(uint channel)
{
	if(!_FModOk || channel>=NumMusicChannel)
		return 0.f;

	return _MusicChannel[channel].getMusicLength();
}

// ***************************************************************************
void	CSoundDriverFMod::setMusicVolume(uint channel, float gain)
{
	if(!_FModOk || channel>=NumMusicChannel)
		return;

	_MusicChannel[channel].setMusicVolume(gain);
}

// ***************************************************************************
void	CSoundDriverFMod::updateMusic()
{
	// get the dt for fade
	sint64	t1= CTime::getLocalTime();
	float	dt;
	if(_LastXFadeTime==0)
		dt= 0;
	else
		dt= (t1-_LastXFadeTime)/1000.f;
	_LastXFadeTime= t1;

	// update all channel
	for(uint i=0;i<NumMusicChannel;i++)
		_MusicChannel[i].updateMusic(dt);
}

// ***************************************************************************

bool getTag (std::string &result, const char *tag, FSOUND_STREAM *stream)
{
	void *name;
	int size;
	char tmp[512];
	int types[]=
	{
		FSOUND_TAGFIELD_ID3V1,
		FSOUND_TAGFIELD_ID3V2,
		FSOUND_TAGFIELD_VORBISCOMMENT,
	};
	uint i;
	for (i=0; i<sizeof(types)/sizeof(int); i++)
	{
		if (FSOUND_Stream_FindTagField(stream, types[i], tag, &name, &size))
		{
			strncpy (tmp, (const char*)name, min((int)sizeof(tmp),size));
			result = trim(string(tmp));
			return true;
		}
	}
	return false;
}

bool	CSoundDriverFMod::getSongTitle(const std::string &filename, std::string &result, uint fileOffset, uint fileSize)
{
	/* Open a stream, get the tag if it exists, close the stream */
	FSOUND_STREAM *stream = FSOUND_Stream_Open (filename.c_str(), FSOUND_2D, fileOffset, fileSize);
	if (stream)
	{
		string artist;
		string title;
		getTag (artist, "ARTIST", stream);
		getTag (title, "TITLE", stream);
		if (title.empty())
			result = CFile::getFilenameWithoutExtension (filename);
		else
		{
			if (artist.empty())
				result = title;
			else
				result = artist+" - "+title;
		}

		/*
		int size;
		if (FSOUND_Stream_GetNumTagFields(stream, &size))
		{
			int i;
			for (i=0; i<size; i++)
			{
				int type;
				char *name;
				void *value;
				int length;
				if (FSOUND_Stream_GetTagField(stream, i, &type, &name, &value, &length))
				{
					int toto = 0;
				}
			}
		}*/

		FSOUND_Stream_Close(stream);
		return true;
	}
	result ="???";
	return false;
}

// ***************************************************************************
void	CSoundDriverFMod::markMusicFaderEnded(void *stream, void *fader)
{
	for(uint i=0;i<NumMusicChannel;i++)
		_MusicChannel[i].markMusicFaderEnded(stream, fader);
}


} // NLSOUND
