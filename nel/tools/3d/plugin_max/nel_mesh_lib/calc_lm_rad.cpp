/** \file calc_lm_rad.cpp
 * extension of the lightmapper with radiosity
 *
 * $Id: calc_lm_rad.cpp,v 1.3 2002/08/27 14:36:25 corvazier Exp $
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

#include "stdafx.h"
#include "export_nel.h"

using namespace NL3D;

bool CExportNel::calculateLMRad( CMesh::CMeshBuild *pZeMeshBuild, CMeshBase::CMeshBaseBuild *pZeMeshBaseBuild, INode& ZeNode, 
							TimeValue tvTime)
{
	return true;
}