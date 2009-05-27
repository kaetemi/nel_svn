/** \file color_button.h
 * display a color box...
 *
 * $Id: color_button.h,v 1.3 2001/06/25 13:20:10 vizerie Exp $
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


#if !defined(AFX_COLOR_BUTTON_H__286CFF58_DD7F_4310_95EB_3477F5A2B923__INCLUDED_)
#define AFX_COLOR_BUTTON_H__286CFF58_DD7F_4310_95EB_3477F5A2B923__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "nel/misc/rgba.h"

using NLMISC::CRGBA ;




/////////////////////////////////////////////////////////////////////////////
// CColorButton window

class CColorButton : public CButton
{

// Construction
public:
	CColorButton();

// Attributes
public:
	// set a nex color for the button
	void setColor(CRGBA col) { _Color = col ; Invalidate() ; }

	// get the color of the button
	CRGBA getColor(void) const { return _Color ; }


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorButton();

	// register this custom control to window
	static void CColorButton::registerClass(void) ;

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


	// current color of the button
	CRGBA _Color ;


	// the event proc for basic cbutton...
	static WNDPROC _BasicButtonWndProc ;

	// a hook to create the dialog
	static LRESULT CALLBACK EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) ;


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOR_BUTTON_H__286CFF58_DD7F_4310_95EB_3477F5A2B923__INCLUDED_)
