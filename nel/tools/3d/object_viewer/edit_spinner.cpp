/** \file edit_spinner.cpp
 * a dialog to edit a spinner
 *
 * $Id: edit_spinner.cpp,v 1.5 2004/06/17 08:13:13 vizerie Exp $
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
#include "edit_spinner.h"
#include "direction_attr.h"
#include "editable_range.h"
#include "popup_notify.h"



/////////////////////////////////////////////////////////////////////////////
// CEditSpinner dialog


CEditSpinner::CEditSpinner(NL3D::CPSBasisSpinner *sf, CParticleWorkspace::CNode *ownerNode, CWnd *pParent, IPopupNotify *pn)
	: CDialog(CEditSpinner::IDD, pParent),
	  _Node(ownerNode),
	  _DirDlg(NULL), 
	  _NbSamplesDlg(NULL),
	  _Spinner(sf),
	  _PN(pn)
{
	//{{AFX_DATA_INIT(CEditSpinner)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CEditSpinner::~CEditSpinner()
{
	if (_DirDlg) { _DirDlg->DestroyWindow(); delete _DirDlg; }
	if (_NbSamplesDlg) { _NbSamplesDlg->DestroyWindow(); delete _NbSamplesDlg; }
}

void CEditSpinner::init(CWnd *pParent)
{
	CDialog::Create(IDD_EDITSPINNER, pParent);	
	ShowWindow(SW_SHOW);
}

void CEditSpinner::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditSpinner)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditSpinner, CDialog)
	//{{AFX_MSG_MAP(CEditSpinner)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditSpinner message handlers

BOOL CEditSpinner::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_NbSampleWrapper.S = _Spinner;	
	_AxisWrapper.S	   = _Spinner;

	_DirDlg = new CDirectionAttr(std::string("SPINNER DIR"));
	_DirDlg->setWrapper(&_AxisWrapper);
	_AxisWrapper.OwnerNode = _Node;
	_DirDlg->init(10, 10, this);

	_NbSamplesDlg = new CEditableRangeUInt("SPINNER NB SAMPLES", _Node, 1, 512);
	_NbSamplesDlg->enableLowerBound(0, true); // 0 not allowed
	_NbSamplesDlg->setWrapper(&_NbSampleWrapper);
	_NbSamplesDlg->init(60, 50, this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditSpinner::OnClose() 
{		
	CDialog::OnClose();
	if (_PN) _PN->childPopupClosed(this);
}
