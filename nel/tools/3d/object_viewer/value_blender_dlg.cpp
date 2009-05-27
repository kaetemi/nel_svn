/** \file value_blender_dlg.cpp
 * a dialog to choose 2 values that are linearly blended in a particle system
 *
 * $Id: value_blender_dlg.cpp,v 1.7 2004/06/17 08:00:11 vizerie Exp $
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
 * MA 02
*/



// ValueBlenderDlg.cpp : implementation file
//

#include "std_afx.h"
#include "object_viewer.h"
#include "value_blender_dlg.h"
#include "edit_attrib_dlg.h"
#include "popup_notify.h"


/////////////////////////////////////////////////////////////////////////////
// CValueBlenderDlg dialog


CValueBlenderDlg::CValueBlenderDlg(IValueBlenderDlgClient *creationInterface,
								   bool destroyInterface,
								   CWnd* pParent,
								   IPopupNotify *pn,
								   CParticleWorkspace::CNode *ownerNode
								  )
	: _CreateInterface(creationInterface),
	  CDialog(CValueBlenderDlg::IDD, pParent),
	  _PN(pn),
	  _DestroyInterface(destroyInterface),
	  _Node(ownerNode)	  
{
	//{{AFX_DATA_INIT(CValueBlenderDlg)
	//}}AFX_DATA_INIT
}

CValueBlenderDlg::~CValueBlenderDlg()
{
	if (_DestroyInterface) delete _CreateInterface;
	delete _Dlg1 ;
	delete _Dlg2 ;	
}


void CValueBlenderDlg::init(CWnd *pParent)
{	
	CDialog::Create(IDD_VALUE_BLENDER, pParent);	
	ShowWindow(SW_SHOW);
}


void CValueBlenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CValueBlenderDlg)
	DDX_Control(pDX, IDC_VALUE2, m_Value2);
	DDX_Control(pDX, IDC_VALUE1, m_Value1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CValueBlenderDlg, CDialog)
	//{{AFX_MSG_MAP(CValueBlenderDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValueBlenderDlg message handlers

BOOL CValueBlenderDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData() ;
	nlassert(_CreateInterface) ;	
	_Dlg1 = _CreateInterface->createDialog(0, _Node) ;
	_Dlg2 = _CreateInterface->createDialog(1, _Node) ;
	RECT r, or ;	
	GetWindowRect(&or) ;
	m_Value1.GetWindowRect(&r) ;
	_Dlg1->init(r.left - or.left, r.top - or.top, this) ;
	m_Value2.GetWindowRect(&r) ;
	_Dlg2->init(r.left - or.left, r.top - or.top, this) ;	
	
	UpdateData(FALSE) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}





void CValueBlenderDlg::OnClose() 
{	
	if (_PN) _PN->childPopupClosed(this);
	//CDialog::OnClose();
}
