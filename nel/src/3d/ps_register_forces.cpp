/** \file ps_register_forces.cpp
 * 
 *
 * $Id: ps_register_forces.cpp,v 1.3 2005/02/22 10:19:11 besson Exp $
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


#include "ps_util.h"
#include "ps_force.h"



namespace NL3D
{
	void CPSUtil::registerForces()
	{
			NLMISC_REGISTER_CLASS(CPSSpring);
		NLMISC_REGISTER_CLASS(CPSDirectionnalForce); 
		NLMISC_REGISTER_CLASS(CPSGravity); 
		NLMISC_REGISTER_CLASS(CPSBrownianForce);
		NLMISC_REGISTER_CLASS(CPSCentralGravity); 
		NLMISC_REGISTER_CLASS(CPSFluidFriction);
		NLMISC_REGISTER_CLASS(CPSTurbul);
		NLMISC_REGISTER_CLASS(CPSCylindricVortex);
		NLMISC_REGISTER_CLASS(CPSMagneticForce);
		CPSBrownianForce::initPrecalc();
	}
} // NL3D
