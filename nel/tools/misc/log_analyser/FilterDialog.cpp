/** \file FilterDialog.cpp
 * implementation file
 *
 * $Id: FilterDialog.cpp,v 1.1 2002/10/18 12:04:56 cado Exp $
 */

/* Copyright, 2002 Nevrax Ltd.
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
// FilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "log_analyser.h"
#include "FilterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;


/////////////////////////////////////////////////////////////////////////////
// CFilterDialog dialog


CFilterDialog::CFilterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilterDialog)
	m_NegFilter = _T("");
	m_PosFilter = _T("");
	m_Sep = _T("");
	//}}AFX_DATA_INIT
}


void CFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterDialog)
	DDX_Text(pDX, IDC_NegFilter, m_NegFilter);
	DDX_Text(pDX, IDC_PosFilter, m_PosFilter);
	DDX_Text(pDX, IDC_Sep, m_Sep);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilterDialog, CDialog)
	//{{AFX_MSG_MAP(CFilterDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterDialog message handlers

BOOL CFilterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if ( Trace )
	{
		GetDlgItem( IDC_PosFilterCap )->SetWindowText( "Service code" );
		GetDlgItem( IDC_NegFilterCap )->ShowWindow( SW_HIDE );
		GetDlgItem( IDC_SepCap )->ShowWindow( SW_HIDE );
		GetDlgItem( IDC_NegFilter )->ShowWindow( SW_HIDE );
		GetDlgItem( IDC_Sep )->ShowWindow( SW_HIDE );
	}
	else
	{
		GetDlgItem( IDC_PosFilterCap )->SetWindowText( "Positive filters (all lines must contain one of these substrings)" );
		GetDlgItem( IDC_NegFilterCap )->ShowWindow( SW_SHOW );
		GetDlgItem( IDC_SepCap )->ShowWindow( SW_SHOW );
		GetDlgItem( IDC_NegFilter )->ShowWindow( SW_SHOW );
		GetDlgItem( IDC_Sep )->SetWindowText( ";" );
		GetDlgItem( IDC_Sep )->ShowWindow( SW_SHOW );
	}

	return TRUE;
}


/*
 *
 */
std::vector<CString>	buildVectorFromString( const CString& str, const CString& sep )
{
	std::vector<CString> vec;
	CString str2 = str;
	char *token;
	token = strtok( str2.GetBuffer( str2.GetLength() ), sep );
	while ( token != NULL )
	{
		vec.push_back( CString(token) );
		token = strtok( NULL, sep );
	}
	str2.ReleaseBuffer();
	return vec;
}


/*
 *
 */
std::vector<CString>		CFilterDialog::getPosFilter() const
{
	return buildVectorFromString( m_PosFilter, m_Sep );
}


/*
 *
 */
std::vector<CString>		CFilterDialog::getNegFilter() const
{
	return buildVectorFromString( m_NegFilter, m_Sep );
}
