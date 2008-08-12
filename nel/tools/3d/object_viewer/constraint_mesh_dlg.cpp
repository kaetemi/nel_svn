/** \file constraint_mesh_dlg.cpp
 * A dialog for editing constraint meshs
 *
 * $Id: constraint_mesh_dlg.cpp,v 1.4 2007/03/19 09:55:26 boucher Exp $
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


#include "std_afx.h"
#include "object_viewer.h"
#include "constraint_mesh_dlg.h"

#include "nel/../../src/3d/ps_mesh.h"


//============================================================================================
CConstraintMeshDlg::CConstraintMeshDlg(NL3D::CPSConstraintMesh *cm, CWnd* pParent /*=NULL*/)
	: _CM(cm), CDialog(CConstraintMeshDlg::IDD, pParent)
{
	nlassert(_CM);
	//{{AFX_DATA_INIT(CConstraintMeshDlg)
	m_ForceStage0Modulation = _CM->isStageModulationForced(0);
	m_ForceStage1Modulation = _CM->isStageModulationForced(1);
	m_ForceStage2Modulation = _CM->isStageModulationForced(2);
	m_ForceStage3Modulation = _CM->isStageModulationForced(3);
	m_ForceVertexColorLighting = _CM->isVertexColorLightingForced();
	//}}AFX_DATA_INIT
}

//============================================================================================
void CConstraintMeshDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstraintMeshDlg)
	DDX_Check(pDX, IDC_FORCE_STAGE_0_MODULATION, m_ForceStage0Modulation);
	DDX_Check(pDX, IDC_FORCE_STAGE_1_MODULATION, m_ForceStage1Modulation);
	DDX_Check(pDX, IDC_FORCE_STAGE_2_MODULATION, m_ForceStage2Modulation);
	DDX_Check(pDX, IDC_FORCE_STAGE_3_MODULATION, m_ForceStage3Modulation);
	DDX_Check(pDX, IDC_FORCE_VERTEX_COLOR_LIGHTING, m_ForceVertexColorLighting);
	//}}AFX_DATA_MAP
}

//============================================================================================
void CConstraintMeshDlg::init(sint x, sint y, CWnd *pParent)
{
	Create(IDD_CONSTRAINT_MESH_DLG, pParent);
	RECT r;
	GetClientRect(&r);	
	MoveWindow(x, y, r.right, r.bottom);		
	ShowWindow(SW_SHOW);	
}

BEGIN_MESSAGE_MAP(CConstraintMeshDlg, CDialog)
	//{{AFX_MSG_MAP(CConstraintMeshDlg)
	ON_BN_CLICKED(IDC_FORCE_STAGE_0_MODULATION, OnForceStage0Modulation)
	ON_BN_CLICKED(IDC_FORCE_STAGE_1_MODULATION, OnForceStage1Modulation)
	ON_BN_CLICKED(IDC_FORCE_STAGE_2_MODULATION, OnForceStage2Modulation)
	ON_BN_CLICKED(IDC_FORCE_STAGE_3_MODULATION, OnForceStage3Modulation)
	ON_BN_CLICKED(IDC_FORCE_VERTEX_COLOR_LIGHTING, OnForceVertexColorLighting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//============================================================================================
BOOL CConstraintMeshDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConstraintMeshDlg::OnForceStage0Modulation() 
{
	UpdateData();
	_CM->forceStageModulationByColor(0, m_ForceStage0Modulation ? true : false /* VC  WARNING */);	
}

void CConstraintMeshDlg::OnForceStage1Modulation() 
{
	UpdateData();
	_CM->forceStageModulationByColor(1, m_ForceStage0Modulation ? true : false /* VC  WARNING */);		
}

void CConstraintMeshDlg::OnForceStage2Modulation() 
{
	UpdateData();
	_CM->forceStageModulationByColor(2, m_ForceStage0Modulation ? true : false /* VC  WARNING */);		
}

void CConstraintMeshDlg::OnForceStage3Modulation() 
{
	UpdateData();
	_CM->forceStageModulationByColor(3, m_ForceStage0Modulation ? true : false /* VC  WARNING */);		
}

void CConstraintMeshDlg::OnForceVertexColorLighting() 
{
	UpdateData();
	_CM->forceVertexColorLighting(m_ForceVertexColorLighting ? true : false /* VC  WARNING */);			
}
