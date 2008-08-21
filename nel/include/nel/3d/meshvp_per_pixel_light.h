/** \file meshvp_per_pixel_light.h
 * TODO: File description
 *
 * $Id: meshvp_per_pixel_light.h,v 1.5 2005/02/22 10:19:10 besson Exp $
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

#ifndef NL_MESHVP_PER_PIXEL_LIGHT_H
#define NL_MESHVP_PER_PIXEL_LIGHT_H

#include "nel/misc/types_nl.h"
#include "nel/3d/mesh_vertex_program.h"
#include "nel/3d/vertex_program.h"


#include <memory>


namespace NL3D {


/**
 * This vertex program is used to perform perpixel lighting with meshs. Its ouputs are :
 *  
 * Coord Tex 0 : duplicate the tex Coord 0 set from the v.b.
 * Coord Tex 1 : The light vector in tangent space.
 * Coord Tex 2 : The half-angle vector in tangent space.
 *
 * This is designed to work with material that got a 'PerPixelLighting' shader. Note that no bump is used with this shader.
 *
 * It requires that the input mesh has its tangent space first column vector encoded in the 2nd texture coordinate.
 * Other stages are not supported for now.
 *
 * Note that this can be mixed with gouraud rendered light (the gouraud diffuse and specular component are still computed) 
 *
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2002
 */
class CMeshVPPerPixelLight : public IMeshVertexProgram
{
public:
	/// true if want Specular Lighting.
	bool		SpecularLighting;
public:
	CMeshVPPerPixelLight() : SpecularLighting(true), _Enabled(false) {}	
	/// \name IMeshVertexProgram implementation
	// @{	
		virtual	void	initInstance(CMeshBaseInstance *mbi);
		virtual	bool	begin(IDriver *drv,
							  CScene *scene,
							  CMeshBaseInstance *mbi,
							  const NLMISC::CMatrix &invertedModelMat,
							  const NLMISC::CVector &viewerPos);			
		virtual	void	end(IDriver *drv);				
		virtual void	serial(NLMISC::IStream &f) throw(NLMISC::EStream);				
		virtual void	setupForMaterial(const CMaterial &mat,
										 IDriver *drv,
										 CScene *scene,
										 CVertexBuffer *vb
										);
		virtual	bool	needTangentSpace() const { return true; }
		NLMISC_DECLARE_CLASS(CMeshVPPerPixelLight);
	// @}			
private:
	// enable / disable this v.p
	void	enable(bool enabled, IDriver *drv);
private:	
	// this setup the material, and returns true if the v.p has been enabled / disabled
	virtual bool	setupForMaterial(const CMaterial &mat,
									 IDriver *drv,
									 CScene *scene
									);
	bool	_Enabled;	
	bool	_IsPointLight;
	//
	enum { NumVp = 8};	
	static	std::auto_ptr<CVertexProgram>	_VertexProgram[NumVp];
};

} // NL3D


#endif // NL_MESHVP_PER_PIXEL_LIGHT_H

/* End of meshvp_per_pixel_light.h */
