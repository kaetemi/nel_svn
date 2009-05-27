/** \file skippable_message_box.cpp
 *
 * $Id: skippable_message_box.cpp,v 1.1 2004/06/17 08:20:48 vizerie Exp $
 */

/* Copyright, 2000-2004 Nevrax Ltd.
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

// skippable_message_box.cpp : implementation file
//

#include "std_afx.h"
#include "object_viewer.h"
#include "skippable_message_box.h"


/////////////////////////////////////////////////////////////////////////////
// CSkippableMessageBox dialog


CSkippableMessageBox::CSkippableMessageBox(const CString &caption, const CString &content, CWnd* pParent /*=NULL*/)
	: CDialog(CSkippableMessageBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkippableMessageBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	_BypassFlag = false;
	_Caption = caption;
	_Content = content;
}


void CSkippableMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkippableMessageBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkippableMessageBox, CDialog)
	//{{AFX_MSG_MAP(CSkippableMessageBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkippableMessageBox message handlers

BOOL CSkippableMessageBox::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText((LPCTSTR) _Caption);
	GetDlgItem(IDC_MB_CONTENT)->SetWindowText((LPCTSTR) _Content);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//*************************************************************************************
void CSkippableMessageBox::OnOK()
{
	_BypassFlag = ((CButton *) GetDlgItem(IDC_DONT_SHOW_AGAIN))->GetCheck() != 0;
	CDialog::OnOK();
}

