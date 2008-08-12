/** \file dummy_window.h
 *
 * $Id: dummy_window.h,v 1.2 2007/05/09 15:31:57 boucher Exp $
 */

/* Copyright, 2000-2007 Nevrax Ltd.
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

#ifndef NL_DUMMY_WINDOW_H
#define NL_DUMMY_WINDOW_H


#include "nel/misc/types_nl.h"

#ifdef NL_OS_WINDOWS // for win32 os only

#include <windows.h>


namespace NLMISC
{

/** A simple invisible win32 window, with an optionnal message handling function.
  * Possible uses include :
  * - Creating an icon in the tray (require a window to be passed)
  * - Creating a message queue (in order to use an IPC mechanism such as WM_COPYDATA)
  * - etc.
  *
  * \author Nicolas Vizerie
  * \author Nevrax France
  * \date 2007
  */
class CDummyWindow
{
public:	
	CDummyWindow();
	/** Init a dummy window, with an optionnal message handling procedure
	  * \return true on success
	  */
	bool init(HINSTANCE hInstance, WNDPROC winProc = NULL);
	// release this window
	void release();
	~CDummyWindow();
	// Get this window handle
	HWND getWnd() const { return _HWnd; }
private:
	HWND _HWnd;
};


} // NLMISC


#endif // NL_OS_WINDOWS


#endif
