/** \file ps_register_particles.cpp
 * 
 *
 * $Id: ps_register_particles.cpp,v 1.4 2005/02/22 10:19:11 besson Exp $
 */
/* Copyright, 2002 Nevrax Ltd.
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

#include "std3d.h"


#include "nel/3d/ps_util.h"
#include "nel/3d/ps_particle.h"
#include "nel/3d/ps_particle2.h"
#include "nel/3d/ps_mesh.h"


namespace NL3D
{
	void CPSUtil::registerParticles()
	{
		NL_PS_FUNC(	CPSUtil_registerParticles)
		NLMISC_REGISTER_CLASS(CPSFanLight);
		NLMISC_REGISTER_CLASS(CPSTailDot);
		NLMISC_REGISTER_CLASS(CPSRibbon);
		NLMISC_REGISTER_CLASS(CPSRibbonLookAt);
		NLMISC_REGISTER_CLASS(CPSShockWave);
		NLMISC_REGISTER_CLASS(CPSFace);
		NLMISC_REGISTER_CLASS(CPSMesh);
		NLMISC_REGISTER_CLASS(CPSConstraintMesh);
		NLMISC_REGISTER_CLASS(CPSDot);
		NLMISC_REGISTER_CLASS(CPSFaceLookAt);

		CPSRotated2DParticle::initRotTable(); // init the precalc rot table for face lookat
		CPSFanLight::initFanLightPrecalc();
		CPSDot::initVertexBuffers();
		CPSQuad::initVertexBuffers();
		CPSConstraintMesh::initPrerotVB();
	}
} // NL3D
