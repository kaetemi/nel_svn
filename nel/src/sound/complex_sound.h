/** \file complex_sound.h
 *
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

#ifndef NL_COMPLEX_SOUND_H
#define NL_COMPLEX_SOUND_H

#include "nel/misc/types_nl.h"
#include "nel/misc/string_mapper.h"
#include "sound.h"
#include <string>

namespace NLSOUND
{

class ISoundController;


typedef std::basic_string<uint16>	uint16_string;


class CComplexSound : public CSound
{
public:

	enum TPATTERN_MODE
	{
		MODE_UNDEFINED,
		MODE_CHAINED,
		MODE_ALL_IN_ONE,
		MODE_SPARSE
	};

	bool							isDetailed() const;
	uint32							getDuration();


	TPATTERN_MODE					getPatternMode()							{ return _PatternMode;}
	void							setPatternMode(TPATTERN_MODE patternMode)	{ _PatternMode = patternMode;}

	const std::vector<uint32>		&getSoundSeq() const						{ return _SoundSeq;}
	const std::vector<uint32>		&getDelaySeq() const						{ return _DelaySeq;}
	NLMISC::TStringId				getSound(uint index) const					{ return !_Sounds.empty() ? _Sounds[index%_Sounds.size()]:0;}
	const std::vector<NLMISC::TStringId>	&getSounds() const					{ return _Sounds;}

	uint32							getFadeLenght() const						{ return _XFadeLenght;}

	/** Constructor */
	CComplexSound();

	/** Destructor */
	virtual ~CComplexSound();

	/// Load the sound parameters from georges' form
	virtual void					importForm(const std::string& filename, NLGEORGES::UFormElm& formRoot);

	/// \name Tempo
	//@{
	virtual float					getTicksPerSecond()							{ return _TicksPerSeconds; }
	virtual void					setTicksPerSecond(float ticks)				{ _TicksPerSeconds = ticks; }
	//@}

	TSOUND_TYPE						getSoundType() {return SOUND_COMPLEX;};

	void							getSubSoundList(std::vector<std::pair<std::string, CSound*> > &subsounds) const;
	bool							doFadeIn()								{ return _DoFadeIn; }
	bool							doFadeOut()								{ return _DoFadeOut; }

	void							serial(NLMISC::IStream &s);


private:

	void							parseSequence(const std::string &str, std::vector<uint32> &seq, uint scale = 1);
	virtual float					getMaxDistance() const;

	TPATTERN_MODE					_PatternMode;
	std::vector<NLMISC::TStringId>	_Sounds;
	float							_TicksPerSeconds;
	std::vector<uint32>				_SoundSeq;
	/// Sequence of delay in millisec.
	std::vector<uint32>			_DelaySeq;

	/// Duration of xfade in millisec.
	uint32						_XFadeLenght;
	/// Flag for fade in
	bool						_DoFadeIn;
	/// Flag for fade out (only on normal termination, not explicit stop).
	bool						_DoFadeOut;

	mutable bool				_MaxDistValid;

	// Duration of sound.
	uint32						_Duration;
	// flag for validity of duration (after first evaluation).
	bool						_DurationValid;
};

} // namespace

#endif // NL_COMPLEX_SOUND_H

