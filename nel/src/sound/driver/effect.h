/**
 * \file effect.h
 * \brief IEffect
 * \date 2008-09-15 22:27GMT
 * \author Jan Boon (Kaetemi)
 * IEffect
 */

/* 
 * Copyright (C) 2008  by authors
 * 
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 2 of the License,
 * or (at your option) any later version.
 * 
 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 */

#ifndef NLSOUND_EFFECT_H
#define NLSOUND_EFFECT_H
#include <nel/misc/types_nl.h>

// STL includes

// NeL includes

// Project includes

namespace NLSOUND {

/**
 * \brief IEffect
 * \date 2008-09-15 22:27GMT
 * \author Jan Boon (Kaetemi)
 * IEffect
 */
class IEffect
{
public:
	enum TEffectType
	{
		Reverb
	};

	IEffect();
	virtual ~IEffect();

	virtual TEffectType getType() = 0;
}; /* class IEffect */

/**
 * \brief IReverb
 * \date 2008-09-15 22:27GMT
 * \author Jan Boon (Kaetemi)
 * IReverb
 */
class IReverb : public IEffect
{
public:
	class CEnvironment
	{

	};

	IReverb();
	virtual ~IReverb();

	virtual void setEnvironment(const CEnvironment &environment) = 0;
	virtual void setRoomSize(float roomSize) = 0;
}; /* class IReverb */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_EFFECT_H */

/* end of file */
