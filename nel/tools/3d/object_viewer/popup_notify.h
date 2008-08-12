/** \file popup_notify.h
 * an interface to now when popup windows are removed
 *
 * $Id: popup_notify.h,v 1.2 2001/12/18 18:39:43 vizerie Exp $
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


#ifndef POPUP_NOTIFY_H
#define POPUP_NOTIFY_H

class CWnd;

// this interface allow windows to be notified when one of their popup ha been removed
struct IPopupNotify
{
	/// call when the window implementing this has been destroyed
	virtual void childPopupClosed(CWnd *child) = 0;
};


#endif