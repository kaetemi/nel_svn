/** \file constraint_mesh_dlg.h
 * A dialog for editing constraint meshs
 *
 * $Id: constraint_mesh_dlg.h,v 1.2 2001/12/18 18:34:34 vizerie Exp $
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


#if !defined(AFX_CONSTRAINT_MESH_DLG_H__AF195682_84F3_4269_BB39_BDE74391B7DA__INCLUDED_)
#define AFX_CONSTRAINT_MESH_DLG_H__AF195682_84F3_4269_BB39_BDE74391B7DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

namespace NL3D
{
	class CPSConstraintMesh;
}

/////////////////////////////////////////////////////////////////////////////
// CConstraintMeshDlg dialog

class CConstraintMeshDlg : public CDialog
{
// Construction
public:
	CConstraintMeshDlg(NL3D::CPSConstraintMesh *cm, CWnd* pParent = NULL);   // standard constructor

	/// init the dialog at the given position
	void init(sint x, sint y, CWnd *pParent);


// Dialog Data
	//{{AFX_DATA(CConstraintMeshDlg)
	enum { IDD = IDD_CONSTRAINT_MESH_DLG };
	BOOL	m_ForceStage0Modulation;
	BOOL	m_ForceStage1Modulation;
	BOOL	m_ForceStage2Modulation;
	BOOL	m_ForceStage3Modulation;
	BOOL	m_ForceVertexColorLighting;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstraintMeshDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	NL3D::CPSConstraintMesh *_CM; // the constraint mesh being edited
	// Generated message map functions
	//{{AFX_MSG(CConstraintMeshDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnForceStage0Modulation();
	afx_msg void OnForceStage1Modulation();
	afx_msg void OnForceStage2Modulation();
	afx_msg void OnForceStage3Modulation();
	afx_msg void OnForceVertexColorLighting();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTRAINT_MESH_DLG_H__AF195682_84F3_4269_BB39_BDE74391B7DA__INCLUDED_)
