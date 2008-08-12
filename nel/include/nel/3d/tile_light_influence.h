/** \file tile_light_influence.h
 * TODO: File description
 *
 * $Id: tile_light_influence.h,v 1.2 2004/11/15 10:24:50 lecroart Exp $
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

#ifndef NL_TILE_LIGHT_INFLUENCE_H
#define NL_TILE_LIGHT_INFLUENCE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"


namespace NL3D 
{


/**
 *	For landscape.
 *	A descriptor of light which influence a corner of a TessBlock:
 *		2 lights Ids (points to PointLight in zone), with 2 diffuseLightFactor.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CTileLightInfluence
{
public:

	/// We support only 2 light per corner. Should never be changed.
	enum	{NumLightPerCorner= 2};

public:
	/// Constructor
	CTileLightInfluence() {}


	/** List of lights.
	 *	Id==0xFF => no light. if Light[i]==0xFF, then Light[j] with j>i is supposed disalbed too.
	 */
	uint8			Light[NumLightPerCorner];

	/// i: 0 or 1. factor E [0..255] is the factor of influence (gouraud) of the ith light. NB: stored on 4 bits.
	void			setDiffuseLightFactor(uint i, uint8 factor);
	/// see setDiffuseLightFactor(). return uint8 E [0, 255]
	uint8			getDiffuseLightFactor(uint i) const;


	void			serial(NLMISC::IStream &f);


private:

	/// Packed
	uint8			PackedLightFactor;

};


} // NL3D


#endif // NL_TILE_LIGHT_INFLUENCE_H

/* End of tile_light_influence.h */
