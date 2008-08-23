/** \file root_model.h
 * TODO: File description
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

#ifndef NL_ROOT_MODEL_H
#define NL_ROOT_MODEL_H

#include "nel/misc/types_nl.h"
#include "nel/3d/transform.h"


namespace NL3D {


// ***************************************************************************
// ClassIds.
const NLMISC::CClassId		RootModelId=NLMISC::CClassId(0x25f0505d, 0x75c69f9);


// ***************************************************************************
/**
 * The purpose of this model is to do nothing in traverse*() but traverseSons() for Hrc and Clip
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CRootModel : public CTransform
{
public:
	/// Call at the begining of the program, to register the model
	static	void	registerBasic();


	/// \name CTransform traverse specialisation
	// @{
	virtual void	traverseHrc();
	virtual void	traverseClip();
	virtual void	traverseAnimDetail();
	virtual void	traverseLoadBalancing();
	virtual void	traverseLight();
	virtual void	traverseRender();
	// @}


protected:
	/// Constructor
	CRootModel() {}
	/// Destructor
	virtual ~CRootModel() {}

private:
	static CTransform	*creator() {return new CRootModel;}

};


} // NL3D


#endif // NL_ROOT_MODEL_H

/* End of root_model.h */
