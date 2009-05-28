/** \file u_shape.h
 * Game interface for managing shape.
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

#ifndef NL_U_SHAPE_H
#define NL_U_SHAPE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"
#include "u_material.h"
#include <vector>


namespace NL3D
{

class	UVisualCollisionMesh;

// ***************************************************************************
/**
 * Game interface for managing shape.
 *	NB: unlike old GameInterface, here the UShape is a Proxy: it keep a ptr on a IShape, thus
 *	it can be created or destroyed statically, on the stack etc...
 *
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class UShape
{
public:

	/** Get the mesh under Triangle Form.
	 *	For now only CMesh and CMeshMultiLod (CMeshGeom only) are supported.
	 *	Warning! return false if the Mesh has already been rendered!! (VertexBuffer resident)
	 *	\param vertices array of vertices
	 *	\param indices triplets of indices to vertices
	 *	\return false if cannot be converted.
	 */
	bool			getMeshTriangles(std::vector<NLMISC::CVector> &vertices, std::vector<uint32> &indices) const;

	/** Return a Visual Collision Mesh if the shape has one (else return empty one)
	 *	For now return someting if Mesh / MeshMultiLod with some lightmap only (supposed big meshs)!
	 */
	void			getVisualCollisionMesh(UVisualCollisionMesh	&colMesh) const;

	/// \name Material access.
	// @{
	/** return number of materials this mesh instance use.
	 *	return 0 if not supported (not a CMeshBase)
	 */
	uint			getNumMaterials() const;
	/** return a local access on a material, typically to get diffuse etc...
	 *	return NULL if not supported (not a CMeshBase) or if materialId is too big
	 *	You should typically just read material values since some mutators (selectTextureSet...) may lead
	 *	to undefined behaviors
	 */
	UMaterial		getMaterial(uint materialId) const;
	// @}

	// Return the Default setup choosed for this shape, for UInstance::setOpacity(). return false if not supported (not a CMeshBase)
	bool			getDefaultOpacity() const;

	// Return the Default setup computed for this shape, for UInstance::setTransparency(). return false if not supported (not a CMeshBase)
	bool			getDefaultTransparency() const;


	/// Proxy interface

	/// Constructors
	UShape() { _Object = NULL; }
	UShape(class IShape *object) { _Object = object; }
	/// Attach an object to this proxy
	void			attach(class IShape *object) { _Object = object; }
	/// Detach the object
	void			detach() { _Object = NULL; }
	/// Return true if the proxy is empty() (not attached)
	bool			empty() const {return _Object==NULL;}
	/// For advanced usage, get the internal object ptr
	class IShape	*getObjectPtr() const {return _Object;}

private:
	class IShape	*_Object;
};


} // NL3D


#endif // NL_U_SHAPE_H

/* End of u_shape_bank.h */
