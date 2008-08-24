/** \file simple_sound.cpp
 * CSound: a sound buffer and its static properties
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

#include "nel/misc/path.h"
#include "simple_sound.h"
#include "sound_bank.h"
#include "sample_bank.h"
#include "driver/sound_driver.h"
#include "driver/buffer.h"

using namespace std;
using namespace NLMISC;


namespace NLSOUND {


/*
 * Constructor
 */
CSimpleSound::CSimpleSound() :
	_Registered(false),
	_Buffer(NULL),
	_Detailed(false),
	_MinDist(1.0f),
	_NeedContext(false)
{
	// init with NULL in case of unexecpted access
	_Filename= NULL;
	_Buffername= NULL;
}


/*
 * Destructor
 */
CSimpleSound::~CSimpleSound()
{
	if (_Buffer != NULL)
		CSoundBank::instance()->unregisterBufferAssoc(this, _Buffer);
}

void CSimpleSound::setBuffer(IBuffer *buffer)
{
	if (_Buffer != NULL && buffer != NULL && _Buffer->getName() != buffer->getName())
	{
		// if buffer name change, update the registration/
		CSoundBank::instance()->unregisterBufferAssoc(this, _Buffer);
		CSoundBank::instance()->registerBufferAssoc(this, buffer);
	}
	else if (!_Registered && buffer != NULL)
	{
		// creater initial registration.
		CSoundBank::instance()->registerBufferAssoc(this, buffer);
		_Registered = true;
	}
	_Buffer = buffer;
}


void				CSimpleSound::getSubSoundList(std::vector<std::pair<std::string, CSound*> > &subsounds) const
{
	// A little hack, we use the reference vector to tag unavailable sample.
	if (!(_Buffername == CStringMapper::emptyId()) && const_cast<CSimpleSound*>(this)->getBuffer() == 0)
		subsounds.push_back(pair<string, CSound*>(CStringMapper::unmap(_Buffername)+" (sample)", 0));
}


/*
 * Return the sample buffer of this sound
 */
IBuffer*			CSimpleSound::getBuffer()
{
	if (_Buffer == 0)
	{
		// try to find the sample buffer in the sample bank.
		_Buffer = CSampleBank::get(_Buffername);
		CSoundBank::instance()->registerBufferAssoc(this, _Buffer);
		_Registered = true;
	}
	return _Buffer;
}


/*
 * Return the length of the sound in ms
 */
uint32				CSimpleSound::getDuration()
{
	IBuffer* buffer = getBuffer();

	if ( buffer == NULL )
	{
		return 0;
	}
	else
	{
		return (uint32)(buffer->getDuration());
	}
}


void				CSimpleSound::serial(NLMISC::IStream &s)
{
	std::string bufferName;
	CSound::serial(s);

	s.serial(_MinDist);
	s.serial(_Alpha);

	if (s.isReading())
	{
		s.serial(bufferName);
		_Buffername = CStringMapper::map(bufferName);
		setBuffer(NULL);

		// contain % so it need a context to play
		if (bufferName.find ("%") != string::npos)
		{
			_NeedContext = true;
		}
	}
	else
	{
		bufferName = CStringMapper::unmap(_Buffername);
		s.serial(bufferName);
	}
}


/**
 * 	Load the sound parameters from georges' form
 */
void				CSimpleSound::importForm(const std::string& filename, NLGEORGES::UFormElm& root)
{
	NLGEORGES::UFormElm *psoundType;
	std::string dfnName;

	// some basic checking.
	root.getNodeByName(&psoundType, ".SoundType");
	nlassert(psoundType != NULL);
	psoundType->getDfnName(dfnName);
	nlassert(dfnName == "simple_sound.dfn");

	// Call the base class
	CSound::importForm(filename, root);

	// Name
	_Filename = CStringMapper::map(filename);

	// Buffername
	std::string bufferName;
	root.getValueByName(bufferName, ".SoundType.Filename");
	bufferName = CFile::getFilenameWithoutExtension(bufferName);
	_Buffername = CStringMapper::map(bufferName);

	setBuffer(NULL);

	// contain % so it need a context to play
	if (bufferName.find ("%") != string::npos)
	{
		_NeedContext = true;
	}

	// MaxDistance
 	root.getValueByName(_MaxDist, ".SoundType.MaxDistance");

	// MinDistance
	root.getValueByName(_MinDist, ".SoundType.MinDistance");

	// Alpha
	root.getValueByName(_Alpha, ".SoundType.Alpha");

}

} // NLSOUND
