/** \file i18n/main.cpp
 * example of the NeL internationalisation features
 *
 * $Id: main.cpp,v 1.2 2004/12/28 15:07:03 lecroart Exp $
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

#include <stdio.h>
#include <stdlib.h>

// contains all i18n features
#include "nel/misc/i18n.h"

using namespace NLMISC;

int main (int argc, char **argv)
{
	// set the path were the .uxt are
	CI18N::setPath("./");
	
	// get all language names (you must call this before calling load())
	const std::vector<ucstring> languages = CI18N::getLanguageNames ();

	if (languages.empty())
	{
		printf ("No language evailable, can't do anything, press <return> to exit\n");
		getchar();
		return EXIT_FAILURE;
	}

	nlinfo ("%d languages are available:", languages.size());
	for (uint i = 0; i < languages.size(); i++)
	{
		nlinfo (" %d - %s", i, languages[i].toString().c_str());
	}
	nlinfo ("Please, type a number between 0 and %d and then press <return>", languages.size()-1);

	// Get the selected language (i know there s a potentiel buffer overflow)
	char  buf[1024];
	gets (buf);

	uint languageNumber = atoi (buf);

	// load the language
	CI18N::load (languageNumber);

	// display "Salut" that is the "hi" string in the selected language (french).
	nlinfo (CI18N::get("hi").toString().c_str ());

	// display "rms est un master", the french version of the string
	nlinfo (CI18N::get("%s is proud to present you NeL Internationalisation system").toString().c_str (), "Ace");

	nlinfo (CI18N::get("press <return> to exit").toString().c_str ());
	getchar ();

	return EXIT_SUCCESS;
}
