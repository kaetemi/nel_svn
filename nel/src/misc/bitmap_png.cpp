/** \file bitmap_png.cpp
 * Class managing bitmaps (complementary file in order to keep bitmap.cpp as clean as possible
 *
 * $Id: bitmap_png.cpp,v 1.5 2005/02/22 10:19:20 besson Exp $
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

// Currently this class supports Windows only
#ifdef NL_OS_WINDOWS

#include "nel/misc/stream.h"
#include "nel/misc/file.h"
#include "nel/misc/dynloadlib.h"
#include "nel/misc/bitmap.h"
#include <csetjmp>

using namespace std;

#define PNG_LIBPNG_VER_STRING "1.2.5"
#define PNG_COLOR_MASK_PALETTE    1
#define PNG_COLOR_MASK_COLOR      2
#define PNG_COLOR_MASK_ALPHA      4
#define PNG_COLOR_TYPE_GRAY 0
#define PNG_COLOR_TYPE_PALETTE  (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_PALETTE)
#define PNG_COLOR_TYPE_RGB        (PNG_COLOR_MASK_COLOR)
#define PNG_COLOR_TYPE_RGB_ALPHA  (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_ALPHA)
#define PNG_COLOR_TYPE_GRAY_ALPHA (PNG_COLOR_MASK_ALPHA)
#define PNG_COLOR_TYPE_RGBA  PNG_COLOR_TYPE_RGB_ALPHA
#define PNG_COLOR_TYPE_GA  PNG_COLOR_TYPE_GRAY_ALPHA
#define PNG_INFO_tRNS 0x0010

typedef struct png_info_struct
{
   /* the following are necessary for every PNG file */
   uint32 width;       /* width of image in pixels (from IHDR) */
   uint32 height;      /* height of image in pixels (from IHDR) */
   uint32 valid;       /* valid chunk data (see PNG_INFO_ below) */
   uint32 rowbytes;    /* bytes needed to hold an untransformed row */
   void			*palette;      /* array of color values (valid & PNG_INFO_PLTE) */
   uint16 num_palette; /* number of color entries in "palette" (PLTE) */
   uint16 num_trans;   /* number of transparent palette color (tRNS) */
   char bit_depth;      /* 1, 2, 4, 8, or 16 bits/channel (from IHDR) */
   char color_type;     /* see PNG_COLOR_TYPE_ below (from IHDR) */
} png_info;

struct png_struct
{
   jmp_buf jmpbuf;            /* used in png_error */
   void *error_fn;    /* function for printing errors and aborting */
   void *warning_fn;  /* function for printing warnings */
   void *error_ptr;       /* user supplied struct for error functions */
   void *write_data_fn;  /* function for writing output data */
   void *read_data_fn;   /* function for reading input data */
   void *io_ptr;          /* ptr to application struct for I/O functions */
};

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

	

