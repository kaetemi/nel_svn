/** \file attrib_list_box.h
 * A list box that can be filled with owner drawn items. Just provide a interface for drawing
 *
 * $Id: attrib_list_box.h,v 1.3 2001/06/25 13:15:00 vizerie Exp $
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

#if !defined(AFX_ATTRIB_LIST_BOX_H__0927B20B_FD26_433B_856B_6EF2871C233E__INCLUDED_)
#define AFX_ATTRIB_LIST_BOX_H__0927B20B_FD26_433B_856B_6EF2871C233E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// attrib_list_box.h : header file
//

class CValueGradientDlg ;
struct IValueGradientDlgClient ;

/////////////////////////////////////////////////////////////////////////////
// CAttribListBox window

class CAttribListBox : public CListBox
{
public:	
	/// a function that can display a value in a gradient, with the given offset
	typedef void (* TDisplayValue)(CDC *dc, uint index, sint x, sint y, void *lParam) ;


// Construction
public:
	CAttribListBox();

// Attributes
public:

// Operations
public:

	void setDrawer(IValueGradientDlgClient *drawer)
	{
		_DrawerInterface = drawer ;
	}

	void setCtrlID(uint id) { _Id = id ; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttribListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAttribListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAttribListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


	IValueGradientDlgClient *_DrawerInterface ;	
	uint _Id ;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTRIB_LIST_BOX_H__0927B20B_FD26_433B_856B_6EF2871C233E__INCLUDED_)
