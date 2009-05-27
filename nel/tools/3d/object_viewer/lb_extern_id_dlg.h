/** \file lb_extern_id_dlg.h
 * A dialog for assigning ID to objects in a particle system
 *
 * $Id: lb_extern_id_dlg.h,v 1.3 2001/12/18 18:38:00 vizerie Exp $
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
//

#if !defined(AFX_LB_EXTERN_ID_DLG_H__A045B811_4473_4F2B_A27E_580B4407837C__INCLUDED_)
#define AFX_LB_EXTERN_ID_DLG_H__A045B811_4473_4F2B_A27E_580B4407837C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

namespace NL3D
{
	class CPSLocatedBindable;
}

/////////////////////////////////////////////////////////////////////////////
// CLBExternIDDlg dialog

class CLBExternIDDlg : public CDialog
{
// Construction
public:
	CLBExternIDDlg(uint32 id, CWnd* pParent = NULL);   // standard constructor

	uint32 getNewID(void) const { return _ID; } // the id after edition by this dialog
// Dialog Data
	//{{AFX_DATA(CLBExternIDDlg)
	enum { IDD = IDD_LB_EXTERN_ID };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLBExternIDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:	
	uint32					  _ID; // the current ID

	// Generated message map functions
	//{{AFX_MSG(CLBExternIDDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEnableExternId();
	afx_msg void OnChangeIdValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LB_EXTERN_ID_DLG_H__A045B811_4473_4F2B_A27E_580B4407837C__INCLUDED_)
