/** \file music_playlist_manager.cpp * 
 * CMusicPlaylistManager
 * 
 * This file is part of NEVRAX SNOWBALLS.
 * NEVRAX SNOWBALLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * NEVRAX SNOWBALLS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NEVRAX SNOWBALLS; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 * $Id$
 */

#include <nel/misc/types_nl.h>
#ifdef NL_OS_WINDOWS
#include "music_playlist_manager.h"

using namespace std;
using namespace NLMISC;
using namespace NLSOUND;

namespace SBCLIENT {

CMusicPlaylistManager *CMusicPlaylistManager::_Instance = NULL;

void CMusicPlaylistManager::init(UAudioMixer *audioMixer)
{
	nlassert(_Instance == NULL);

	_Instance = this;

	_AudioMixer = audioMixer;
	PlaylistCount = _Config.exists("Count")
		? _Config.getVar("Count").asInt() : 0;
	_Playlists = new CPlaylist[PlaylistCount];

	for (uint32 i = 0; i < PlaylistCount; ++i)
	{
		std::string iS = NLMISC::toString("%u_", i);

		_Playlists[i] = CPlaylist(
			_Config.exists(iS + "Volume")
			? _Config.getVar(iS + "Volume").asFloat() : 1.0f,
			_Config.exists(iS + "Fade")
			? _Config.getVar(iS + "Fade").asInt() : 0,
			_Config.exists(iS + "Async")
			? _Config.getVar(iS + "Async").asBool() : true,
			_Config.exists(iS + "Loop")
			? (uint8)_Config.getVar(iS + "Loop").asInt() : 0,
			i);

		_Config.setCallback(iS + "Volume", cbPlaylistVolume, this, &(_Playlists[i]));
		_Config.setCallback(iS + "Fade", cbPlaylistFade, this, &(_Playlists[i]));
		_Config.setCallback(iS + "Async", cbPlaylistAsync, this, &(_Playlists[i]));
		_Config.setCallback(iS + "Loop", cbPlaylistLoop, this, &(_Playlists[i]));

		if (_Config.exists(iS + "Music"))
		{
			NLMISC::CConfigFile::CVar &plMusic
				= _Config.getVar(iS + "Music");
			_Playlists[i].MusicCount = plMusic.size();
			_Playlists[i].Music = new std::string[_Playlists[i].MusicCount];
			for (uint32 j = 0; j < _Playlists[i].MusicCount; ++j)
				_Playlists[i].Music[j] = plMusic.asString(j);
		}
	}
}
CMusicPlaylistManager::CMusicPlaylistManager(UAudioMixer *audioMixer, const string &configFile, const string &configPrefix)
	: _Current(-1), _CurrentVolume(0.0f), _TargetVolume(0.0f), _TimeVolume(0)
{
	_Config.setConfigFile(configFile, configPrefix);
	init(audioMixer);
}

CMusicPlaylistManager::CMusicPlaylistManager(UAudioMixer *audioMixer, CConfigFile *configFile, const string &configPrefix)
	: _Current(-1), _CurrentVolume(0.0f), _TargetVolume(0.0f), _TimeVolume(0)
{
	_Config.setConfigFile(configFile, configPrefix);
	init(audioMixer);
}

CMusicPlaylistManager::~CMusicPlaylistManager()
{
	_AudioMixer->stopMusic();

	for (uint32 i = 0; i < PlaylistCount; ++i)
	{
		std::string iS = NLMISC::toString("%u_", i);
		_Config.setCallback(iS + "Volume", NULL, NULL, NULL);
		_Config.setCallback(iS + "Fade", NULL, NULL, NULL);
		_Config.setCallback(iS + "Async", NULL, NULL, NULL);
		_Config.setCallback(iS + "Loop", NULL, NULL, NULL);
	}

	delete[] _Playlists;
	_Instance = NULL;
}

CMusicPlaylistManager *CMusicPlaylistManager::getInstance()
{
	nlassert(_Instance != NULL);
	return _Instance;
}

void CMusicPlaylistManager::update(NLMISC::TTime dTime)
{
	// kaetemi_todo: add automatic playlist loop for loop mode 2

	if (_CurrentVolume != _TargetVolume)
	{
		if (_TimeVolume == 0)
		{
			_CurrentVolume = _TargetVolume;
			_AudioMixer->setMusicVolume(_TargetVolume);
		}
		else
		{
			float change = (float)((double)dTime / (double)_TimeVolume);
			if (change > 1.0) { change = 1.0; _TimeVolume = 0; }
			else { _TimeVolume -= (sint32)dTime; }
			change *= _TargetVolume - _CurrentVolume;
			_CurrentVolume += change;
			_AudioMixer->setMusicVolume(_CurrentVolume);
		}
	}
}

void CMusicPlaylistManager::playMusic(sint32 playlist, sint32 track)
{
	if (playlist == -1)
	{
		_AudioMixer->stopMusic(_Playlists[_Current].Fade);
		_Current = playlist;
	}

	if (playlist == _Current && track == _Playlists[_Current].Current) return;
	if (track == -1) track = _Playlists[playlist].Current + 1;

	if (playlist < 0 || playlist >= (sint32)PlaylistCount)
	{
		nlwarning("Music playlist '%i' doesn't exist", playlist);
		return;
	}
	if (track < 0 || track >= (sint32)_Playlists[playlist].MusicCount)
	{
		nlwarning("Track '%i' doesn't exist in music playlist '%i'", track, playlist);
		return;
	}

	if (_Playlists[playlist].Volume > 0.0f)
	{
		std::string trackS = _Playlists[playlist].Music[track];
		_AudioMixer->playMusic(
			_Playlists[playlist].Music[track], 
			getFadeTo(playlist), 
			_Playlists[playlist].Async, 
			_Playlists[playlist].Loop == 1);
		_TargetVolume = _Playlists[playlist].Volume;
		_TimeVolume = _TargetVolume == _CurrentVolume ? 0 : getFadeTo(playlist);
		if (_TimeVolume == 0)
		{
			_CurrentVolume = _TargetVolume;
			_AudioMixer->setMusicVolume(_TargetVolume);
		}
	}
	else
	{
		_AudioMixer->stopMusic(getFadeTo(playlist));
	}

	_Playlists[playlist].Current = track;
	_Current = playlist;
}

sint32 CMusicPlaylistManager::getFadeTo(sint32 playlist)
{
	return _Current == -1 
		? playlist == -1
			? 0 : _Playlists[playlist].Fade
		: playlist == -1
			? 0 : std::min(_Playlists[playlist].Fade, _Playlists[_Current].Fade);
}

void CMusicPlaylistManager::setVolume(sint32 playlist, float volume)
{
	_Playlists[playlist].Volume = volume;
	if (playlist == _Current) _TargetVolume = volume;
	std::string cfgVarVolume = NLMISC::toString("%i_Volume", playlist);
	_Config.getVar(cfgVarVolume).forceAsDouble((double)volume);
}

void CMusicPlaylistManager::fadeVolume(sint32 playlist, float volume)
{
	if (playlist == _Current) _TimeVolume = _Playlists[playlist].Fade;
	setVolume(playlist, volume);
}

void CMusicPlaylistManager::setFade(sint32 playlist, sint32 fade)
{
	_Playlists[playlist].Fade = fade;
	std::string varName = NLMISC::toString("%i_Fade", playlist);
	_Config.getVar(varName).forceAsInt(fade);
}

void CMusicPlaylistManager::setAsync(sint32 playlist, bool async)
{
	_Playlists[playlist].Async = async;
	std::string varName = NLMISC::toString("%i_Async", playlist);
	_Config.getVar(varName).asBool(async);
}

void CMusicPlaylistManager::setLoop(sint32 playlist, uint8 loop)
{
	_Playlists[playlist].Loop = loop;
	std::string varName = NLMISC::toString("%i_Loop", playlist);
	_Config.getVar(varName).forceAsInt(loop);
}

void CMusicPlaylistManager::cbPlaylistVolume(NLMISC::CConfigFile::CVar &var, void *context, void *state)
{
	((CMusicPlaylistManager *)context)
		->fadeVolume(((CPlaylist *)state)->Index, var.asFloat());
}	

void CMusicPlaylistManager::cbPlaylistFade(NLMISC::CConfigFile::CVar &var, void *context, void *state)
{
	((CMusicPlaylistManager *)context)
		->setFade(((CPlaylist *)state)->Index, var.asInt());
}

void CMusicPlaylistManager::cbPlaylistAsync(NLMISC::CConfigFile::CVar &var, void *context, void *state)
{
	((CMusicPlaylistManager *)context)
		->setAsync(((CPlaylist *)state)->Index, var.asBool());
}

void CMusicPlaylistManager::cbPlaylistLoop(NLMISC::CConfigFile::CVar &var, void *context, void *state)
{
	((CMusicPlaylistManager *)context)
		->setLoop(((CPlaylist *)state)->Index, var.asInt());
}

}

#endif 

