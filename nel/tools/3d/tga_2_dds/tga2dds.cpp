/** \file tga2dds.cpp
 * TGA to DDS converter
 *
 * $Id: tga2dds.cpp,v 1.12 2004/01/29 09:23:02 besson Exp $
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
#include <iostream>

#include "nel/misc/file.h"
#include "nel/misc/bitmap.h"
#include "nel/misc/file.h"
#include "nel/misc/debug.h"
#include <math.h>

#include "s3_intrf.h"
#include "ddraw.h"
#include "../s3tc_compressor_lib/s3tc_compressor.h"


using namespace NLMISC;
using namespace std;


#define	TGA8	8
#define	TGA16	16
#define NOT_DEFINED 0xff


bool sameType(const char *sFileNameDest, uint8 algo);
bool dataCheck(const char *sFileNameSrc, const char *sFileNameDest, uint8 algo);
std::string getOutputFileName(std::string inputFileName);
void writeInstructions();
void main(int argc, char **argv);




uint8 getType(const char *sFileNameDest)
{
	uint32 dds;
	FILE *f = fopen(sFileNameDest,"rb");
	if(f==NULL)
	{
		return NOT_DEFINED;
	}
	DDSURFACEDESC2 h;
	fread(&dds,1,4,f);
	fread(&h,sizeof(DDSURFACEDESC2),1,f);
	if(fclose(f))
	{
		cerr<<sFileNameDest<< "is not closed"<<endl;
	}

	if(h.ddpfPixelFormat.dwFourCC==MAKEFOURCC('D','X', 'T', '1')
		&& h.ddpfPixelFormat.dwRGBBitCount==0)
	{
		return DXT1;
	}
				
	if(h.ddpfPixelFormat.dwFourCC==MAKEFOURCC('D','X', 'T', '1')
		&& h.ddpfPixelFormat.dwRGBBitCount>0)
	{
		return DXT1A;
	}
	
	if(h.ddpfPixelFormat.dwFourCC==MAKEFOURCC('D','X', 'T', '3'))
	{
		return DXT3;
	}

	if(h.ddpfPixelFormat.dwFourCC==MAKEFOURCC('D','X', 'T', '5'))
	{
		return DXT5;
	}

	return NOT_DEFINED;
}

bool sameType(const char *sFileNameDest, uint8 &algo, bool wantMipMap)
{
	uint32 dds;
	FILE *f = fopen(sFileNameDest,"rb");
	if(f==NULL)
	{
		return false;
	}
	DDSURFACEDESC2 h;
	fread(&dds,1,4,f);
	fread(&h,sizeof(DDSURFACEDESC2),1,f);
	if(fclose(f))
	{
		cerr<<sFileNameDest<< "is not closed"<<endl;
	}

	bool	algoOk= false;
	switch(algo)
	{
		case DXT1:
			if(h.ddpfPixelFormat.dwFourCC==MAKEFOURCC('D','X', 'T', '1')
				&& h.ddpfPixelFormat.dwRGBBitCount==0)
				algoOk=true;
			break;
					
		case DXT1A:
			if(h.ddpfPixelFormat.dwFourCC==MAKEFOURCC('D','X', 'T', '1')
				&& h.ddpfPixelFormat.dwRGBBitCount>0)
				algoOk=true;
			break;
		
		case DXT3:
			if(h.ddpfPixelFormat.dwFourCC==MAKEFOURCC('D','X', 'T', '3'))
				algoOk=true;
			break;

		case DXT5:
			if(h.ddpfPixelFormat.dwFourCC==MAKEFOURCC('D','X', 'T', '5'))
				algoOk=true;
			break;
	}
	if(!algoOk)
		return false;
	
	// Test Mipmap.
	bool	fileHasMipMap= (h.dwFlags&DDSD_MIPMAPCOUNT) && (h.dwMipMapCount>1);
	if(fileHasMipMap==wantMipMap)
		return true;

	return false;
}



bool dataCheck(const char *sFileNameSrc, const char *sFileNameDest, uint8& algo, bool wantMipMap)
{
	
	HANDLE h1 = CreateFile( sFileNameSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(h1 == INVALID_HANDLE_VALUE)
	{
		cerr<<"Can't open file "<<sFileNameSrc<<endl;
		exit(1);
	}
	
	HANDLE h2 = CreateFile( sFileNameDest, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h2==INVALID_HANDLE_VALUE)
	{
		return false; // destination file doesn't exist yet
	}
	
	uint8 res;
	FILETIME Tmp;
	FILETIME lpLastWriteTime1;
	FILETIME lpLastWriteTime2;
	
	res = GetFileTime(h1, &Tmp, &Tmp, &lpLastWriteTime1);
	nlassert(res);
	
	res = GetFileTime(h2, &Tmp, &Tmp, &lpLastWriteTime2);
	nlassert(res);
	
	uint32 nComp = CompareFileTime(&lpLastWriteTime1, &lpLastWriteTime2);

	CloseHandle(h1);
	CloseHandle(h2);
	
	if(nComp==+1)
	{
		return false;
	}
	if(nComp==-1)
	{
		if(!sameType(sFileNameDest, algo, wantMipMap))
		{
			return false; // file exists but a new compression type is required
		}
		return true;
	}
	return true;
}


void writeInstructions()
{
	cout<<endl;
	cout<<"TGA2DDS"<<endl;
	cout<<"  Convert TGA image file (24bits or 32 bits) to DDS compressed file using"<<endl;
	cout<<"S3TC compression (DXTC1, DXTC1 with alpha, DXTC3, or DXTC5). "<<endl;
	cout<<"  The program looks for possible user color files and load them automatically,"<<endl;
	cout<<"a user color file must have the same name that the original tga file, plus the"<<endl;
	cout<<"extension \"_usercolor\""<<endl;
	cout<<"ex : pic.tga, the associated user color file must be : pic_usercolor.tga"<<endl; 
	cout<<endl;
	cout<<"syntax : tga2dds <input.tga> [-o <output.dds>] [-a <algo>] [-m]"<<endl;
	cout<<endl;
	cout<<"with"<<endl;
	cout<<"algo      : 1  for DXTC1 (no alpha)"<<endl;
	cout<<"            1A for DXTC1 with alpha"<<endl;
	cout<<"            3  for DXTC3"<<endl;
	cout<<"            5  for DXTC5"<<endl;
	cout<<"            tga16  for TGA 16 bits"<<endl;
	cout<<"            tga8   for TGA 8  bits"<<endl;
	cout<<"-m        : Create MipMap"<<endl;
	cout<<"-rFACTOR  : Reduce the bitmap size before compressing"<<endl;
	cout<<"            FACTOR is 0, 1, 2, 3, 4, 5, 6, 7 or 8"<<endl;
	cout<<endl;
	cout<<"default   : DXTC1 if Tga 24b, DXTC5 if Tga 32b."<<endl;
	cout<<endl;
	cout<<"/? for this help"<<endl;
	cout<<endl; 
}


std::string getOutputFileName(std::string inputFileName)
{
	uint8 pos = inputFileName.rfind(".tga");
	if(pos>=inputFileName.length()) // name whithout extension ".tga"
		return (inputFileName + ".dds");
	else
		return (inputFileName.substr(0,pos) + ".dds");
}


// ***************************************************************************
string		OptOutputFileName;
uint8		OptAlgo = NOT_DEFINED;
bool		OptMipMap = false;
uint		Reduce = 0;
bool	parseOptions(int argc, char **argv)
{
	for(sint i=2;i<argc;i++)
	{
		// OutputFileName.
		if(!strcmp(argv[i], "-o"))
		{
			i++;
			if(i>=argc) return false;
			OptOutputFileName= argv[i];
		}
		// Algo.
		else if(!strcmp(argv[i], "-a"))
		{
			i++;
			if(i>=argc) return false;
			if(!strcmp(argv[i],"1"))	OptAlgo = DXT1;
			else
			if(!strcmp(argv[i],"1A")) 	OptAlgo = DXT1A;
			else
			if(!strcmp(argv[i],"1a")) 	OptAlgo = DXT1A;
			else
			if(!strcmp(argv[i],"3"))	OptAlgo = DXT3;
			else
			if(!strcmp(argv[i],"5"))	OptAlgo = DXT5;
			else
			if(!strcmp(argv[i],"tga16"))	OptAlgo = TGA16;
			else
			if(!strcmp(argv[i],"tga8"))	OptAlgo = TGA8;
			else
			{
				cerr<<"Algorithm unknown : "<<argv[i]<<endl;
				exit(1);
			}
		}
		// MipMap.
		else if(!strcmp(argv[i], "-m"))
		{
			OptMipMap= true;
		}
		// Reduce size of the bitmap
		else if(!strcmp(argv[i], "-r0"))
			Reduce = 0;
		else if(!strcmp(argv[i], "-r1"))
			Reduce = 1;
		else if(!strcmp(argv[i], "-r2"))
			Reduce = 2;
		else if(!strcmp(argv[i], "-r3"))
			Reduce = 3;
		else if(!strcmp(argv[i], "-r4"))
			Reduce = 4;
		else if(!strcmp(argv[i], "-r5"))
			Reduce = 5;
		else if(!strcmp(argv[i], "-r6"))
			Reduce = 6;
		else if(!strcmp(argv[i], "-r7"))
			Reduce = 7;
		else if(!strcmp(argv[i], "-r8"))
			Reduce = 8;
		// What is this option?
		else
		{
			return false;
		}
	}

	return true;
}

// ***************************************************************************
void dividSize (CBitmap &bitmap)
{
	// Must be RGBA
	nlassert (bitmap.getPixelFormat () == CBitmap::RGBA);

	// Copy the bitmap
	CBitmap temp = bitmap;

	// Resize the destination
	const uint width = temp.getWidth ();
	const uint height = temp.getHeight ();
	const uint newWidth = temp.getWidth ()/2;
	const uint newHeight = temp.getHeight ()/2;
	bitmap.resize (newWidth, newHeight, CBitmap::RGBA);

	// Pointers
	uint8 *pixelSrc = &(temp.getPixels ()[0]);
	uint8 *pixelDest = &(bitmap.getPixels ()[0]);

	// Resample
	uint x, y;
	for (y=0; y<newHeight; y++)
	for (x=0; x<newWidth; x++)
	{
		const uint offsetSrc = ((y*2)*width+x*2)*4;
		const uint offsetDest = (y*newWidth+x)*4;
		uint i;
		for (i=0; i<4; i++)
		{
			pixelDest[offsetDest+i] = ((uint)pixelSrc[offsetSrc+i] + (uint)pixelSrc[offsetSrc+4+i] + 
				(uint)pixelSrc[offsetSrc+4*width+i] + (uint)pixelSrc[offsetSrc+4*width+4+i])>>2;
		}
	}
}

// ***************************************************************************
void main(int argc, char **argv)
{
	uint8 algo;
	
	// Parse Command Line.
	//====================
	if(argc<2)
	{
		writeInstructions();
		return;
	}
	if(!strcmp(argv[1],"/?"))
	{
		writeInstructions();
		return;
	}
	if(!strcmp(argv[1],"-?"))
	{
		writeInstructions();
		return;
	}
	if(!parseOptions(argc, argv))
	{
		writeInstructions();
		return;
	}


	// Reading TGA and converting to RGBA
	//====================================
	CBitmap picTga;
	CBitmap picTga2;
	CBitmap picSrc;

	
	std::string inputFileName(argv[1]);
	if(inputFileName.find("_usercolor")<inputFileName.length())
	{
		return;
	}
	NLMISC::CIFile input;
	if(!input.open(inputFileName))
	{
		cerr<<"Can't open input file "<<inputFileName<<endl;
		exit(1);
	}
	uint8 imageDepth = picTga.load(input);
	if(imageDepth==0)
	{
		cerr<<"Can't load file : "<<inputFileName<<endl;
		exit(1);
	}
	if(imageDepth!=16 && imageDepth!=24 && imageDepth!=32 && imageDepth!=8)
	{
		cerr<<"Image not supported : "<<imageDepth<<endl;
		exit(1);
	}
	input.close();
	uint32 height = picTga.getHeight();
	uint32 width= picTga.getWidth();
	picTga.convertToType (CBitmap::RGBA);


	// Output file name and algo.
	//===========================
	std::string outputFileName;
	if(OptOutputFileName!="")
		outputFileName= OptOutputFileName;
	else
		outputFileName= getOutputFileName(inputFileName);

	// Check dest algo
	if (OptAlgo==NOT_DEFINED)
		OptAlgo = getType (outputFileName.c_str());
	
	// Choose Algo.
	if(OptAlgo!=NOT_DEFINED)
	{
		algo= OptAlgo;
	}
	else
	{
		if(imageDepth==24)
			algo = DXT1;
		else
			algo = DXT5;
	}

	// Data check
	//===========
	if(dataCheck(inputFileName.c_str(),outputFileName.c_str(), OptAlgo, OptMipMap))
	{
		cout<<outputFileName<<" : a recent dds file already exists"<<endl;
		return;
	}


	// Vectors for RGBA data
	CObjectVector<uint8> RGBASrc = picTga.getPixels();
	CObjectVector<uint8> RGBASrc2;
	CObjectVector<uint8> RGBADest;
	RGBADest.resize(height*width*4);
	uint	dstRGBADestId= 0;
	



	// UserColor
	//===========
	/*
	// Checking if option "usercolor" has been used
	std::string userColorFileName;
	if(argc>4)
	{
		if(strcmp("-usercolor",argv[4])==0)
		{
			if(argc!=6)
			{
				writeInstructions();
				return;
			}
			userColorFileName = argv[5];
		}
		else
		{
			writeInstructions();
			return;
		}
	}
	*/
	// Checking if associate usercolor file  exists
	std::string userColorFileName;
	uint8 pos = inputFileName.rfind(".tga");
	if(pos>=inputFileName.length()) // name whithout extension ".tga"
	{
		pos = inputFileName.length();
		userColorFileName = inputFileName.substr(0,pos) + "_usercolor"; 
	}
	else
		userColorFileName = inputFileName.substr(0,pos) + "_usercolor.tga";
	
	
	// Reading second Tga for user color
	NLMISC::CIFile input2;
	if(input2.open(userColorFileName))
	{
		picTga2.load(input2);
		uint32 height2 = picTga2.getHeight();
		uint32 width2 = picTga2.getWidth();
		nlassert(width2==width);
		nlassert(height2==height);
		picTga2.convertToType (CBitmap::RGBA);



		RGBASrc2 = picTga2.getPixels();

		NLMISC::CRGBA *pRGBASrc = (NLMISC::CRGBA*)&RGBASrc[0];
		NLMISC::CRGBA *pRGBASrc2 = (NLMISC::CRGBA*)&RGBASrc2[0];
	
		for(uint32 i = 0; i<width*height; i++)
		{
			// If no UserColor, must take same RGB, and keep same Alpha from src1 !!! So texture can have both alpha
			// userColor and other alpha usage.
			if(pRGBASrc2[i].A==255) 
			{
				RGBADest[dstRGBADestId++]= pRGBASrc[i].R;
				RGBADest[dstRGBADestId++]= pRGBASrc[i].G;
				RGBADest[dstRGBADestId++]= pRGBASrc[i].B;
				RGBADest[dstRGBADestId++]= pRGBASrc[i].A;
			}
			else
			{
				// Old code.
				/*uint8 F = (uint8) ((float)pRGBASrc[i].R*0.3 + (float)pRGBASrc[i].G*0.56 + (float)pRGBASrc[i].B*0.14);
				uint8 Frgb;
				if((F*pRGBASrc2[i].A/255)==255)
					Frgb = 0;
				else
					Frgb = (255-pRGBASrc2[i].A)/(255-F*pRGBASrc2[i].A/255);
				RGBADest[dstRGBADestId++]= Frgb*pRGBASrc[i].R/255;
				RGBADest[dstRGBADestId++]= Frgb*pRGBASrc[i].G/255;
				RGBADest[dstRGBADestId++]= Frgb*pRGBASrc[i].B/255;
				RGBADest[dstRGBADestId++]= F*pRGBASrc[i].A/255;*/

				// New code: use new restrictions from IDriver.
				float	Rt, Gt, Bt, At;
				float	Lt;
				float	Rtm, Gtm, Btm, Atm;

				// read 0-1 RGB pixel.
				Rt= (float)pRGBASrc[i].R/255;
				Gt= (float)pRGBASrc[i].G/255;
				Bt= (float)pRGBASrc[i].B/255;
				Lt= Rt*0.3f + Gt*0.56f + Bt*0.14f;

				// take Alpha from userColor src.
				At= (float)pRGBASrc2[i].A/255;
				Atm= 1-Lt*(1-At);

				// If normal case.
				if(Atm>0)
				{
					Rtm= Rt*At / Atm;
					Gtm= Gt*At / Atm;
					Btm= Bt*At / Atm;
				}
				// Else special case: At==0, and Lt==1.
				else
				{
					Rtm= Gtm= Btm= 0;
				}

				// copy to buffer.
				sint	r,g,b,a;
				r= (sint)floor(Rtm*255+0.5f);
				g= (sint)floor(Gtm*255+0.5f);
				b= (sint)floor(Btm*255+0.5f);
				a= (sint)floor(Atm*255+0.5f);
				clamp(r, 0,255);
				clamp(g, 0,255);
				clamp(b, 0,255);
				clamp(a, 0,255);
				RGBADest[dstRGBADestId++]= r;
				RGBADest[dstRGBADestId++]= g;
				RGBADest[dstRGBADestId++]= b;
				RGBADest[dstRGBADestId++]= a;
			}
		}
	}
	else
		RGBADest = RGBASrc;

	// Copy to the dest bitmap.
	picSrc.resize(width, height, CBitmap::RGBA);
	picSrc.getPixels(0)= RGBADest;

	// Resize the destination bitmap ?
	while (Reduce != 0)
	{
		dividSize (picSrc);
		Reduce--;
	}

	// 8 or 16 bits tga ?
	if ((algo == TGA16) || (algo == TGA8))
	{
		// Saving TGA file
		//=================
		NLMISC::COFile output;
		if(!output.open(outputFileName))
		{
			cerr<<"Can't open output file "<<outputFileName<<endl;
			exit(1);
		}
		try 
		{
			if (algo == TGA16)
			{
				picSrc.writeTGA (output, 16);
			} 
			else if (algo == TGA8)
			{
				picSrc.convertToType(CBitmap::Luminance);
				picSrc.writeTGA (output, 8);
			}
		}
		catch(NLMISC::EWriteError &e)
		{
			cerr<<e.what()<<endl;
			exit(1);
		}
	
		output.close();

	}
	else
	{
		// Compress
		//===========

		// log.
		std::string algostr;
		switch(algo)
		{
			case DXT1:
				algostr = "DXTC1";
				break;
			case DXT1A:
				algostr = "DXTC1A";
				break;
			case DXT3:
				algostr = "DXTC3";
				break;
			case DXT5:
				algostr = "DXTC5";
				break;
		}
		cout<<"compressing ("<<algostr<<") "<<inputFileName<<" to "<<outputFileName<<endl;


		// Saving compressed DDS file
		//=================*/
		NLMISC::COFile output;
		if(!output.open(outputFileName))
		{
			cerr<<"Can't open output file "<<outputFileName<<endl;
			exit(1);
		}
		try
		{
			CS3TCCompressor		comp;
			comp.compress(picSrc, OptMipMap, algo, output);
		}
		catch(NLMISC::EWriteError &e)
		{
			cerr<<e.what()<<endl;
			exit(1);
		}
		
		output.close();
	}
}	










	
