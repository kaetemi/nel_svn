/** \file u_primitive_block.h
 */

/* Copyright, 2000, 2001, 2002 Nevrax Ltd.
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

#ifndef NL_U_PRIMITIVE_BLOCK_H
#define NL_U_PRIMITIVE_BLOCK_H

#include <string>
#include "nel/pacs/u_move_primitive.h"

namespace NLMISC
{
	class IStream;
}

namespace NLPACS
{

/**
 * Block of pacs primitives, user interface.
 * They can be created from a stream (*.pacs_prim)
 * A primitive block can be instanciated in a move container.
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2002
 */
class UPrimitiveBlock
{
public:
	// dtor
	virtual ~UPrimitiveBlock() {}
	/** Create a primitive block from a stream.
	  * This may raise exception if loading failed
	  */
	static UPrimitiveBlock *createPrimitiveBlock(NLMISC::IStream &src);
	/** Create a primitive block from its file name.
	  * This may raise exceptions if loading failed.
	  */
	static UPrimitiveBlock *createPrimitiveBlockFromFile(const std::string &fileName);

	/// get the number of primitives in the block
	virtual uint						getNbPrimitive() = 0;

	/// return the user data for a primitive of the block
	virtual UMovePrimitive::TUserData	getUserData(uint nPrimNb) = 0;
};

}

#endif





