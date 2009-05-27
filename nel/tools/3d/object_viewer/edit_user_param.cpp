/** \file edit_user_param.cpp
 * A dialog for editing one of the global user params in a particle system
 *
 * $Id: edit_user_param.cpp,v 1.3 2002/11/04 15:40:44 boucher Exp $
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
#include "edit_user_param.h"


/////////////////////////////////////////////////////////////////////////////
// CEditUserParam dialog


CEditUserParam::CEditUserParam(uint32 userParamIndex, CWnd* pParent /*=NULL*/)
	: _UserParamIndex(userParamIndex), CDialog(CEditUserParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditUserParam)
	//}}AFX_DATA_INIT
}


void CEditUserParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditUserParam)
	DDX_Control(pDX, IDC_USER_PARAM_INDEX, m_UserParamIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditUserParam, CDialog)
	//{{AFX_MSG_MAP(CEditUserParam)
	ON_CBN_SELCHANGE(IDC_USER_PARAM_INDEX, OnSelchangeUserParamIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditUserParam message handlers

BOOL CEditUserParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_UserParamIndex.SetCurSel(_UserParamIndex) ;	
	UpdateData(FALSE) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditUserParam::OnSelchangeUserParamIndex() 
{
	UpdateData() ;
	_UserParamIndex = m_UserParamIndex.GetCurSel() ;
}
