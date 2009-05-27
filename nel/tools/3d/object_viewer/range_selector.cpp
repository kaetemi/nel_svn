/** \file range_selector.cpp
 * Helps to select a range for numeric values in a CEditableRange dialog
 *
 * $Id: range_selector.cpp,v 1.3 2002/11/04 15:40:45 boucher Exp $
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


// range_selector.cpp : implementation file
//

#include "std_afx.h"
#include "object_viewer.h"
#include "range_selector.h"
#include "editable_range.h"


/////////////////////////////////////////////////////////////////////////////
// CRangeSelector dialog


CRangeSelector::CRangeSelector(const CString &lowerBound, const CString &upperBound, CEditableRange *er, CWnd* pParent)
	: CDialog(CRangeSelector::IDD, pParent), _EditableRange(er)
{
	//{{AFX_DATA_INIT(CRangeSelector)
	m_LowerBound = _T(lowerBound);
	m_UpperBound = _T(upperBound);
	//}}AFX_DATA_INIT
}


void CRangeSelector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRangeSelector)
	DDX_Control(pDX, IDC_UPPER_BOUND, m_UpperBoundCtrl);
	DDX_Control(pDX, IDC_LOWER_BOUND, m_LowerBoundCtrl);
	DDX_Text(pDX, IDC_LOWER_BOUND, m_LowerBound);
	DDX_Text(pDX, IDC_UPPER_BOUND, m_UpperBound);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRangeSelector, CDialog)
	//{{AFX_MSG_MAP(CRangeSelector)
	ON_EN_SETFOCUS(IDC_LOWER_BOUND, OnSetfocusLowerBound)
	ON_EN_SETFOCUS(IDC_UPPER_BOUND, OnSetfocusUpperBound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRangeSelector message handlers

void CRangeSelector::OnOK() 
{
	UpdateData() ;
	if (_EditableRange->editableRangeValueValidator(m_LowerBound, m_UpperBound))
	{
		CDialog::OnOK();
	}
}

void CRangeSelector::OnSetfocusLowerBound() 
{
	
	m_LowerBoundCtrl.PostMessage(EM_SETSEL, 0, -1) ;	
	m_LowerBoundCtrl.Invalidate() ; 	
}

void CRangeSelector::OnSetfocusUpperBound() 
{
	m_UpperBoundCtrl.PostMessage(EM_SETSEL, 0, -1) ;	
	m_UpperBoundCtrl.Invalidate() ;
}

BOOL CRangeSelector::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_LowerBoundCtrl.PostMessage(EM_SETSEL, 0, -1) ;	
	m_LowerBoundCtrl.Invalidate() ; 	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
