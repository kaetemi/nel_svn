/** \file debug/main.cpp
 * example of the NeL debug features
 *
 * $Id: main.cpp,v 1.1 2002/04/17 08:08:32 lecroart Exp $
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

// contains all debug features
#include "nel/misc/debug.h"

using namespace NLMISC;

int main (int argc, char **argv)
{
	// all debug functions have different behaviors in debug and in release mode.
	// in general, in debug mode, all debug functions are active, they display
	// what happens and some break the program to debug it. In release mode, they often
	// do nothing to increase the execution speed.


	// this function initializes debug functions. it adds displayers into the debug
	// logger.
	// in debug mode, all debug functions display on the std output.
	// in release mode, this function does nothing by default. you have to add a displayer
	// manually, or put true in the parameter to say to the function that you want it to
	// add the default displayers
	createDebug ();

	// display debug information, that will be skipped in release mode.
	nldebug ("nldebug() %d", 1);

	// display the string
	nlinfo ("nlinfo() %d", 2);

	// when something not normal, but that the program can manage, occurs, call nlwarning()
	nlwarning ("nlwarning() %d", 3);

	// nlassert() is like assert but do more powerful things. in release mode, the test is
	// not executed and nothing will happen. (Press F5 in Visual C++ to continue the execution)
	nlassert (true == false);

	// in a switch case or when you want that the program never executes a part of code, use stop.
	// in release, nlstop does nothing. in debug mode,
	// if the code reaches the nlstop, a breakpoint will be set. (In Visual C++ press F5 to continue)
	nlstop;

	// when the program failed, call nlerror(), it displays the message and throws a EFatalError to
	// exit the program. don't forget to put a try/catch block everywhere an nlerror could
	// occurs. (In Visual C++ press F5 to continue)
	try
	{
		nlerror ("nlerror() %d", 4);
	}
	catch(EFatalError &)
	{
		// just continue...
		nlinfo ("nlerror() generated an EFatalError exception, just ignore it");
	}

	printf("\nPress <return> to exit\n");
	getchar ();

	return EXIT_SUCCESS;
}
