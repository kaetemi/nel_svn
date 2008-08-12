/** \file vegetable_blend_layer_model.h
 * TODO: File description
 *
 * $Id: vegetable_blend_layer_model.h,v 1.7 2005/02/22 10:19:12 besson Exp $
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

#ifndef NL_VEGETABLE_BLEND_LAYER_MODEL_H
#define NL_VEGETABLE_BLEND_LAYER_MODEL_H

#include "nel/misc/types_nl.h"
#include "transform.h"


namespace	NL3D
{


class	CVegetableManager;
class	CVegetableSortBlock;
class	IDriver;


// ***************************************************************************
// ClassIds.
const NLMISC::CClassId		VegetableBlendLayerModelId=NLMISC::CClassId(0x77375163, 0x2fca1003);


// ***************************************************************************
/**
 * A CVegetableBlendLayerModel does not have to be created by user. It is an internal class of CVegetableManager.
 *	It is used to draw AlphaBlend ZSort rdrPass vegetables. Thoses vegetables are rendered in separate Z ordered 
 *	layer, so transparency with other transparents objects is well performed (as best as it can).
 *
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CVegetableBlendLayerModel : public CTransform
{
public:
	/// Call at the begining of the program, to register the model
	static	void	registerBasic();

public:

	/** The vegetableManager which create us, and will delete us.
	 */
	CVegetableManager		*VegetableManager;


	/** Public (for vegetableManager only!!) list of vegetable SortBlocks to render.
	 *	this is a vector<> because not so much reallocation, and it is just an array of ptrs, so
	 *	very little memory load.
	 */
	std::vector<CVegetableSortBlock*>		SortBlocks;


	/** Ugly but it works: setup directly both the worldMatrix and the localMatrix.
	 *	NB: LayerModels are always created in the root.
	 */
	void		setWorldPos(const CVector &pos);


	/// \name CTransform traverse specialisation
	// @{
	virtual	bool	clip()
	{
		return true;
	}
	virtual void	traverseRender();
	// @}

protected:
	/// Constructor
	CVegetableBlendLayerModel();
	/// Destructor
	virtual ~CVegetableBlendLayerModel() {}


private:
	static CTransform	*creator() {return new CVegetableBlendLayerModel();}

	/// render method
	void			render(IDriver *driver);

};


} // NL3D


#endif // NL_VEGETABLE_BLEND_LAYER_MODEL_H

/* End of vegetable_blend_layer_model.h */
