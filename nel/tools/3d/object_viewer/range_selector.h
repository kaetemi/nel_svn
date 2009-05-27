/** \file range_selector.h
 * Helps to select a range for numeric values in a CEditableRange dialog
 *
 * $Id: range_selector.h,v 1.2 2001/06/25 12:57:31 vizerie Exp $
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


#if !defined(AFX_RANGE_SELECTOR_H__BF9974E6_D43D_447D_8BC5_625620BDBD8F__INCLUDED_)
#define AFX_RANGE_SELECTOR_H__BF9974E6_D43D_447D_8BC5_625620BDBD8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// range_selector.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRangeSelector dialog

class CRangeSelector : public CDialog
{
// Construction
public:	
	CRangeSelector(const CString &lowerBound, const CString &upperBound, class CEditableRange *er, CWnd* pParent = NULL);   // standard constructor


	const CString &getUpperBound(void) const { return m_UpperBound ; }
	const CString &getLowerBound(void) const { return m_LowerBound ; }

// Dialog Data
	//{{AFX_DATA(CRangeSelector)
	enum { IDD = IDD_SELECT_RANGE };
	CEdit	m_UpperBoundCtrl;
	CEdit	m_LowerBoundCtrl;
	CString	m_LowerBound;
	CString	m_UpperBound;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRangeSelector)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	class CEditableRange *_EditableRange ;	

	// Generated message map functions
	//{{AFX_MSG(CRangeSelector)
	virtual void OnOK();
	afx_msg void OnSetfocusLowerBound();
	afx_msg void OnSetfocusUpperBound();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RANGE_SELECTOR_H__BF9974E6_D43D_447D_8BC5_625620BDBD8F__INCLUDED_)
