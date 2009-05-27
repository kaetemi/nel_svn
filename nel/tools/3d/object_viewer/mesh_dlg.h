/** \file mesh_dlg.h
 * A dialog that allows to choose a mesh (for mesh particles), and display the current mesh name 
 * $Id: mesh_dlg.h,v 1.4 2005/02/16 17:05:33 vizerie Exp $
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

#if !defined(AFX_MESH_DLG_H__27F79AAD_DEA7_4A3E_85E9_9DB32B9419C5__INCLUDED_)
#define AFX_MESH_DLG_H__27F79AAD_DEA7_4A3E_85E9_9DB32B9419C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "popup_notify.h"
#include "particle_dlg.h"
#include "particle_workspace.h"
#include "color_static.h"

namespace NL3D
{
	struct CPSShapeParticle;
}

class CEditMorphMeshDlg;

/////////////////////////////////////////////////////////////////////////////
// CMeshDlg dialog

class CMeshDlg : public CDialog, IPopupNotify
{
// Construction
public:
	CMeshDlg(CParticleWorkspace::CNode *ownerNode, NL3D::CPSShapeParticle *sp, CParticleDlg  *particleDlg);   // standard constructor
	~CMeshDlg();

	void init(CWnd *pParent, sint x, sint y);

	BOOL EnableWindow( BOOL bEnable);

// Dialog Data
	//{{AFX_DATA(CMeshDlg)
	enum { IDD = IDD_CHOOSE_MESH };
	CColorStatic	m_MeshErrorMsg;
	CString	m_ShapeName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeshDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	// utility function : string from shape error code
	static CString getShapeErrorString(sint errorCode);

// Implementation
protected:
	CParticleWorkspace::CNode *_Node;
	CParticleDlg			  *_ParticleDlg;
	NL3D::CPSShapeParticle	  *_ShapeParticle;
	CEditMorphMeshDlg		  *_EMMD;
	void updateForMorph();
	virtual void childPopupClosed(CWnd *child);
	// Generated message map functions
	//{{AFX_MSG(CMeshDlg)
	afx_msg void OnBrowseShape();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnableMorphing();
	afx_msg void OnEditMorph();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void updateModifiedFlag() { if (_Node) _Node->setModified(true); }
	void touchPSState();
	void updateMeshErrorString();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH_DLG_H__27F79AAD_DEA7_4A3E_85E9_9DB32B9419C5__INCLUDED_)
