/** \file logic_editor_interface.cpp
 *
 * $Id: logic_editor_interface.h,v 1.1 2002/02/14 13:25:55 corvazier Exp $
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

#ifndef LOGIC_EDITOR_INTERFACE
#define LOGIC_EDITOR_INTERFACE

#ifndef LOGIC_EDITOR_EXPORT
#define LOGIC_EDITOR_EXPORT __declspec( dllimport ) 
#endif // LOGIC_EDITOR_EXPORT

// Increment this version number each time you distribute a new version of the dll.
#define LOGIC_EDITOR_VERSION 2



/**
 * ILogicEditor
 *
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2001
 */
class ILogicEditor
{
public:
	virtual ~ILogicEditor () {}

	// Init the UI
	virtual void initUI (HWND parent=NULL)=0;

	// Init the UI Light version
	virtual void initUILight (int x, int y, int cx, int cy)=0;

	// Go
	virtual void go ()=0;

	// Release the UI
	virtual void releaseUI ()=0;

	// Get the main frame
	virtual void*getMainFrame ()=0;

	// load a logic file
	virtual void loadFile( const char * fileName ) = 0;

	// create a default file
	virtual void createDefaultFile( const char * filename = "logic.logic ") = 0;
	
	// Get instance
	static LOGIC_EDITOR_EXPORT ILogicEditor * getInterface( int version = LOGIC_EDITOR_VERSION );

	// Release instance
	static LOGIC_EDITOR_EXPORT void releaseInterface( ILogicEditor * logicEditor );
};


// To export the names in a good format that can be human readable and not with the heavy style
// of the MFC we have to do it in 'old-school' mode
extern "C" 
{
	LOGIC_EDITOR_EXPORT ILogicEditor * ILogicEditorGetInterface( int version = LOGIC_EDITOR_VERSION);
	LOGIC_EDITOR_EXPORT void ILogicEditorReleaseInterface( ILogicEditor * pWE );
} 


#endif LOGIC_EDITOR_INTERFACE
