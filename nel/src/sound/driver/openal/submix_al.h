/**
 * \file submix_al.h
 * \brief CSubmixAl
 * \date 2008-09-15 23:09GMT
 * \author Jan Boon (Kaetemi)
 * CSubmixAl
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

#ifndef NLSOUND_SUBMIX_AL_H
#define NLSOUND_SUBMIX_AL_H
#include <nel/misc/types_nl.h>

// STL includes

// NeL includes

// Project includes

namespace NLSOUND {

/**
 * \brief CSubmixAl
 * \date 2008-09-15 23:09GMT
 * \author Jan Boon (Kaetemi)
 * CSubmixAl
 */
class CSubmixAl : public ISubmix
{
protected:
	// outside pointers
	IEffect *_Effect;
	
	// instances
	ALuint _AlAuxEffectSlot;
public:
	CSubmixAl(ALuint alEfxObject);
	virtual ~CSubmixAl();

	inline ALuint getAlEfxObject() { return _AlAuxEffectSlot; }

	virtual void setEffect(IEffect *effect);
	virtual void setGain(float gain);
}; /* class CSubmixAl */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_SUBMIX_AL_H */

/* end of file */
