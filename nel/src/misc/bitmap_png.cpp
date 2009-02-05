/** \file bitmap_png.cpp
 * Class managing bitmaps (complementary file in order to keep bitmap.cpp as clean as possible
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

#include "stdmisc.h"

#include "nel/misc/bitmap.h"

#include "nel/misc/stream.h"
#include "nel/misc/file.h"
#include "nel/misc/dynloadlib.h"
#include <csetjmp>

using namespace std;


namespace NLMISC
{
/*-------------------------------------------------------------------*\
							readPNG
\*-------------------------------------------------------------------*/

uint8 CBitmap::readPNG( NLMISC::IStream &f )
{

	int                 iBitDepth;
	int                 iColorType;
	png_struct *png_ptr = NULL;
	png_info *info_ptr = NULL;
	PixelFormat=RGBA;

	if(!f.isReading()) return false;

	/*Initialise the info header*/
	png_ptr = (png_struct*)png_create_read_struct(PNG_LIBPNG_VER_STRING,//
      NULL, NULL, NULL);

	if (png_ptr == NULL)
	{
		nlwarning("CBitmap::readPNG : failed to create the png read struct");
		return (0);
	}

	/* Allocate/initialize the memory for image information. */
	info_ptr = (png_info*)png_create_info_struct(png_ptr);
	if (info_ptr == NULL)
	{
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		nlwarning("CBitmap::readPNG : failed to create the png info struct");
		return (0);
	}


	if (setjmp(png_ptr->jmpbuf))
	{
		/* Free all of the memory associated with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		/* If we get here, we had a problem reading the file */
		nlwarning("CBitmap::readPNG : failed to setjump");
		return (0);
	}

	//transtype
	//CIFile*  test=(CIFile*)&f;



	//set the read function
	png_set_read_fn(png_ptr, (void*)&f, readPNGData);


	//set number of bit already read (in order to step back)
	png_set_sig_bytes(png_ptr, 4);



	//read header info and use it
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR( png_ptr,
				  info_ptr,
				  (png_uint_32*) &_Width,
				  (png_uint_32*) &_Height,
				  &iBitDepth,
				  &iColorType,
				  NULL, NULL, NULL);


	// row_bytes is the width x number of channels

	 uint32 ulRowBytes = png_get_rowbytes(png_ptr, info_ptr);
     uint32 ulChannels = png_get_channels(png_ptr, info_ptr);




	// expand images of all color-type and bit-depth to 3x8 bit RGB images
    // let the library process things like alpha, transparency, background
    double              dGamma;

    if (iBitDepth == 16)
        png_set_strip_16(png_ptr);

	/* Expand grayscale images to the full 8 bits from 1, 2, or 4 bits/pixel */
	if (iColorType == PNG_COLOR_TYPE_GRAY && iBitDepth < 8)
		png_set_gray_1_2_4_to_8(png_ptr);

    /*if (iColorType == PNG_COLOR_TYPE_PALETTE)
        png_set_expand(png_ptr);*/

    if (iBitDepth < 8)
        png_set_expand(png_ptr);

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_expand(png_ptr);

    // if required set gamma conversion
    if (png_get_gAMA(png_ptr, info_ptr, &dGamma))
        png_set_gamma(png_ptr, (double) 2.2, dGamma);


    // after the transformations have been registered update info_ptr data

    png_read_update_info(png_ptr, info_ptr);

    // get again width, height and the new bit-depth and color-type

    png_get_IHDR(png_ptr,
				 info_ptr,
				 (png_uint_32*) &_Width,
				 (png_uint_32*) &_Height,
				 &iBitDepth,
				 &iColorType,
				 NULL,
				 NULL,
				 NULL);


	//At this point, the image must converted to an 24bit image RGB


	//allocate memory to load the image
//	char **pbRowPointers=new char*[(const uint32)_Height];




    // row_bytes is the width x number of channels
	ulRowBytes = png_get_rowbytes(png_ptr, info_ptr);
	ulChannels = png_get_channels(png_ptr, info_ptr);

	uint32 *piChannels;
	char **ppbRowPointers;
	char *pbImageData=NULL;
	piChannels = &ulChannels;

	// now we can allocate memory to store the image


	if ((pbImageData = new char  [ulRowBytes * (_Height)
						* sizeof(char)]) == NULL)
	{
		png_error(png_ptr, "Visual PNG: out of memory");
	}


	// and allocate memory for an array of row-pointers

	if ((ppbRowPointers = new char*[_Height
						* sizeof(char*)]) == NULL)
	{
		png_error(png_ptr, "Visual PNG: out of memory");
	}

	// set the individual row-pointers to point at the correct offsets

	for (uint16 i = 0; i < (_Height); i++)
	{
		ppbRowPointers[i] = pbImageData + i * ulRowBytes;
	}


	//effective read of the image
	png_read_image(png_ptr, (png_bytepp)ppbRowPointers);

	png_read_end(png_ptr, NULL);



	uint8 bit=0;//number of bit needed for a pixel

	//RGB and RGBA results to almost the same bitmap, alpha will be added to RGB
	if(iColorType==PNG_COLOR_TYPE_RGB)
	{
		resize (_Width, _Height, RGBA);//resize the _Data pointer to the correct size and format

		for (uint32 row = 0; row < _Height; row++)
	   {
			for(uint32 line=0;line<_Width;line++)
			{
				for(uint32 pix=0;pix<3;pix++)
				{//get the RGB
					_Data[0][row*_Width*4+line*4+pix]=pbImageData[row*_Width*3+line*3+pix];
				}//for pix<3
				_Data[0][row*_Width*4+line*4+3]=0xff;//add the alpha setting
			}//for line<_Width
		}//for row<_Height
		bit=4;

	}

	if(iColorType==PNG_COLOR_TYPE_RGBA)
	{
		resize (_Width, _Height, RGBA);//resize the _Data pointer to the correct size and format

		for (uint32 row = 0; row < _Height; row++)
		{
			for(uint32 line=0;line<_Width;line++)
			{
				for(uint32 pix=0;pix<4;pix++)
				{//get the RGBA
				 _Data[0][row*_Width*4+line*4+pix]=pbImageData[row*_Width*4+line*4+pix];
				}//for pix<4
			}//for line<_Width

		}//for row<_Height
		bit=4;
    }



	//handled slitly diferently, a gray image will de kept gray ( to save some space)
	if(iColorType==PNG_COLOR_TYPE_GRAY || iColorType==PNG_COLOR_TYPE_GRAY_ALPHA)
	{
		//resize the _Data pointer to the correct size and format
		resize (_Width, _Height, (iColorType==PNG_COLOR_TYPE_GRAY)?Luminance:Alpha);

		for (uint32 row = 0; row < _Height; row++)
		{
			for(uint32 line=0;line<_Width;line++)
			{
				//data is copied seamlessly
				_Data[0][row*_Width+line]=pbImageData[row*_Width+line];
			}//for line<_Width

		}  //for row<_Height
		bit=1;
    }

	//the paletted PNG are not handled yet
	if(iColorType==PNG_COLOR_TYPE_PALETTE)
	{
		//test->close();
		nlwarning("CBitmap::readPNG : paletted image are not supported yet");
		return 0;
	}
	delete []ppbRowPointers;//free allocated memory to copy the image
	delete []pbImageData;



   /* clean up after the read, and free any memory allocated  */
   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

   //test->close();
   return uint8(iBitDepth)*bit;//return the size of a pixel, either 8,24,32 bit
}

