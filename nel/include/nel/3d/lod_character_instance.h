/** \file lod_character_instance.h
 * TODO: File description
 *
 * $Id: lod_character_instance.h,v 1.3 2004/11/15 10:24:41 lecroart Exp $
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#ifndef NL_LOD_CHARACTER_INSTANCE_H
#define NL_LOD_CHARACTER_INSTANCE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/uv.h"
#include "nel/misc/rgba.h"
#include "nel/3d/animation_time.h"


namespace NL3D 
{


using NLMISC::CRGBA;
using NLMISC::CUV;


class CLodCharacterManager;


// ***************************************************************************
/**
 * An instance of a lodCharacter (stored in CSkeletonModel).
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CLodCharacterInstance
{
public:
	/// shapeId is the id of the lod character shape to use. No-Op if not found.
	sint					ShapeId;	// -1 if disabled
	/// animId is the anim to use for this shape. No-Op if not found.
	uint					AnimId;
	/// time is the time of animation
	TGlobalAnimationTime	AnimTime;
	/// wrapMode if true, the anim loop, else just clamp
	bool					WrapMode;

	/** The precomputed alpha array
	 *	must be same size of the shape number vertices, else the
	 *	whole mesh is supposed to be opaque. see CLodCharacterShape::startBoneAlpha() for how to build this array
	 */
	std::vector<uint8>		VertexAlphas;

public:
	CLodCharacterInstance()
	{
		ShapeId= -1;
		AnimId= 0;
		AnimTime= 0;
		WrapMode= true;
		_TextureId= -1;
		_Owner= NULL;
	}

	~CLodCharacterInstance();

	/// get a ptr on the UVs.
	const CUV		*getUVs() const;

// ***************
private:
	friend class CLodCharacterManager;

	// The manager which owns us. Filled by CLodCharacterManager.
	CLodCharacterManager	*_Owner;
	// The id of the texture the manager gives to us. Filled by CLodCharacterManager.
	sint					_TextureId;
	/// The precomputed UVs. Filled by CLodCharacterManager.
	std::vector<CUV>		_UVs;

};



} // NL3D


#endif // NL_LOD_CHARACTER_INSTANCE_H

/* End of lod_character_instance.h */