//	CLibrary fctLoader(CLibrary::loadLibrary(string("libpng13.dll")));
	CLibrary fctLoader("libpng13.dll", false, false);

	///////////////////////////

	BOOL (* png_create_read_struct) (const char *user_png_ver, 
											void *error_ptr,
											void *error_fn, 
											void *warn_fn)		
	=NULL;
	*(FARPROC*)&png_create_read_struct=(FARPROC)fctLoader.getSymbolAddress(string("png_create_read_struct"));
	if(!png_create_read_struct)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_create'");
		return 0;
	}

	///////////////////////////
		
	BOOL (* png_create_info_struct)(png_struct *png_ptr)=NULL;
	*(FARPROC*)&png_create_info_struct=(FARPROC)fctLoader.getSymbolAddress(string("png_create_info_struct"));
	if(!png_create_info_struct)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_create_info_struct'");
		return 0;
	}

	///////////////////////////
	
	BOOL (* png_destroy_read_struct) (png_struct **png_ptr_ptr, 
											png_info **info_ptr_ptr, 
											png_info **end_info_ptr_ptr)
	=NULL;
	*(FARPROC*)&png_destroy_read_struct=(FARPROC)fctLoader.getSymbolAddress(string("png_destroy_read_struct"));
	if(!png_destroy_read_struct)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_destroy_read_struct'");
		return 0;
	}

	///////////////////////////
	
	BOOL (* png_set_sig_bytes)   (png_struct *png_ptr,
										int num_bytes)
	=NULL;
	*(FARPROC*)&png_set_sig_bytes=(FARPROC)fctLoader.getSymbolAddress(string("png_set_sig_bytes"));
	if(!png_set_sig_bytes)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_set_sig_bytes'");
		return 0;
	}

	///////////////////////////
	
	BOOL (* png_malloc)  (png_struct *png_ptr,
								uint32 size)
	=NULL;
	*(FARPROC*)&png_malloc=(FARPROC)fctLoader.getSymbolAddress(string("png_malloc"));
	if(!png_malloc)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_malloc'");
		return 0;
	}

	///////////////////////////
	
	BOOL (* png_get_rowbytes)    (png_struct *png_ptr,
										png_info *info_ptr)
	=NULL;
	*(FARPROC*)&png_get_rowbytes=(FARPROC)fctLoader.getSymbolAddress(string("png_get_rowbytes"));
	if(!png_get_rowbytes)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_get_rowbytes'");
		return 0;
	}

	///////////////////////////
	
	BOOL (* png_init_io)    (png_struct *png_ptr,
										FILE *f)
	=NULL;
	*(FARPROC*)&png_init_io=(FARPROC)fctLoader.getSymbolAddress(string("png_init_io"));
	if(!png_init_io)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_init_io'");
		return 0;
	}

	///////////////////////////
	
	BOOL (* png_read_info)    (png_struct *png_ptr, 
							 png_info *info_ptr)
	=NULL;
	*(FARPROC*)&png_read_info=(FARPROC)fctLoader.getSymbolAddress(string("png_read_info"));
	if(!png_read_info)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_read_info'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_set_read_fn)    ( png_struct *png_ptr,
								void *io_ptr, 
								void *read_data_fn)
	=NULL;
	*(FARPROC*)&png_set_read_fn=(FARPROC)fctLoader.getSymbolAddress(string("png_set_read_fn"));
	if(!png_set_read_fn)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_set_read_fn'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_get_IHDR)    (  png_struct *png_ptr,
								png_info *info_ptr, 
								uint32 *width, 
								uint32 *height,
								int *bit_depth, 
								int *color_type, 
								int *interlace_method,
								int *compression_method, 
								int *filter_method)
	=NULL;
	
	*(FARPROC*)&png_get_IHDR=(FARPROC)fctLoader.getSymbolAddress(string("png_get_IHDR"));
	if(!png_get_IHDR)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_get_IHDR'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_get_channels)     ( png_struct *png_ptr,
									png_info *info_ptr)
	=NULL;
	*(FARPROC*)&png_get_channels=(FARPROC)fctLoader.getSymbolAddress(string("png_get_channels"));
	if(!png_get_channels)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_get_channels'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_set_strip_16)    (png_struct *png_ptr)
	=NULL;
	*(FARPROC*)&png_set_strip_16=(FARPROC)fctLoader.getSymbolAddress(string("png_set_strip_16"));
	if(!png_set_strip_16)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_set_strip_16'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_set_gray_1_2_4_to_8)    (png_struct *png_ptr)
	=NULL;
	*(FARPROC*)&png_set_gray_1_2_4_to_8=(FARPROC)fctLoader.getSymbolAddress(string("png_set_gray_1_2_4_to_8"));
	if(!png_set_gray_1_2_4_to_8)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_set_gray_1_2_4_to_8'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_get_valid)    ( png_struct *png_ptr,
								png_info *info_ptr, 
								uint32 flag)
	=NULL;
	*(FARPROC*)&png_get_valid=(FARPROC)fctLoader.getSymbolAddress(string("png_get_valid"));
	if(!png_get_valid)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_get_valid'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_set_expand)    (png_struct *png_ptr)
	=NULL;
	*(FARPROC*)&png_set_expand=(FARPROC)fctLoader.getSymbolAddress(string("png_set_expand"));
	if(!png_set_expand)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_set_expand'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_get_gAMA)    (  png_struct *png_ptr,
								png_info *info_ptr, 
								double *file_gamma  )
	=NULL;
	*(FARPROC*)&png_get_gAMA=(FARPROC)fctLoader.getSymbolAddress(string("png_get_gAMA"));
	if(!png_get_gAMA)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_get_gAMA'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_set_gamma)    ( png_struct *png_ptr,
								double screen_gamma, 
								double default_file_gamma)
	=NULL;
	*(FARPROC*)&png_set_gamma=(FARPROC)fctLoader.getSymbolAddress(string("png_set_gamma"));
	if(!png_set_gamma)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_set_gamma'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_read_update_info)    (  png_struct *png_ptr,
										png_info *info_ptr)
	=NULL;
	*(FARPROC*)&png_read_update_info=(FARPROC)fctLoader.getSymbolAddress(string("png_read_update_info"));
	if(!png_read_update_info)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_read_update_info'");
		return 0;
	}

	///////////////////////////

	BOOL (* png_error)    ( png_struct *png_ptr,
							const char *error_message)
	=NULL;
	*(FARPROC*)&png_error=(FARPROC)fctLoader.getSymbolAddress(string("png_error"));
	if(!png_error)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_error'");
		return 0;
	}

	///////////////////////////
	
	BOOL (* png_read_image)    ( png_struct *png_ptr,
								 char **image)
	=NULL;
	*(FARPROC*)&png_read_image=(FARPROC)fctLoader.getSymbolAddress(string("png_read_image"));
	if(!png_read_image)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_read_image'");
		return 0;
	}

	///////////////////////////
	

	BOOL (* png_read_end)    (  png_struct *png_ptr,
								png_info *info_ptr)
	=NULL;
	*(FARPROC*)&png_read_end=(FARPROC)fctLoader.getSymbolAddress(string("png_read_end"));
	if(!png_read_end)
	{
		nlwarning("CBitmap::readPNG : can't find function 'png_read_end'");
		return 0;
	}

	///////////////////////////

	
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



	//set the read functiun
	png_set_read_fn(png_ptr, (void*)&f, readPNGData);


	//set number of bit already read (in order to step back)
	png_set_sig_bytes(png_ptr, 4);



	//read header info and use it
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR( png_ptr, 
				  info_ptr,
				  (uint32*) &_Width,
				  (uint32*) &_Height, 
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
				 (uint32*) &_Width,
				 (uint32*) &_Height,
				 &iBitDepth,
				 &iColorType, 
				 NULL, 
				 NULL, 
				 NULL);

	
	//At this point, the image must converted to an 24bit image RGB


	//allocate memory to load the image
	char **pbRowPointers=new char*[(const uint32)_Height];



	
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
	png_read_image(png_ptr, ppbRowPointers);

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
				_Data[0][row*_Width*4+line*4+3]=(uint8)'255';//add the alpha seting
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
   return iBitDepth*bit;//return the size of a pixel, either 8,24,32 bit
}

/*-------------------------------------------------------------------*\
								readPNGData		
\*-------------------------------------------------------------------*/

void readPNGData(png_struct *png_ptr, char *data, uint length)
{
	((IStream*) png_ptr->io_ptr)->serialBuffer((uint8*)data,length);

}

}//namespace

#endif // NL_OS_WINDOWS
