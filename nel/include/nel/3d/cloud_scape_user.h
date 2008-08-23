/** \file cloud_scape_user.h
 * 
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#include "nel/3d/u_cloud_scape.h"

namespace NL3D 
{

class UDriver;
class UCamera;
class CCloudScape;

/// implementation of UWaterInstance methods
class CCloudScapeUser : public UCloudScape
{
public:		

	CCloudScapeUser(CScene *scene);
	virtual	~CCloudScapeUser();

	virtual void init (SCloudScapeSetup *pCSS = NULL);

	virtual void set (SCloudScapeSetup &css);

	virtual void anim (double dt);

	virtual void render ();

	virtual uint32 getMemSize();

	virtual void setQuality (float threshold);

	virtual void setNbCloudToUpdateIn80ms (uint32 n);

	virtual bool isDebugQuadEnabled ();
	
	virtual void setDebugQuad (bool b);

	CCloudScape *_CS;
	CScene *_Scene;
};


} // NL3D

