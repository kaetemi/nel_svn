/** \file s3tc_compressor.cpp
 * TODO: File description
 *
 * $Id: s3tc_compressor.cpp,v 1.7 2007/03/19 09:55:27 boucher Exp $
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

#include "s3tc_compressor.h"
#include "s3_intrf.h"
#include "ddraw.h"
#include "nel/../../src/3d/hls_color_texture.h"


using namespace std;


// ***************************************************************************
static void		compressMipMap(uint8 *pixSrc, sint width, sint height, vector<uint8>	&compdata, DDSURFACEDESC &dest, sint algo)
{
	// Filling DDSURFACEDESC structure for input
	DDSURFACEDESC src;
	memset(&src, 0, sizeof(src));
	src.dwSize = sizeof(src);
	src.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_LPSURFACE | 
				  DDSD_PITCH | DDSD_PIXELFORMAT;
	src.dwHeight = height;
	src.dwWidth = width;
	src.lPitch = width * 4;
	src.lpSurface = pixSrc;
	src.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	src.ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_ALPHAPIXELS;
	src.ddpfPixelFormat.dwRGBBitCount = 32;
	src.ddpfPixelFormat.dwRBitMask = 0x0000ff;
	src.ddpfPixelFormat.dwGBitMask = 0x00ff00;
	src.ddpfPixelFormat.dwBBitMask = 0xff0000;
	src.ddpfPixelFormat.dwRGBAlphaBitMask = 0xff000000;

	// Filling DDSURFACEDESC structure for output
	//===========================================
	memset(&dest, 0, sizeof(dest));
	dest.dwSize = sizeof(dest);
	
	// Setting encode type
	uint32 encodeType = 0;
	switch(algo)
	{
		case DXT1:
			encodeType = S3TC_ENCODE_RGB_FULL | S3TC_ENCODE_ALPHA_NONE;
			dest.dwLinearSize = width * height / 2; // required by S3TCTool
			break;
		case DXT1A:
			encodeType = S3TC_ENCODE_RGB_FULL | S3TC_ENCODE_RGB_ALPHA_COMPARE;
			S3TCsetAlphaReference(127); // set the threshold to 0.5
			dest.dwLinearSize = width * height / 2; // required by S3TCTool
			break;
		case DXT3:
			encodeType = S3TC_ENCODE_RGB_FULL | S3TC_ENCODE_ALPHA_EXPLICIT;
			dest.dwLinearSize = width * height; // required by S3TCTool
			break;
		case DXT5:
			encodeType = S3TC_ENCODE_RGB_FULL | S3TC_ENCODE_ALPHA_INTERPOLATED;
			dest.dwLinearSize = width * height; // required by S3TCTool
			break;
	}

	

	// Encoding
	//===========
	// resize dest.
	uint32 encodeSz = S3TCgetEncodeSize(&src,encodeType);
	compdata.resize(encodeSz);
	// Go!
	float weight[3] = {0.3086f, 0.6094f, 0.0820f};
	S3TCencode(&src, NULL, &dest, &(*compdata.begin()), encodeType, weight);
	
	switch(algo)
	{
		case DXT1:
			dest.ddpfPixelFormat.dwFourCC = MAKEFOURCC('D','X', 'T', '1');
			break;
		case DXT1A:
			dest.ddpfPixelFormat.dwFourCC = MAKEFOURCC('D','X', 'T', '1');
			break;
		case DXT3:
			dest.ddpfPixelFormat.dwFourCC = MAKEFOURCC('D','X', 'T', '3');
			break;
		case DXT5:
			dest.ddpfPixelFormat.dwFourCC = MAKEFOURCC('D','X', 'T', '5');
			break;
	}

	/* S3TC is a very good compressor, but make BIG mistakes in some case with  DXTC5 and DXTC3
	*/
	if( algo==DXT5 || algo==DXT3 )
	{
		sint	wBlock= max(1, width/4);
		sint	hBlock= max(1, height/4);
		uint	numTotalBlock= wBlock*hBlock;
		uint	numFixedBlock= 0;
		
		NLMISC::CRGBA	*rgbaSrc= (NLMISC::CRGBA*)pixSrc;
		for(sint y=0;y<hBlock;y++)
		{
			for(sint x=0;x<wBlock;x++)
			{
				// get comp dest
				uint8	*pixDst= &(*(compdata.begin() + (y*wBlock + x) * 16));
				uint16	rgb0= *(uint16*)(pixDst+8);
				uint16	rgb1= *(uint16*)(pixDst+10);
				/* If S3TC decided to use "50% decode table" (case rgb0<=rgb1), this is an error
					compress this block with our own compressor
				*/
				if(rgb0<=rgb1)
				{
					numFixedBlock++;

					// copy color block
					NLMISC::CRGBA	col[16];
					sint	x0, y0;
					NLMISC::CRGBA	precColor= NLMISC::CRGBA::Black;
					for(y0=0;y0<4;y0++)
					{
						for(x0=0;x0<4;x0++)
						{
							// manage case where height or width are <4
							if(y*4+y0<height && x*4+x0<width)
							{
								precColor= rgbaSrc[(y*4+y0)*width + x*4+x0];
								col[y0*4+x0]= precColor;
							}
							else
							{
								// copy preceding color, to allow correct compression 
								col[y0*4+x0]= precColor;
							}
						}
					}
					
					// compress
					NL3D::CHLSColorTexture::compressBlockRGB(col, pixDst);
					// get correct image under photoshop (swap color if our compressor invert them)
					rgb0= *(uint16*)(pixDst+8);
					rgb1= *(uint16*)(pixDst+10);
					if(rgb0<=rgb1)
					{
						*(uint16*)(pixDst+8)= rgb1;
						*(uint16*)(pixDst+10)= rgb0;
						uint32	&bits= *(uint32*)(pixDst+12);
						for(uint i=0;i<16; i++)
						{
							static uint8	invertTable[]= {1,0,3,2};
							uint	pixVal= (bits>>(i*2))&3;
							pixVal= invertTable[pixVal];
							bits&= ~(3<<(i*2));
							bits|= (pixVal<<(i*2));
						}
					}

					// Test: 05 to 1323
					/*
					uint32	&bits= *(uint32*)(pixDst+12);
					for(uint i=0;i<16; i++)
					{
						uint	pixVal= (bits>>(i*2))&3;
						if(pixVal==2)
						{
							uint r= (rand()&0xFF)>>7;
							pixVal= r+2;
							bits&= ~(3<<(i*2));
							bits|= (pixVal<<(i*2));
						}
					}*/
				}
			}
		}

		if(numFixedBlock && numTotalBlock)
		{
			nlinfo("Fix %d blocks on %d total ", numFixedBlock, numTotalBlock);
		}
	}
	
}