/*-------------------------------------------------------------------*\
							writePNG
\*-------------------------------------------------------------------*/
bool CBitmap::writePNG( NLMISC::IStream &f, uint32 d)
{
	if(f.isReading()) return false;

	if (d==0)
	{
		switch (PixelFormat)
		{
		case RGBA:
			d = 32;
			break;
		case Luminance:
			d = 8;
			break;
		case Alpha:
			d = 8;
			break;
		default:
			;
		}
	}

	if (d!=24 && d!=32) return false;
	if ((PixelFormat != RGBA)&&(PixelFormat != Alpha)&&(PixelFormat != Luminance)) return false;
	if ((PixelFormat == Alpha) && (d != 8)) return false;
	if ((PixelFormat == Luminance) && (d != 8)) return false;

	png_struct *png_ptr = NULL;
	png_info *info_ptr = NULL;

	png_ptr = (png_struct*)png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, setPNGError, setPNGWarning);

	if (!png_ptr)
	{
		nlwarning("CBitmap::writePNG : Couldn't save PNG image.");
		return false;
	}

	info_ptr = (png_info_struct*)png_create_info_struct(png_ptr);

	if (info_ptr == NULL)
	{
		png_destroy_write_struct( &png_ptr, (png_info**)NULL );
		nlwarning("CBitmap::writePNG : Couldn't save PNG image.");
		return false;
	}

	if (setjmp(png_ptr->jmpbuf))
	{
		png_destroy_write_struct( &png_ptr, (png_info**)NULL );
		nlwarning("CBitmap::writePNG : Couldn't save PNG image.");
		return false;
	}

	//set the write functiun
	png_set_write_fn(png_ptr, (void*)&f, writePNGData, NULL);

	const int iColorType = (d == 32) ? PNG_COLOR_TYPE_RGBA:PNG_COLOR_TYPE_RGB; // only RGBA and RGB color type is implemented
	const int iBitDepth = 8; // we don't have to implement 16bits formats because NeL only uses 8bits

	png_set_IHDR(png_ptr, info_ptr, _Width, _Height, iBitDepth, iColorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	int iElements;
	png_color_8 sig_bit;

	if (iColorType & PNG_COLOR_MASK_COLOR)
	{
		sig_bit.red = sig_bit.green = sig_bit.blue = (uint8)iBitDepth;
		iElements = 3;
	}
	else // grey
	{
		sig_bit.gray = (uint8)iBitDepth;
		iElements = 1;
	}

	if (iColorType & PNG_COLOR_MASK_ALPHA)
	{
		sig_bit.alpha = (uint8)iBitDepth;
		++iElements;
	}

	png_set_sBIT( png_ptr, info_ptr, &sig_bit );
	png_write_info( png_ptr, info_ptr );
	png_set_shift( png_ptr, &sig_bit );
	png_set_packing( png_ptr );

	uint8 *scanline = NULL;

	int iHeight = _Height;
	int iWidth = _Width;

	if ((PixelFormat == Alpha)||(PixelFormat == Luminance))
	{
		scanline = new uint8[iWidth];
	}
	else
	{
		scanline = new uint8[iWidth*4];
	}

	if(!scanline)
	{
		png_destroy_write_struct( &png_ptr, (png_info**)NULL );
		nlwarning("CBitmap::writePNG : Couldn't save PNG image.");
		return false;
	}

	sint32 y, j, i;

	for(y=0; y<(sint32)iHeight; ++y)
	{
		uint32 k=0;

		for(i=0; i<iWidth*4; i+=4)
		{
			for(j=0; j<(sint32)d/8; ++j)
			{
				scanline[k++] = _Data[0][y*iWidth*4 + i + j];
			}
		}

		png_write_rows(png_ptr, (uint8**)&scanline, 1);
	}

	delete [] scanline;

	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);

	return true;
}

#ifdef NL_OS_WINDOWS
#pragma managed(pop)
#endif

/*-------------------------------------------------------------------*\
								readPNGData
\*-------------------------------------------------------------------*/

void readPNGData(png_structp png_ptr, png_bytep data, png_size_t length)
{
	((IStream*) png_ptr->io_ptr)->serialBuffer((uint8*)data,length);
}

/*-------------------------------------------------------------------*\
								writePNGData
\*-------------------------------------------------------------------*/

void writePNGData(png_structp png_ptr, png_bytep data, png_size_t length)
{
	((IStream*) png_ptr->io_ptr)->serialBuffer((uint8*)data,length);
}

void setPNGWarning(png_struct * /* png_ptr */, const char* message)
{
	nlwarning(message);
}

// from pngerror.c
// so that the libpng doesn't send anything on stderr
void setPNGError(png_struct *png_ptr, const char* message)
{
	setPNGWarning(NULL, message);

    // we're not using libpng built-in jump buffer (see comment before
    // wxPNGInfoStruct above) so we have to return ourselves, otherwise libpng
    // would just abort
	longjmp(png_ptr->jmpbuf, 1);
}

}//namespace
