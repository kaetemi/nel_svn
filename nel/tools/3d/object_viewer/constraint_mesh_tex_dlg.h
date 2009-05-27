/** \file constraint_mesh_tex_dlg.h
 * A dialog for editing constraint meshs texture animation
 *
 * $Id: constraint_mesh_tex_dlg.h,v 1.1 2001/12/18 18:35:55 vizerie Exp $
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


#if !defined(AFX_CONSTRAINT_MESH_TEX_DLG_H__CB61D391_C962_46D1_9587_6145EAF2C4C9__INCLUDED_)
#define AFX_CONSTRAINT_MESH_TEX_DLG_H__CB61D391_C962_46D1_9587_6145EAF2C4C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

namespace NL3D
{
	class CPSConstraintMesh;
}



/////////////////////////////////////////////////////////////////////////////
// CConstraintMeshTexDlg dialog

class CConstraintMeshTexDlg : public CDialog
{
// Construction
public:
	CConstraintMeshTexDlg(NL3D::CPSConstraintMesh *cm, CWnd* pParent = NULL);   // standard constructor
	~CConstraintMeshTexDlg();

	void init(uint x, uint y, CWnd *pParent);
// Dialog Data
	//{{AFX_DATA(CConstraintMeshTexDlg)
	enum { IDD = IDD_CONSTRAINT_MESH_TEX_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstraintMeshTexDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	NL3D::CPSConstraintMesh *_CM; // the constraint mesh being edited
	CDialog					*_CurrDlg; // the current dialog for edition

	//// Create a dialog for global animation at the, discarding any previous dialog
	void	createGlobalAnimationDlg(uint stage);

	void   setupDlg();


	// Generated message map functions
	//{{AFX_MSG(CConstraintMeshTexDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCurrentStage();
	afx_msg void OnSelchangeTexAnimType();
	afx_msg void OnReinitWhenNewElementIsCreated();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTRAINT_MESH_TEX_DLG_H__CB61D391_C962_46D1_9587_6145EAF2C4C9__INCLUDED_)
