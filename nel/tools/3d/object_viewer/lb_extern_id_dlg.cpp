/** \file lb_extern_id_dlg.cpp
 * A dialog for assigning ID to objects in a particle system
 *
 * $Id: lb_extern_id_dlg.cpp,v 1.5 2002/11/04 15:40:44 boucher Exp $
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
#include "lb_extern_id_dlg.h"


/////////////////////////////////////////////////////////////////////////////
// CLBExternIDDlg dialog


CLBExternIDDlg::CLBExternIDDlg(uint32 id, CWnd* pParent /* = NULL*/)
	: CDialog(CLBExternIDDlg::IDD, pParent), _ID(id)
{
	//{{AFX_DATA_INIT(CLBExternIDDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLBExternIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLBExternIDDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLBExternIDDlg, CDialog)
	//{{AFX_MSG_MAP(CLBExternIDDlg)
	ON_BN_CLICKED(IDC_ENABLE_EXTERN_ID, OnEnableExternId)
	ON_EN_CHANGE(IDC_ID_VALUE, OnChangeIdValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLBExternIDDlg message handlers

BOOL CLBExternIDDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	GetDlgItem(IDC_ID_VALUE)->EnableWindow(_ID != 0);
	((CButton *) GetDlgItem(IDC_ENABLE_EXTERN_ID))->SetCheck(_ID != 0 ? 1 : 0);

	if (_ID)
	{
		char val[5];
		for (uint k = 0; k < 4; ++k)
		{
			#ifdef NL_LITTLE_ENDIAN
				val[k] = (unsigned char) (_ID >> ((3 - k) << 3));
			#else
				val[k] = (unsigned char) (_ID >> (k << 3));				
			#endif
		}
		val[4] = '\0';		
		GetDlgItem(IDC_ID_VALUE)->SetWindowText(val);

	}
	else
	{
		_ID = 0;
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


static uint32 StringToID(const char *buf)
{
	uint32 id;
	#ifdef NL_LITTLE_ENDIAN
		id = ((uint32) buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | (buf[3]);		
	#else
		id = *(uint32 *) buf;		
	#endif
	return id;
}

void CLBExternIDDlg::OnEnableExternId() 
{
	if (_ID == 0)
	{
		GetDlgItem(IDC_ID_VALUE)->EnableWindow(TRUE);
		_ID = StringToID("NONE");		
		GetDlgItem(IDC_ID_VALUE)->SetWindowText("NONE");		
	}
	else
	{
		GetDlgItem(IDC_ID_VALUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_ID_VALUE)->SetWindowText("");		
		_ID = 0;
	}		
}

void CLBExternIDDlg::OnChangeIdValue() 
{	
	if (!((CButton *) GetDlgItem(IDC_ENABLE_EXTERN_ID))->GetCheck()) return;
	char buf[6];
	::memset(buf, 0, 6);
	GetDlgItem(IDC_ID_VALUE)->GetWindowText(buf, 6);
	_ID = StringToID(buf);	
	if (_ID)
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDC_ENABLE_EXTERN_ID)->EnableWindow(TRUE);		
		if (::strlen(buf) > 4)
		{
			buf[4] = '\0';
			GetDlgItem(IDC_ID_VALUE)->SetWindowText(buf);
		}
	}
	else
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDC_ENABLE_EXTERN_ID)->EnableWindow(FALSE);	
	}

}
