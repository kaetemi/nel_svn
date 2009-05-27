/** \file bin_op_dlg.cpp
 * A dialog that helps editing binary opeartors ofr particle systems attributes.
 *
 * $Id: bin_op_dlg.cpp,v 1.4 2002/11/04 15:40:44 boucher Exp $
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

#include "std_afx.h"
#include "object_viewer.h"
#include "bin_op_dlg.h"
#include "popup_notify.h"

/////////////////////////////////////////////////////////////////////////////
// CBinOpDlg dialog


CBinOpDlg::CBinOpDlg(IPopupNotify *pn, CWnd* pParent /*=NULL*/)
	: _PN(pn), CDialog(CBinOpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBinOpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBinOpDlg::create(CWnd *pParent)
{
	CDialog::Create(IDD_BIN_OP, pParent);	
	ShowWindow(SW_SHOW);
}


void CBinOpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBinOpDlg)
	DDX_Control(pDX, IDC_BIN_OP, m_BinOp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBinOpDlg, CDialog)
	//{{AFX_MSG_MAP(CBinOpDlg)
	ON_CBN_SELCHANGE(IDC_BIN_OP, OnSelchangeBinOp)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBinOpDlg message handlers

BOOL CBinOpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();					
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBinOpDlg::OnSelchangeBinOp() 
{
	UpdateData() ;
	newOp(m_BinOp.GetItemData(m_BinOp.GetCurSel())) ;	
}

void CBinOpDlg::OnClose() 
{
	CDialog::OnClose();
	if (_PN) _PN->childPopupClosed(this);	
}
