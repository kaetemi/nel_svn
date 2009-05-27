/** \file dialog_stack.h
 * for dialog that create multiple sub-dialog, this helps to record them,
 * and to properly destroy them
 *
 * $Id: dialog_stack.h,v 1.1 2001/06/25 13:19:27 vizerie Exp $
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


#ifndef DIALOG_STACK_H
#define DIALOG_STACK_H


/** this helps to record dynamically created window or dialog
  * Just deriv from this and call the method pushWnd to register a new window
  * They'll be deleted in the dtor
  */


class CDialogStack
{
	public:
		void pushWnd(CWnd *wnd)
		{
			// a window must be registered only once
			nlassert(std::find(_WndList.begin(), _WndList.end() , wnd) == _WndList.end()) ; 			
			_WndList.push_back(wnd) ;
		}

		~CDialogStack()
		{
			for (std::vector<CWnd *>::iterator it = _WndList.begin() ; it != _WndList.end() ; ++it)
			{
				(*it)->DestroyWindow() ;
				delete *it ;
			}
		}

	protected:

		std::vector<CWnd *> _WndList ;

} ;

#endif