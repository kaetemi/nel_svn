/** \file primitive_block.h
 * Block of PACS primitive
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

#ifndef NL_PRIMITIVE_BLOCK_PACS_H
#define NL_PRIMITIVE_BLOCK_PACS_H

#include "nel/misc/types_nl.h"
#include "nel/pacs/u_move_primitive.h"
#include "nel/pacs/u_primitive_block.h"


namespace NLPACS
{

/**
 * PACS primitive description
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2002
 */
class CPrimitiveDesc
{
public:

	// Default constructor
	CPrimitiveDesc ();

	// The length of the 4 edges. The first is the width, the second is the depth
	// For cylinder, the first is the radius
	float							Length[2];

	// This is the height of the box or of the cylinder.
	float							Height;

	// Attenuation
	float							Attenuation;

	// Primitive type
	UMovePrimitive::TType			Type;

	// Reaction type
	UMovePrimitive::TReaction		Reaction;

	// Reaction type
	UMovePrimitive::TTrigger		Trigger;

	// Obstacle flag
	bool							Obstacle;

	// Occlusion mask
	UMovePrimitive::TCollisionMask	OcclusionMask;

	// Collision mask
	UMovePrimitive::TCollisionMask	CollisionMask;

	// Position of the primitive
	NLMISC::CVector					Position;

	// Orientation of the primitive
	float							Orientation;

	// User data
	UMovePrimitive::TUserData		UserData;

	// Serial methods
	void serial (NLMISC::IStream &s);
};

/**
 * Block of pacs primitive
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2002
 */
class CPrimitiveBlock	: public UPrimitiveBlock
{
public:

	// Array of primitives
	std::vector<CPrimitiveDesc>		Primitives;

	// Serial methods
	void serial (NLMISC::IStream &s);

	///\name from UPrimitive block, create a P.B. from a stream
	//@{
	static UPrimitiveBlock *createPrimitiveBlock(NLMISC::IStream &src);
	static UPrimitiveBlock *createPrimitiveBlockFromFile(const std::string &fileName);
	uint						getNbPrimitive() { return Primitives.size(); }
	UMovePrimitive::TUserData	getUserData(uint nPrimNb) { nlassert(nPrimNb < Primitives.size());
															return Primitives[nPrimNb].UserData; }
	//@}
};


} // NLPACS


#endif // NL_PRIMITIVE_BLOCK_PACS_H

/* End of primitive_block.h */