// ***************************************************************************
CS3TCCompressor::CS3TCCompressor()
{
}


// ***************************************************************************
void		CS3TCCompressor::compress(const NLMISC::CBitmap &bmpSrc, bool optMipMap, uint algo, NLMISC::IStream &output)
{
	vector<uint8>		CompressedMipMaps;
	DDSURFACEDESC		dest;
	NLMISC::CBitmap		picSrc= bmpSrc;


	// For all mipmaps, compress.
	if(optMipMap)
	{
		// Build the mipmaps.
		picSrc.buildMipMaps();
	}
	for(sint mp= 0;mp<(sint)picSrc.getMipMapCount();mp++)
	{
		uint8	*pixDest;
		uint8	*pixSrc= picSrc.getPixels(mp).getPtr();
		sint	w= picSrc.getWidth(mp);
		sint	h= picSrc.getHeight(mp);
		vector<uint8>	compdata;
		DDSURFACEDESC	temp;
		compressMipMap(pixSrc, w, h, compdata, temp, algo);
		// Copy the result of the base dds in the dest.
		if(mp==0)
			dest= temp;

		// Append this data to the global data.
		sint	delta= CompressedMipMaps.size();
		CompressedMipMaps.resize(CompressedMipMaps.size()+compdata.size());
		pixDest= &(*CompressedMipMaps.begin())+ delta;
		memcpy( pixDest, &(*compdata.begin()), compdata.size());
	}



	// Replace DDSURFACEDESC destination header by a DDSURFACEDESC2 header
	//====================================================================
	DDSURFACEDESC2 dest2;
	memset(&dest2, 0, sizeof(dest2));
	dest2.dwSize = sizeof(dest2);
	dest2.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_LPSURFACE | 
					DDSD_LINEARSIZE | DDSD_PIXELFORMAT; 
	dest2.dwHeight = dest.dwHeight;
	dest2.dwWidth = dest.dwWidth;
	dest2.dwLinearSize = dest.dwLinearSize;
	dest2.dwMipMapCount = dest.dwMipMapCount;
	dest2.dwAlphaBitDepth = dest.dwAlphaBitDepth;
	dest2.dwReserved = dest.dwReserved;
	dest2.lpSurface = dest.lpSurface;
	dest2.ddpfPixelFormat = dest.ddpfPixelFormat;
	// Setting Nb MipMap.
	dest2.dwFlags|= DDSD_MIPMAPCOUNT;
	dest2.dwMipMapCount= picSrc.getMipMapCount();


	// Saving DDS file
	//=================
	output.serialBuffer((uint8*)std::string("DDS ").c_str(),4);
	output.serialBuffer((uint8*) &dest2, sizeof(dest2));
	output.serialBuffer(&(*CompressedMipMaps.begin()), CompressedMipMaps.size());
}
