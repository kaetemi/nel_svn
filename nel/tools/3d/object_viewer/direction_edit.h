/** \file direction_edit.h
 * a dialog to choose a direction (normalized vector).
 *
 * $Id: direction_edit.h,v 1.2 2001/09/17 14:02:00 vizerie Exp $
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

#if !defined(AFX_DIRECTION_EDIT_H__D494432C_2D31_4725_BEE7_E042C1F7845F__INCLUDED_)
#define AFX_DIRECTION_EDIT_H__D494432C_2D31_4725_BEE7_E042C1F7845F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 
#include "ps_wrapper.h"
namespace NLMISC
{
	class CVector ;
}


class CDirectionAttr ;
struct IPopupNotify;

/////////////////////////////////////////////////////////////////////////////
// CDirectionEdit dialog


class CDirectionEdit : public CDialog
{
// Construction
public:
	
	CDirectionEdit(IPSWrapper<NLMISC::CVector> *wrapper) ;   // standard constructor

	void init(IPopupNotify *p, CWnd *parent) ;

// Dialog Data
	//{{AFX_DATA(CDirectionEdit)
	enum { IDD = IDD_DIRECTION_EDIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectionEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// the mouse state
	enum State { Wait, Drag } _MouseState ;

	IPopupNotify *_Parent ;

	// select a new vect from a point (must be in the basis)
	void selectNewVect(const CPoint &pos) ;


	IPSWrapper<NLMISC::CVector> *_Wrapper ;
	// Generated message map functions
	//{{AFX_MSG(CDirectionEdit)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTION_EDIT_H__D494432C_2D31_4725_BEE7_E042C1F7845F__INCLUDED_)
