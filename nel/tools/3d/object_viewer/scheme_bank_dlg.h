/** \file scheme_bank_dlg.h
 * Dialog used to manage a bank of attributes makers in a particle system
 *
 * $Id: scheme_bank_dlg.h,v 1.3 2001/12/18 18:40:31 vizerie Exp $
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


#if !defined(AFX_SCHEME_BANK_DLG_H__C3639E36_1266_4D32_9CC3_5B9E3CD79F93__INCLUDED_)
#define AFX_SCHEME_BANK_DLG_H__C3639E36_1266_4D32_9CC3_5B9E3CD79F93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

namespace NL3D
{
	class CPSAttribMakerBase;
}

class CSchemeBankDlg : public CDialog
{
// Construction
public:
	CSchemeBankDlg(const std::string &type, CWnd* pParent = NULL);   // standard constructor


	// get the scheme that has been selected, or NULL if none
	NL3D::CPSAttribMakerBase  *getSelectedScheme() { return _CurrScheme; }

	void buildList();


// Dialog Data
	//{{AFX_DATA(CSchemeBankDlg)
	enum { IDD = IDD_SCHEME_BANK_DLG };
	CListBox	m_SchemeList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchemeBankDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	std::string				  _Type;
	NL3D::CPSAttribMakerBase  *_CurrScheme;
	// Generated message map functions
	//{{AFX_MSG(CSchemeBankDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSchemeList();
	afx_msg void OnSaveBank();
	afx_msg void OnLoadBank();
	afx_msg void OnRemove();
	afx_msg void OnRename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEME_BANK_DLG_H__C3639E36_1266_4D32_9CC3_5B9E3CD79F93__INCLUDED_)
