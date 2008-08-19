/** \file win_displayer.h
 * Win32 Implementation of the CWindowDisplayer (look at window_displayer.h)
 *
 * $Id: win_displayer.h,v 1.16 2005/04/04 14:51:47 miller Exp $
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

#ifndef NL_WIN_DISPLAYER_H
#define NL_WIN_DISPLAYER_H

#include "types_nl.h"

#ifdef NL_OS_WINDOWS

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define NOMINMAX
#include <windows.h>

#include "displayer.h"
#include "reader_writer.h"

#include "window_displayer.h"

namespace NLMISC {


/**
 * this displayer displays on a win32 windows.
 * MT = Main Thread, DT = Display Thread
 * \author Vianney Lecroart
 * \author Nevrax France
 * \date 2001
 */
class CWinDisplayer : public NLMISC::CWindowDisplayer
{
public:

	CWinDisplayer (const char *displayerName = "") : CWindowDisplayer(displayerName), Exit(false)
	{
		needSlashR = true;
		createLabel ("@Clear|CLEAR");
	}

	virtual ~CWinDisplayer ();

#ifdef NL_OS_WINDOWS
	HWND getHWnd () const { return _HWnd; }
#endif // NL_OS_WINDOWS

private:

	// called by DT only
	void	resizeLabels ();
	// called by DT only
	void	updateLabels ();

	// called by DT only
	void	open (std::string titleBar, bool iconified, sint x, sint y, sint w, sint h, sint hs, sint fs, const std::string &fn, bool ww, CLog *log);
	// called by DT only
	void	clear ();
	// called by DT only
	void	display_main ();

	virtual void	setTitleBar (const std::string &titleBar);

	virtual void	getWindowPos (uint32 &x, uint32 &y, uint32 &w, uint32 &h);

	// all these variables above is used only by the DT

	HWND _HEdit, _HWnd, _HInputEdit;
	HFONT _HFont;
	HMODULE _HLibModule;

	CLog *Log;

	// the MT must set the value to true to exit the thread
	bool Exit;

	friend LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

} // NLMISC

#endif // NL_OS_WINDOWS

#endif // NL_WIN_DISPLAYER_H

/* End of win_displayer.h */
