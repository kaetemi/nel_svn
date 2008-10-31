/** \file sound_driver_fmod.cpp
 * FMod driver
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

#include <cmath>

#include "nel/misc/hierarchical_timer.h"
#include "nel/misc/path.h"
#include "nel/misc/file.h"
#include "nel/misc/dynloadlib.h"
#include "nel/misc/big_file.h"
#include "../sound_driver.h"

#include "sound_driver_fmod.h"
#include "listener_fmod.h"
#include "music_channel_fmod.h"

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
ISoundDriver* createISoundDriverInstanceFMod
#else
__declspec(dllexport) ISoundDriver *NLSOUND_createISoundDriverInstance
#endif
	(ISoundDriver::IStringMapperProvider *stringMapper)
{

	return new CSoundDriverFMod(stringMapper);
}

// ******************************************************************

#ifdef NL_STATIC
uint32 interfaceVersionFMod()
#else
__declspec(dllexport) uint32 NLSOUND_interfaceVersion()
#endif
{
	return ISoundDriver::InterfaceVersion;
}

// ******************************************************************

#ifdef NL_STATIC
void outputProfileFMod
#else
__declspec(dllexport) void NLSOUND_outputProfile
#endif
	(string &out)
{
	CSoundDriverFMod::getInstance()->writeProfile(out);
}

// ******************************************************************

#ifdef NL_STATIC
ISoundDriver::TDriver getDriverTypeFMod()
#else
__declspec(dllexport) ISoundDriver::TDriver NLSOUND_getDriverType()
#endif
{
	return ISoundDriver::DriverFMod;
}

#elif defined (NL_OS_UNIX)
extern "C"
{
ISoundDriver *NLSOUND_createISoundDriverInstance(ISoundDriver::IStringMapperProvider *stringMapper)
{
	return new CSoundDriverFMod(stringMapper);
}
uint32 NLSOUND_interfaceVersion ()
{
	return ISoundDriver::InterfaceVersion;
}
} // EXTERN "C"
#endif // NL_OS_UNIX

// ******************************************************************

CSoundDriverFMod::CSoundDriverFMod(ISoundDriver::IStringMapperProvider *stringMapper)
: _StringMapper(stringMapper), _FModOk(false), _MasterGain(1.f), _ForceSoftwareBuffer(false)
{
	
}

// ******************************************************************

CSoundDriverFMod::~CSoundDriverFMod()
{
	//nldebug("Destroying FMOD");

	// Stop any played music
	{
		set<CMusicChannelFMod *>::iterator it(_MusicChannels.begin()), end(_MusicChannels.end());
		for (; it != end; ++it)
		{
			nlwarning("CMusicChannelFMod was not deleted by user, deleting now!");
			delete *it;
		}
		_MusicChannels.clear();
	}


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
}

/// Return a list of available devices for the user. If the result is empty, you should use the default device.
// ***todo*** void CSoundDriverFMod::getDevices(std::vector<std::string> &devices) { }

/// Initialize the driver with a user selected device. If device.empty(), the default or most appropriate device is used.
void CSoundDriverFMod::init(std::string device, TSoundOptions options)
{
	// set the options: no adpcm, no effects
	_Options = options;
	// _Options = (TSoundOptions)((uint)_Options | OptionLocalBufferCopy);
	_Options = (TSoundOptions)((uint)_Options & ~OptionAllowADPCM);
	_Options = (TSoundOptions)((uint)_Options & ~OptionEnvironmentEffects);

	uint initFlags = 0;
#ifdef NL_OS_WINDOWS
	initFlags = FSOUND_INIT_DSOUND_DEFERRED;
#endif

	// Init with 32 channels, and deferred sound
	if (!FSOUND_Init(22050, 32, initFlags))
	{
		throw ESoundDriver("Failed to create the FMod driver object");
	}

	// succeed
	_FModOk = true;

	// Allocate buffer in software?
	_ForceSoftwareBuffer = getOption(OptionSoftwareBuffer);

	// Display Hardware Support
	int num2D, num3D, numTotal;
	FSOUND_GetNumHWChannels(&num2D, &num3D, &numTotal);
	nlinfo("FMod Hardware Support: %d 2D channels, %d 3D channels, %d Total Channels", num2D, num3D, numTotal);
}

/// Return options that are enabled (including those that cannot be disabled on this driver).
ISoundDriver::TSoundOptions CSoundDriverFMod::getOptions()
{
	return _Options;
}

/// Return if an option is enabled (including those that cannot be disabled on this driver).
bool CSoundDriverFMod::getOption(ISoundDriver::TSoundOptions option)
{
	return ((uint)_Options & (uint)option) == (uint)option;
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

void CSoundDriverFMod::removeBuffer(CBufferFMod * /* buffer */)
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

void CSoundDriverFMod::removeSource(CSourceFMod *source)
{
	_Sources.erase((CSourceFMod*) source);
}

// ******************************************************************

void CSoundDriverFMod::removeMusicChannel(CMusicChannelFMod *musicChannel)
{
	_MusicChannels.erase(static_cast<CMusicChannelFMod *>(musicChannel));
}

// ******************************************************************

void CSoundDriverFMod::commit3DChanges()
{
    if ( !_FModOk )
		return;

	if (getOption(OptionManualRolloff))
	{
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
	}

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

/// Create a music channel
IMusicChannel *CSoundDriverFMod::createMusicChannel()
{
	CMusicChannelFMod *music_channel = new CMusicChannelFMod(this);
	_MusicChannels.insert(music_channel);
	return static_cast<IMusicChannel *>(music_channel);
}

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

/** Get music info. Returns false if the song is not found or the function is not implemented. 
 *  \param filepath path to file, CPath::lookup done by driver
 *  \param artist returns the song artist (empty if not available)
 *  \param title returns the title (empty if not available)
 */
bool CSoundDriverFMod::getMusicInfo(const std::string &filepath, std::string &artist, std::string &title)
{
	/* Open a stream, get the tag if it exists, close the stream */
	string pathName = CPath::lookup(filepath, false);
	uint32 fileOffset = 0, fileSize = 0;
	if (pathName.empty())
	{
		nlwarning("NLSOUND FMod Driver: Music file %s not found!", filepath.c_str());
		return false;
	}
	// if the file is in a bnp
	if (pathName.find('@') != string::npos)
	{
		if (CBigFile::getInstance().getFileInfo(pathName, fileSize, fileOffset))
		{
			// set pathname to bnp
			pathName = pathName.substr(0, pathName.find('@'));			
		}
		else
		{
			nlwarning("NLSOUND FMod Driver: BNP BROKEN");
			return false;
		}
	}

	FSOUND_STREAM *stream = FSOUND_Stream_Open((const char *)CPath::lookup(filepath, false).c_str(), FSOUND_2D, (sint)fileOffset, (sint)fileSize);
	if (stream)
	{
		getTag(artist, "ARTIST", stream);
		getTag(title, "TITLE", stream);
		FSOUND_Stream_Close(stream);
		return true;
	}
	artist.clear();
	title.clear();
	return false;
}

void CSoundDriverFMod::updateMusic()
{
	set<CMusicChannelFMod *>::iterator it(_MusicChannels.begin()), end(_MusicChannels.end());
	for (; it != end; ++it) (*it)->update();
}

void CSoundDriverFMod::markMusicChannelEnded(void *stream, CMusicChannelFMod *musicChannel)
{
	// verify if it exists
	set<CMusicChannelFMod *>::iterator it(_MusicChannels.find(musicChannel));
	if (it != _MusicChannels.end()) musicChannel->markMusicChannelEnded(stream);
}

} // NLSOUND
