/** \file value_from_emitter_dlg.cpp
 * Dialog used to tune particle attributes that are computed from their emitter
 *
 * $Id: value_from_emitter_dlg.cpp,v 1.4 2002/11/04 15:40:45 boucher Exp $
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

#include "std_afx.h"
#include "object_viewer.h"
#include "value_from_emitter_dlg.h"
#include "popup_notify.h"


/////////////////////////////////////////////////////////////////////////////
// CValueFromEmitterDlg dialog


CValueFromEmitterDlg::CValueFromEmitterDlg(IPopupNotify *pn, CWnd* pParent /*=NULL*/)
	: CDialog(CValueFromEmitterDlg::IDD, pParent), _PN(pn)
{
	//{{AFX_DATA_INIT(CValueFromEmitterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CValueFromEmitterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CValueFromEmitterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CValueFromEmitterDlg::create(CWnd *pParent)
{
	CDialog::Create(IDD_MEMORY_VALUE_DLG, pParent);	
	ShowWindow(SW_SHOW);
}


BEGIN_MESSAGE_MAP(CValueFromEmitterDlg, CDialog)
	//{{AFX_MSG_MAP(CValueFromEmitterDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValueFromEmitterDlg message handlers

BOOL CValueFromEmitterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CValueFromEmitterDlg::OnClose() 
{		
	CDialog::OnClose();
	if (_PN) _PN->childPopupClosed(this);
}
