/** \file choose_name.h
 * A dialog that allow to choose a name
 *
 * $Id: choose_name.h,v 1.1 2001/09/12 13:25:55 vizerie Exp $
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



#if !defined(AFX_CHOOSE_NAME_H__AF59C290_0134_437B_BACA_3698979572B5__INCLUDED_)
#define AFX_CHOOSE_NAME_H__AF59C290_0134_437B_BACA_3698979572B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// choose_name.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseName dialog

class CChooseName : public CDialog
{
// Construction
public:
	CChooseName(const char *initialName, CWnd* pParent = NULL);   // standard constructor

	std::string getName();

// Dialog Data
	//{{AFX_DATA(CChooseName)
	enum { IDD = IDD_CHOOSE_NAME };
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSE_NAME_H__AF59C290_0134_437B_BACA_3698979572B5__INCLUDED_)
