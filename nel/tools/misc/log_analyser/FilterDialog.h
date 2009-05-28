/** \file FilterDialog.h
 * header file
 *
 * $Id: FilterDialog.h,v 1.1 2002/10/18 12:04:56 cado Exp $
 */

/* Copyright, 2002 Nevrax Ltd.
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
#if !defined(AFX_FILTERDIALOG_H__916C1178_3FEE_4DD0_A4D7_2EE5B39A07D9__INCLUDED_)
#define AFX_FILTERDIALOG_H__916C1178_3FEE_4DD0_A4D7_2EE5B39A07D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilterDialog.h : header file
//

#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CFilterDialog dialog

class CFilterDialog : public CDialog
{
// Construction
public:
	CFilterDialog(CWnd* pParent = NULL);   // standard constructor

	///
	std::vector<CString>	getPosFilter() const;

	///
	std::vector<CString>	getNegFilter() const;

	bool					Trace;
	
// Dialog Data
	//{{AFX_DATA(CFilterDialog)
	enum { IDD = IDD_FILTERDIALOG };
	CString	m_NegFilter;
	CString	m_PosFilter;
	CString	m_Sep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilterDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERDIALOG_H__916C1178_3FEE_4DD0_A4D7_2EE5B39A07D9__INCLUDED_)
