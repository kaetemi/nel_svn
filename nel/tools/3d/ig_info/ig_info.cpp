/** \file ig_info.cpp
 * A simple tool to view the content of an ig
 * $Id: ig_info.cpp,v 1.2 2007/03/19 09:55:25 boucher Exp $
 */

/* Copyright, 2000, 2001, 2002 Nevrax Ltd.
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


#include "nel/../../src/3d/scene_group.h"
#include "nel/misc/file.h"
#include "nel/misc/common.h"
#include <string>
#include "stdio.h"

using namespace NL3D;
using namespace NLMISC;
using namespace std;

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage : %s file.ig\n", argv[0]);
		return -1;
	}
	try
	{
		uint k;
		CInstanceGroup ig;
		CIFile inputStream;
		if (!inputStream.open(string(argv[1])))
		{
			printf("unable to open %s\n", argv[1]);
			return -1;
		}
		ig.serial(inputStream);
		printf("Origine\n");
		printf("---------\n");
		CVector gpos = ig.getGlobalPos();
		printf("global pos : x = %.1f, y = %.1f, z =%.1f\n", gpos.x, gpos.y, gpos.z);
		printf("Instances\n");
		printf("---------\n");
		for(k = 0; k < ig._InstancesInfos.size(); ++k)
		{
			printf("instance %s : x = %.1f, y = %.1f, z = %.1f, sx = %.1f, sy = %.1f, sz = %.1f\n", ig._InstancesInfos[k].Name.c_str(), ig._InstancesInfos[k].Pos.x + gpos.x, ig._InstancesInfos[k].Pos.y + gpos.y, ig._InstancesInfos[k].Pos.z + gpos.z, ig._InstancesInfos[k].Scale.x, ig._InstancesInfos[k].Scale.y, ig._InstancesInfos[k].Scale.z);
		}
		printf("\n");
		printf("Lights\n");
		printf("---------\n");
		for(k = 0; k < ig.getNumPointLights(); ++k)
		{
			const CPointLightNamed &pl = ig.getPointLightNamed(k);
			printf("light group = %d, anim = \"%s\" x = %.1f, y = %.1f, z = %.1f\n", pl.LightGroup, pl.AnimatedLight.c_str(), pl.getPosition().x + gpos.x, pl.getPosition().y + gpos.y, pl.getPosition().z + gpos.z);
		}
		printf("---------\n");
		printf("Realtime sun contribution = %s\n", ig.getRealTimeSunContribution() ? "on" : "off");
		printf("---------\n");
		// IGSurfaceLight info.
		const CIGSurfaceLight::TRetrieverGridMap	&rgm= ig.getIGSurfaceLight().getRetrieverGridMap();
		printf("IGSurfaceLighting: CellSize: %f. NumGridRetriever: %d\n", 
			ig.getIGSurfaceLight().getCellSize(), rgm.size() );
		uint	rgmInst= 0;
		uint	totalCells= 0;
		CIGSurfaceLight::TRetrieverGridMap::const_iterator	it= rgm.begin();
		for(;it!=rgm.end();it++)
		{
			for(uint i=0;i<it->second.Grids.size();i++)
			{
				printf("grid(%d, %d): %dx%d\n", rgmInst, i, it->second.Grids[i].Width, it->second.Grids[i].Height );
				totalCells+= it->second.Grids[i].Cells.size();
			}
			rgmInst++;
		}
		printf("TotalCells: %d\n", totalCells);

	}
	catch (std::exception &e)
	{
		printf(e.what());
	}
}
