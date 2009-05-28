/** \file u_cloud_scape.h
 * User interface for cloud scape manipulation
 */

/* Copyright, 2000, 2002 Nevrax Ltd.
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

#ifndef NL_U_CLOUD_SCAPE_H
#define NL_U_CLOUD_SCAPE_H

#include "nel/misc/types_nl.h"


namespace NLMISC
{
	class CVector2f;
	class CVector;
};


namespace NL3D {

class UDriver;
class UCamera;

// ------------------------------------------------------------------------------------------------
struct SCloudScapeSetup
{
	float	TimeToChange;
	float	WindSpeed;	// Speed the cloud move (along x axis)
	float	CloudSpeed; // Speed the cloud change
	uint32	NbCloud;
	NLMISC::CRGBA	Ambient;
	NLMISC::CRGBA	Diffuse;

	SCloudScapeSetup ()
	{
		TimeToChange = 120.0f;
		WindSpeed = 2.0f;
		CloudSpeed = 5.0f;
		NbCloud = 25;
		Ambient = NLMISC::CRGBA (120,140,160,255);
		Diffuse = NLMISC::CRGBA (255,255,255,255);
	}
};

/**
 * \author Matthieu 'Trap' Besson
 * \author Nevrax France
 * \date 2002
 */
// ------------------------------------------------------------------------------------------------
class UCloudScape
{
public:

	UCloudScape () {}
	virtual	~UCloudScape () {}

	virtual void init (SCloudScapeSetup *pCSS = NULL) = 0;

	virtual void set (SCloudScapeSetup &css) = 0;

	virtual void anim (double dt) = 0;

	virtual void render () = 0;

	virtual uint32 getMemSize() = 0;

	virtual void setQuality (float threshold) = 0;

	virtual void setNbCloudToUpdateIn80ms (uint32 n) = 0;

	virtual bool isDebugQuadEnabled () = 0;

	virtual void setDebugQuad (bool b) = 0;

};



} // NL3D


#endif // NL_U_CLOUD_SCAPE_H

/* End of u_cloud_scape.h */
