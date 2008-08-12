/** \file zone_dump.cpp
 * zone_dump.cpp : Very simple zone dumper
 *
 * $Id: zone_dump.cpp,v 1.3 2005/02/08 15:31:34 lecroart Exp $
 */

/* Copyright, 2000 Nevrax Ltd.
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

#include "nel/misc/stream.h"
#include "nel/misc/file.h"
#include "nel/misc/vector.h"
#include "nel/misc/time_nl.h"
#include "3d/zone.h"
#include "3d/landscape.h"
#include "nel/misc/triangle.h"
#include "../zone_lib/zone_utility.h"	// load a header file from zone_welder project

#include <stdio.h>
#include <float.h>

using namespace std;
using namespace NLMISC;
using namespace NL3D;

void	buildFaces(CLandscape& landscape, sint zoneId, sint patch, std::vector<CTriangle> &faces)
{
	faces.clear();

	CZone* pZone=landscape.getZone (zoneId);

	// Then trace all patch.
	sint	N= pZone->getNumPatchs();
	nlassert(patch>=0);
	nlassert(patch<N);
	const CPatch	*pa= const_cast<const CZone*>(pZone)->getPatch(patch);

	// Build the faces.
	//=================
	sint	ordS= 4*pa->getOrderS();
	sint	ordT= 4*pa->getOrderT();
	sint	x,y;
	float	OOS= 1.0f/ordS;
	float	OOT= 1.0f/ordT;
	for(y=0;y<ordT;y++)
	{
		for(x=0;x<ordS;x++)
		{
			CTriangle	f;
			f.V0= pa->computeVertex(x*OOS, y*OOT);
			f.V1= pa->computeVertex(x*OOS, (y+1)*OOT);
			f.V2= pa->computeVertex((x+1)*OOS, (y+1)*OOT);
			faces.push_back(f);
			f.V0= pa->computeVertex(x*OOS, y*OOT);
			f.V1= pa->computeVertex((x+1)*OOS, (y+1)*OOT);
			f.V2= pa->computeVertex((x+1)*OOS, y*OOT);
			faces.push_back(f);
		}
	}
}

int main(int argc, char* argv[])
{
	try
	{
		// Good number of args ?
		if (argc!=4)
		{
			// Help message
			printf ("zone_dump [first_zone.zone] [last_zone.zone] [output.dump]\n");
			printf ("Dump file format:\n");
			printf ("\t4 bytes: number of triangles\n");
			printf ("\tfor each triangles:\n");
			printf ("\t\t3 floats, X, Y, Z for Vertex 0\n");
			printf ("\t\t3 floats, X, Y, Z for Vertex 1\n");
			printf ("\t\t3 floats, X, Y, Z for Vertex 2\n");
			printf ("\t\tVertices are CCW, in a right hand basis with Z axis to the top\n");
		}
		else
		{
			// Get zones coordinates
			uint16 xMin;
			uint16 yMin;
			if (!getZoneCoordByName(getName (argv[1]).c_str(), xMin, yMin))
				fprintf (stderr, "Invalid zone name: %s\n", argv[1]);
			else
			{
				// Get zones coordinates
				uint16 xMax;
				uint16 yMax;
				if (!getZoneCoordByName(getName (argv[2]).c_str(), xMax, yMax))
					fprintf (stderr, "Invalid zone name: %s\n", argv[2]);
				else
				{
					// Reorder coordinates
					uint16 tmp;
					if (xMax<xMin)
					{
						tmp=xMin;
						xMin=xMax;
						xMax=tmp;
					}
					if (yMax<yMin)
					{
						tmp=yMin;
						yMin=yMax;
						yMax=tmp;
					}

					// Open the output file
					COFile output;
					if (output.open (argv[3]))
					{
						// Serial a tmp size
						uint32 zero=0;
						output.serial (zero);

						// Triangles counter
						uint32	triangles=0;

						// Get zones path name
						string path=getDir (argv[1]);
						string ext=getExt (argv[1]);

						// For all the zones
						for (int y=yMin; y<=yMax; y++)
						for (int x=xMin; x<=xMax; x++)
						{
							// Name of the zone
							string name;

							// Generate the zone name
							getZoneNameByCoord(x, y, name);

							// Open the zone
							CIFile input;
							if (input.open(path+name+ext))
							{
								// Warning message
								printf ("Dump %s\n", name);

								// Landscape
								CLandscape landscape;

								// Create a zone
								CZone zone;

								// Serial the zone
								zone.serial (input);

								// Add the zone
								landscape.addZone (zone);

								// Add triangle of this zone in the quadtree
								for (uint patch=0; patch<(uint)zone.getNumPatchs(); patch++)
								{
									// vector of triangle
									std::vector<CTriangle> faces;

									// Build a list of triangles at 50 cm
									buildFaces (landscape, zone.getZoneId(), patch, faces);

									// Add to the file
									for (uint tri=0; tri<faces.size(); tri++)
									{
										// Serial the triangle
										faces[tri].V0.serial (output);
										faces[tri].V1.serial (output);
										faces[tri].V2.serial (output);
									}

									// Triangle count
									triangles+=faces.size();
								}
							}
							else
								// Warning message
								printf ("Dump %s (missing)\n", name);
						}
					
						// Get the current pos
						sint32 curPos=output.getPos ();

						// File at the begining
						output.seek (0, IStream::begin);

						// Write the triangle count
						output.serial (triangles);

						// Go to the end of the file
						output.seek (curPos, IStream::begin);

						// Close the file
						output.close ();
					}
					else
					{
						fprintf (stderr, "Can't open %s for writing.", argv[3]);
					}

					// Export the zones
				}

			}
		}
	}
	catch (Exception& e)
	{
		fprintf (stderr, "FATAL: %s", e.what());
	}
	
	// exit.
	return 0;
}
