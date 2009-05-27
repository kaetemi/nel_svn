/** \file ps_global_color_dlg.h
 * This dialog helps to tune the global color of the system depending on its distance.
 * $Id: ps_global_color_dlg.h,v 1.3 2004/06/17 08:05:06 vizerie Exp $
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


#if !defined(AFX_PS_GLOBAL_COLOR_DLG_H__A0259E2D_877E_418E_B8A4_202615C5D141__INCLUDED_)
#define AFX_PS_GLOBAL_COLOR_DLG_H__A0259E2D_877E_418E_B8A4_202615C5D141__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "dialog_stack.h"
#include "ps_wrapper.h"
#include "particle_workspace.h"

namespace NL3D
{
	class CParticleSystem;
}

struct IPopupNotify;

class CPSGlobalColorDlg : public CDialog, public CDialogStack
{
// Construction
public:
	CPSGlobalColorDlg(CParticleWorkspace::CNode *ownerNode, IPopupNotify *pn, CWnd* pParent = NULL);   // standard constructor

	void init(CWnd *pParent);
// Dialog Data
	//{{AFX_DATA(CPSGlobalColorDlg)
	enum { IDD = IDD_GLOBAL_COLOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSGlobalColorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CParticleWorkspace::CNode *_Node;	
	IPopupNotify			  *_PN;
	// Generated message map functions
	//{{AFX_MSG(CPSGlobalColorDlg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	struct CGlobalColorWrapper : public IPSSchemeWrapperRGBA
	{
		NL3D::CParticleSystem *PS;
		virtual scheme_type *getScheme(void) const;
		virtual void setScheme(scheme_type *s);
	}
	_GlobalColorWrapper;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PS_GLOBAL_COLOR_DLG_H__A0259E2D_877E_418E_B8A4_202615C5D141__INCLUDED_)
