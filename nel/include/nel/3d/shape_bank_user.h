/** \file shape_bank_user.h
 * Implementation of the user interface managing shape bank.
 *
 * $Id: shape_bank_user.h,v 1.9 2005/03/10 17:27:04 berenguier Exp $
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

#ifndef NL_SHAPE_BANK_USER_H
#define NL_SHAPE_BANK_USER_H

#include "nel/misc/types_nl.h"
#include "nel/3d/u_shape_bank.h"
#include "shape_bank.h"

#define NL3D_MEM_SHAPE_BANK					NL_ALLOC_CONTEXT( 3dShpBk )

namespace NL3D 
{

class CDriverUser;
/**
 * Implementation of the user interface managing shape bank
 *
 * \author Matthieu Besson
 * \author Nevrax France
 * \date 2001
 */
class CShapeBankUser : public UShapeBank
{
public:
	virtual ~CShapeBankUser() 
	{
		NL3D_MEM_SHAPE_BANK
	}

	virtual void addShapeCache(const std::string &shapeCacheName);
	virtual void removeShapeCache(const std::string &shapeCacheName);
	virtual void reset();
	virtual void setShapeCacheSize(const std::string &shapeCacheName, sint32 maxSize);
	virtual void linkShapeToShapeCache(const std::string &shapeName, const std::string &shapeCacheName);
	virtual void	preLoadShapesFromDirectory(const std::string &shapeCacheName, 
		const std::string &path, const std::string &wildCard, bool recurs, NLMISC::IProgressCallback *progress = NULL, bool flushTextures = false);
	virtual void	preLoadShapesFromBNP(const std::string &shapeCacheName, 
		const std::string &bnpName, const std::string &wildCard, NLMISC::IProgressCallback *progress = NULL, bool flushTextures = false);
	virtual UShape	getShape(const std::string &shapeName);
	virtual void	buildSystemGeometryForshape(const std::string &shapeName);
	
	// The real shape bank
	CShapeBank _ShapeBank;
	CDriverUser *_DriverUser;
};


} // NL3D


#endif // NL_SHAPE_BANK_USER_H

/* End of shape_bank_user.h */
