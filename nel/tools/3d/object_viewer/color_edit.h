/** \file color_edit.h
 * a dialog to edit a color (or call the windows color dialog)
 *
 * $Id: color_edit.h,v 1.8 2001/12/19 17:51:32 vizerie Exp $
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


#if !defined(AFX_COLOR_EDIT_H__50C45CFE_2188_4161_B565_C773FE029BF3__INCLUDED_)
#define AFX_COLOR_EDIT_H__50C45CFE_2188_4161_B565_C773FE029BF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// color_edit.h : header file
//

#include "nel/misc/rgba.h"

using NLMISC::CRGBA ;

#include "edit_attrib_dlg.h"
#include "color_button.h"
#include "ps_wrapper.h"
#include "edit_ex.h"

/////////////////////////////////////////////////////////////////////////////
// CColorEdit dialog


class CColorButton ;

class CColorEdit : public CEditAttribDlg, CEditEx::IListener
{
// Construction
public:
	// construct the dialog.
	CColorEdit(CWnd* pParent = NULL);   // standard constructor


	// inherited from CEditAttribDlg
	virtual void init(uint32 x, uint32 y, CWnd *pParent) ;

// Dialog Data
	//{{AFX_DATA(CColorEdit)
	enum { IDD = IDD_COLOR_EDIT };
	CEditEx	m_BlueEditCtrl;
	CEditEx	m_AlphaEditCtrl;
	CEditEx	m_GreenEditCtrl;
	CEditEx	m_RedEditCtrl;
	CScrollBar	m_AlphaCtrl;
	CScrollBar	m_GreenCtrl;
	CScrollBar	m_BlueCtrl;
	CScrollBar	m_RedCtrl;
	CColorButton	m_Color;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation


public:
	// set a wrapper to get the datas
	void setWrapper(IPSWrapperRGBA *wrapper) { _Wrapper = wrapper ; }
	

protected:
	/// inherited from CEditEx::IListener
	virtual void editExValueChanged(CEditEx *ctrl);
	CColorButton &getColorCtrl(void) { return  * (CColorButton *) GetDlgItem(IDC_PARTICLE_COLOR) ; }
	void updateEdits();
	
	// wrapper to the datas
	IPSWrapperRGBA *_Wrapper ;

	// once the xrapper has been set, this display the basis
	void updateColorFromReader(void) ;

	// Generated message map functions
	//{{AFX_MSG(CColorEdit)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBrowseColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOR_EDIT_H__50C45CFE_2188_4161_B565_C773FE029BF3__INCLUDED_)
