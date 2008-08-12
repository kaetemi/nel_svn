/** \file font/main.cpp
 * Example of font management *without* using the user interface.
 * This example is deprecated because the new way to use font is to pass though the user interface.
 *
 * $Id: main.cpp,v 1.1 2002/04/17 08:08:31 lecroart Exp $
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

#include <stdlib.h>
#include <string>

#include "nel/misc/types_nl.h"

// look at event example
#include "nel/misc/event_emitter.h"
#include "nel/misc/event_listener.h"

// look at 3dinit example
#include "3d/nelu.h"

// used for font management
#include "3d/font_manager.h"
#include "3d/computed_string.h"
#include "3d/text_context.h"

using namespace std;
using namespace NL3D;
using namespace NLMISC;

int main (int argc, char **argv)
{
	// look at 3dinit example
	CNELU::init (800, 600, CViewport(), 32, true); 

	// create a font manager
	CFontManager fontManager;

	// set the font cache to 2 megabytes (default is 1mb)
	fontManager.setMaxMemory(2000000);
	
	CTextContext tc;

	tc.init (CNELU::Driver, &fontManager);

	// The first param is the font name (could be ttf, pfb, fon, etc...). The
	// second one is optionnal, it's the font kerning file
	tc.setFontGenerator ("n019003l.pfb", "n019003l.afm");

	// create the first computed string.
	// A computed string is a string with a format and it generates the string
	// into a texture. First param is the string or ucstring (unicode string).
	// Second is a pointer to a font generator. 3rd is the color of the font.
	// 4th is the size of the font. 5th is a pointer to the video driver.
	// 6th is the resulting computed string.
	CComputedString cptedString1;
	fontManager.computeString ("Nevrax", tc.getFontGenerator(), CRGBA(255,255,255), 70, CNELU::Driver, cptedString1);

	CComputedString cptedString3d;
	fontManager.computeString ("3d string!!!", tc.getFontGenerator(), CRGBA(255,127,0), 75, CNELU::Driver, cptedString3d);

	ucstring ucs;
	ucs = 28000;
	ucs += 28108;
	ucs += 28188;
	ucs += 28858;
	// generate an unicode string. You can see it only if you have an unicode font.
	// we haven't find a GPL unicode font yet :(
	CComputedString cptedString4;
	fontManager.computeString (ucs, tc.getFontGenerator(), CRGBA(32,64,127), 75, CNELU::Driver, cptedString4);

/*
	CComputedString cptedString[10];
	for (uint i = 0; i < 10; i++)
		fontManager.computeString ("Nevrax", &fontGenerator, CRGBA(255,255,255), i*10, CNELU::Driver, cptedString[i]);
*/



	// look at event example
	CNELU::EventServer.addEmitter(CNELU::Driver->getEventEmitter());
	CNELU::AsyncListener.addToServer(CNELU::EventServer);
	
	do
	{
		// look at 3dinit example
		CNELU::clearBuffers(CRGBA(0,0,0));

		// now, every frame, we have to render the computer string.

		static float x=0, y=0, z=0;
		x+=0.01f; y+=0.1f, z+=0.001f;
		CMatrix m;
		m.identity();
		m.translate(CVector(0.7f*4.0f/3.0f, 0.5, 0.5));
		m.rotateX(x);
		m.rotateY(y);
		m.rotateZ(z);
		// display a string in 3d
		// first param is a pointer to the driver. second one is
		// the matrix transormation for the string
		cptedString3d.render3D (*CNELU::Driver, m);

		// the first param is a pointer to a driver. second one is the x position
		// (between (0.0 (left) and 1.0 (right)). third one is the y position (between
		// 0.0 (bottom) and 1.0 (top)).
		tc.setColor (CRGBA (255, 255, 255));
		tc.setFontSize (40);
		tc.setHotSpot (CComputedString::BottomLeft);
		tc.printAt (0.5f, 0.7f, string("Nevrax"));

		// the fourth param is the position of the hotspot, the text will be displayed at x,y
		// depending on the hotspot
		tc.setColor (CRGBA (0, 0, 255));
		tc.setFontSize (40);
		tc.setHotSpot (CComputedString::BottomLeft);
		tc.printAt (0.0f, 0.0f, string("NeL"));

		static float scale=1.0f, way=0.01f;
		scale+=way;
		if (scale>5 || scale < 1) way = -way;
		// the 5th and 6th params are the scale of the texture

		tc.setColor (CRGBA (200, 255, 64));
		tc.setFontSize (20);
		tc.setHotSpot (CComputedString::BottomLeft);
		tc.setScaleX (scale);
		tc.setScaleZ (scale);
		tc.printAt (0.1f, 0.3f, string("Nevrax Library"));
		
		// display the same string with no scale
		tc.setHotSpot (CComputedString::TopLeft);
		tc.setScaleX (1.0f);
		tc.setScaleZ (1.0f);
		tc.printAt (0.1f, 0.2f, string("Nevrax Library"));

		// the 7th params is the rotation in radian
		static float angle=0.0f;
		angle+=0.01f;
		cptedString1.render2D (*CNELU::Driver, 0.2f, 0.7f, CComputedString::MiddleMiddle, 1, 1, angle);

		// display the unicode string
		tc.setColor (CRGBA (32, 64, 127));
		tc.setFontSize (70);
		tc.setHotSpot (CComputedString::MiddleRight);
		tc.printAt (1.0f, 0.2f, ucs);
/*
		uint i;
		for (i = 0; i < 10; i++)
		{
			fontManager.computeString ("Nevrax", &fontGenerator, CRGBA(255,255,255), i*10, CNELU::Driver, cptedString[i]);
			cptedString[i].render2D (*CNELU::Driver, 0.0f, i/10.0f, CComputedString::MiddleLeft);
		}

		for (i = 0; i < 10; i++)
			cptedString[i].render2D (*CNELU::Driver, 0.5f, i/10.0f, CComputedString::MiddleLeft);
*/
		tc.setColor (CRGBA (255, 127, 0));
		tc.setFontSize (20);
		tc.setHotSpot (CComputedString::BottomRight);
		tc.printAt (0.99f, 0.01f, string("Press <ESC> to quit"));

		// look 3dinit example
		CNELU::swapBuffers();
		CNELU::screenshot();
		
		// look at event example
		CNELU::EventServer.pump();
	}
	while(!CNELU::AsyncListener.isKeyPushed(KeyESCAPE));

	fontManager.dumpCache ("ok.tga");

	// look at event example
	CNELU::AsyncListener.removeFromServer(CNELU::EventServer);

	// look at 3dinit example
	CNELU::release();

	return EXIT_SUCCESS;
}
