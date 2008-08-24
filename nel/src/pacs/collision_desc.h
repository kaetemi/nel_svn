/** \file collision_desc.h
 * Description of the contact of a collision
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

#ifndef NL_COLLISION_DESC_H
#define NL_COLLISION_DESC_H

#include "nel/misc/types_nl.h"
#include "nel/misc/file.h"
#include "nel/misc/vector.h"
#include "nel/pacs/u_collision_desc.h"
#include <vector>

namespace NLPACS
{

/**
 * Description of the contact of a collision
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class CCollisionDesc: public UCollisionDesc
{
public:
	// XChg contact normal 0 and 1
	void XChgContactNormals ()
	{
		NLMISC::CVectorD tmp=ContactNormal0;
		ContactNormal0=ContactNormal1;
		ContactNormal1=tmp;
	}
};


/**
 * Ident of a surface.
 *
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CSurfaceIdent
{
public:
	/// the surface mesh instance Id.
	sint32				RetrieverInstanceId;
	/// the surface Id of this surface mesh instance. -1 if Wall/impossible to walk through.
	sint32				SurfaceId;

	bool operator==(const CSurfaceIdent &o) const
	{
		return RetrieverInstanceId==o.RetrieverInstanceId && SurfaceId==o.SurfaceId;
	}

	bool operator!=(const CSurfaceIdent &o) const
	{
		return !(*this==o);
	}


public:
	CSurfaceIdent() {}
	CSurfaceIdent(sint32 retInstance, sint32 surfId) : RetrieverInstanceId(retInstance), SurfaceId(surfId) {}

	void				serial(NLMISC::IStream &f)	{ f.serial(RetrieverInstanceId, SurfaceId); }
};


/**
 * Description of the contact of a collision against a surface (interior/zones).
 *
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CCollisionSurfaceDesc
{
public:
	NLMISC::CVectorD	ContactNormal;
	double				ContactTime;

	/// To which surface we have collided.
	CSurfaceIdent		ContactSurface;
};


typedef	std::vector<CCollisionSurfaceDesc>	TCollisionSurfaceDescVector;



} // NLPACS


#endif // NL_COLLISION_DESC_H

/* End of collision_desc.h */
