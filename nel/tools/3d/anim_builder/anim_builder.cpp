/** \file anim_builder.cpp
 * Parse a directory and build optimized animations to an other directory
 *
 * $Id: anim_builder.cpp,v 1.2 2007/03/19 09:55:25 boucher Exp $
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

#include "anim_builder.h"
#include "nel/misc/stream.h"
#include "nel/misc/file.h"
#include "nel/misc/config_file.h"
#include "nel/misc/path.h"

#include "nel/../../src/3d/animation.h"
#include "nel/../../src/3d/animation_optimizer.h"
#include "nel/../../src/3d/register_3d.h"


using namespace std;
using namespace NLMISC;
using namespace NL3D;

// ***************************************************************************
void	skipLog(const char *str)
{
	DebugLog->addNegativeFilter(str);
	WarningLog->addNegativeFilter(str);
}

// ***************************************************************************
int main(int argc, char* argv[])
{
	// Register 3d
	registerSerial3d ();

	// Avoid some stupids warnings.
	NLMISC::createDebug();
	skipLog("variable \"RootConfigFilename\"");
	skipLog("variable \"anim_low_precision_tracks\"");
	skipLog("variable \"anim_sample_rate\"");
	InfoLog->addNegativeFilter("FEHTIMER>");
	InfoLog->addNegativeFilter("adding the path");


	// Good number of args ?
	if (argc<4)
	{
		// Help message
		printf ("anim_builder [directoryIn] [pathOut] [parameter_file] \n");
	}
	else
	{
		try
		{
			string	directoryIn= argv[1];
			string	pathOut= argv[2];
			string	paramFile= argv[3];

			// Verify directoryIn.
			directoryIn= CPath::standardizePath(directoryIn);
			if( !CFile::isDirectory(directoryIn) )
			{
				printf("DirectoryIn %s is not a directory", directoryIn.c_str());
				return -1;
			}
			// Verify pathOut.
			pathOut= CPath::standardizePath(pathOut);
			if( !CFile::isDirectory(pathOut) )
			{
				printf("PathOut %s is not a directory", pathOut.c_str());
				return -1;
			}

			// Our Animation optimizer.
			//=================
			CAnimationOptimizer		animationOptimizer;
			// Leave thresholds as default.
			animationOptimizer.clearLowPrecisionTracks();


			// Load and setup configFile.
			//=================
			CConfigFile parameter;
			// Load and parse the param file
			parameter.load (paramFile);

			// Get the Low Precision Track Key Names
			try
			{
				CConfigFile::CVar &anim_low_precision_tracks = parameter.getVar ("anim_low_precision_tracks");
				uint lpt;
				for (lpt = 0; lpt < (uint)anim_low_precision_tracks.size(); lpt++)
				{
					animationOptimizer.addLowPrecisionTrack(anim_low_precision_tracks.asString(lpt));
				}
			}
			catch(EUnknownVar &)
			{
				nlwarning("\"anim_low_precision_tracks\" not found in the parameter file. Add \"Finger\" and \"Ponytail\" by default");
				animationOptimizer.addLowPrecisionTrack("Finger");
				animationOptimizer.addLowPrecisionTrack("Ponytail");
			}

			// Sample Rate.
			try
			{
				CConfigFile::CVar &anim_sample_rate = parameter.getVar ("anim_sample_rate");
				float	sr= anim_sample_rate.asFloat(0);
				// Consider values > 1000 as error values.
				if(sr<=0 || sr>1000)
				{
					nlwarning("Bad \"anim_sample_rate\" value. Use Default of 30 fps.");
					animationOptimizer.setSampleFrameRate(30);
				}
				else
				{
					animationOptimizer.setSampleFrameRate(sr);
				}
			}
			catch(EUnknownVar &)
			{
				nlwarning("\"anim_sample_rate\" not found in the parameter file. Use Default of 30 fps.");
				animationOptimizer.setSampleFrameRate(30);
			}


			// Scan and load all files .ig in directories
			//=================
			uint		numSkipped= 0;
			uint		numBuilded= 0;
			vector<string>				listFile;
			CPath::getPathContent(directoryIn, false, false, true, listFile);
			for(uint iFile=0; iFile<listFile.size(); iFile++)
			{
				string	&igFile= listFile[iFile];
				// verify it is a .anim.
				if( CFile::getExtension(igFile) == "anim" )
				{
					string	fileNameIn= CFile::getFilename(igFile);
					string	fileNameOut= pathOut + fileNameIn;

					// skip the file?
					bool	mustSkip= false;

					// If File Out exist 
					if(CFile::fileExists(fileNameOut))
					{
						// If newer than file In, skip
						uint32		fileOutDate= CFile::getFileModificationDate(fileNameOut);
						if(	fileOutDate > CFile::getFileModificationDate(igFile) )
						{
							mustSkip= true;
						}
					}

					// If must process the file.
					if(!mustSkip)
					{
						// Read the animation.
						CAnimation	animIn;
						CIFile	fin;
						fin.open(CPath::lookup(igFile));
						fin.serial(animIn);

						// process.
						CAnimation	animOut;
						animationOptimizer.optimize(animIn, animOut);

						// Save this animation.
						COFile	fout;
						fout.open(fileNameOut);
						fout.serial(animOut);
						fout.close();

						numBuilded++;
					}
					else
					{
						numSkipped++;
					}

					// progress
					printf("Anim builded: %4d. Anim Skipped: %4d\r", numBuilded, numSkipped);
				}
			}

			// Add some info in the log.
			nlinfo("Anim builded: %4d", numBuilded);
			nlinfo("Anim skipped: %4d", numSkipped);

		}
		catch (Exception& except)
		{
			// Error message
			nlwarning ("ERROR %s\n", except.what());
		}
	}

	// exit.
	return 0;
}
