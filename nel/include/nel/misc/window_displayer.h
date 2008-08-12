/** \file window_displayer.h
 * Implementation of the CDisplayer (look at displayer.h) that display on a Windows.
 * It's the base class for win_displayer (win32 api) and gtk_displayer (gtk api)
 *
 * $Id: window_displayer.h,v 1.18 2005/02/22 10:14:12 besson Exp $
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

#ifndef NL_WINDOW_DISPLAYER_H
#define NL_WINDOW_DISPLAYER_H

#include "types_nl.h"
#include "common.h"
#include "debug.h"

#include "displayer.h"
#include "mutex.h"
#include "thread.h"

namespace NLMISC {


/**
 * this displayer displays on a win32 windows.
 * MT = Main Thread, DT = Display Thread
 * \author Vianney Lecroart
 * \author Nevrax France
 * \date 2001
 */
class CWindowDisplayer : public NLMISC::IDisplayer
{
public:

	CWindowDisplayer (const char *displayerName = "") :
	  IDisplayer(displayerName), 
		_Buffer("CWindowDisplayer::_Buffer"), _Labels("CWindowDisplayer::_Labels"), _CommandsToExecute("CWindowDisplayer::_CommandsToExecute"),
		_Continue(true), _PosInHistory(0), _Init(false), _HistorySize(0), _ToolBarHeight(22), _InputEditHeight(25), _Thread(0), Log(0)
	  { }

	virtual ~CWindowDisplayer ();

	// open the window and run the display thread (MT)
	void	create (std::string titleBar = "", bool iconified = false, sint x = -1, sint y = -1, sint w = -1, sint h = -1, sint hs = -1, sint fs = 0, const std::string &fn = "", bool ww = false, CLog *log = InfoLog);

	// create a new label. empty string mean separator. start with @ means that is a command (MT)
	uint	createLabel (const char *value = "?");

	// change the value of a label (MT)
	void	setLabel (uint label, const std::string &value);

	// execute user commands (MT) return false to quit
	bool	update ();

	// set a special title to the window bar
	virtual void	setTitleBar (const std::string &titleBar) { }

	virtual void	getWindowPos (uint32 &x, uint32 &y, uint32 &w, uint32 &h) { x=y=w=h=0; }

protected:

	// display a string (MT)
	virtual void doDisplay (const NLMISC::CLog::TDisplayInfo &args, const char *message);

	// true for windows
	bool needSlashR;

	struct CLabelEntry
	{
		CLabelEntry (const std::string &value) : Hwnd(NULL), Value(value), NeedUpdate(true) { }
		void		*Hwnd;
		std::string	 Value;
		bool		 NeedUpdate;
	};

	// buffer that contains the text that the DT will have to display
	// uint32 is the color of the string
	CSynchronized<std::list<std::pair<uint32, std::string> > >	_Buffer;
	CSynchronized<std::vector<CLabelEntry> >						_Labels;
	CSynchronized<std::vector<std::string> >						_CommandsToExecute;

	// called by DT only
	virtual void	open (std::string titleBar, bool iconified, sint x, sint y, sint w, sint h, sint hs, sint fs, const std::string &fn, bool ww, CLog *log) = 0;
	// called by DT only
	virtual void	display_main () = 0;

	// all these variables above is used only by the DT

	bool _Continue;

	std::vector<std::string>	_History;
	uint						_PosInHistory;
	bool _Init;
	sint _HistorySize;
	sint _ToolBarHeight;
	sint _InputEditHeight;

	// the thread used to update the display
	NLMISC::IThread *_Thread;

	CLog *Log;

	friend class CUpdateThread;
};

} // NLMISC

#endif // NL_WINDOW_DISPLAYER_H

/* End of window_displayer.h */
