/** \file scheme_bank_dlg.cpp
 * Dialog used to manage a bank of attributes makers in a particle system
 *
 * $Id: scheme_bank_dlg.cpp,v 1.4 2002/11/04 15:40:45 boucher Exp $
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
#include "scheme_bank_dlg.h"
#include "scheme_manager.h"
#include "choose_name.h"
#include <nel/misc/file.h>


/////////////////////////////////////////////////////////////////////////////
// CSchemeBankDlg dialog


CSchemeBankDlg::CSchemeBankDlg(const std::string &type, CWnd* pParent /*=NULL*/)
: CDialog(CSchemeBankDlg::IDD, pParent), _Type(type), _CurrScheme(NULL)
{
	//{{AFX_DATA_INIT(CSchemeBankDlg)
	//}}AFX_DATA_INIT
}


void CSchemeBankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSchemeBankDlg)
	DDX_Control(pDX, IDC_SCHEME_LIST, m_SchemeList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSchemeBankDlg, CDialog)
	//{{AFX_MSG_MAP(CSchemeBankDlg)
	ON_LBN_SELCHANGE(IDC_SCHEME_LIST, OnSelchangeSchemeList)
	ON_BN_CLICKED(IDC_SAVE_BANK, OnSaveBank)
	ON_BN_CLICKED(IDC_LOAD_BANK, OnLoadBank)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_RENAME, OnRename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchemeBankDlg message handlers

BOOL CSchemeBankDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	buildList();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSchemeBankDlg::OnSelchangeSchemeList() 
{
	UpdateData();
	if (m_SchemeList.GetCurSel() == LB_ERR)
	{
		_CurrScheme = NULL;
		return;
	}
	_CurrScheme = (NL3D::CPSAttribMakerBase *) m_SchemeList.GetItemData(m_SchemeList.GetCurSel());
}

void CSchemeBankDlg::buildList() 
{
	m_SchemeList.ResetContent();
	typedef std::vector<CSchemeManager::TSchemeInfo> TSchemeVect;
	static TSchemeVect schemes;
	SchemeManager.getSchemes(_Type, schemes);
	for (TSchemeVect::const_iterator it = schemes.begin(); it != schemes.end(); ++it)
	{
		int index = m_SchemeList.AddString(it->first.c_str());
		m_SchemeList.SetItemData(index, (unsigned long) it->second);
	}

	UpdateData(FALSE);
}

void CSchemeBankDlg::OnSaveBank() 
{
	static char BASED_CODE szFilter[] = "scheme bank files(*.scb)|*.scb||";
	CFileDialog fd( FALSE, NULL, "default.scb", 0, szFilter);
	
	if (fd.DoModal() == IDOK)
	{
		// Add to the path
		char drive[256];
		char dir[256];
		char path[256];

		// Add search path for the texture
		_splitpath (fd.GetPathName(), drive, dir, NULL, NULL);
		_makepath (path, drive, dir, NULL, NULL);
		NLMISC::CPath::addSearchPath (path);
		
		try
		{
			NLMISC::COFile iF;
			iF.open(std::string( (LPCTSTR) fd.GetFileName()));
			iF.serial(SchemeManager);			
		}
		catch (std::exception &e)
		{
			MessageBox(("Error saving scheme bank :" + std::string(e.what())).c_str(), "Object viewer", MB_ICONEXCLAMATION | MB_OK);
			return;
		}		
	}	
}

void CSchemeBankDlg::OnLoadBank() 
{
	static char BASED_CODE szFilter[] = "scheme bank files(*.scb)|*.scb||";
	CFileDialog fd( TRUE, NULL, "*.scb", 0, szFilter);
	
	if (fd.DoModal() == IDOK)
	{
		// Add to the path
		char drive[256];
		char dir[256];
		char path[256];

		// Add search path for the texture
		_splitpath (fd.GetPathName(), drive, dir, NULL, NULL);
		_makepath (path, drive, dir, NULL, NULL);
		NLMISC::CPath::addSearchPath (path);

		CSchemeManager sm;
		try
		{
			NLMISC::CIFile iF;
			iF.open(NLMISC::CPath::lookup(std::string((LPCTSTR) fd.GetFileName())));
			iF.serial(sm);
			SchemeManager.swap(sm);
		}
		catch (std::exception &e)
		{
			MessageBox(("Error loading scheme bank :" + std::string(e.what())).c_str(), "Object viewer", MB_ICONEXCLAMATION | MB_OK);
			return;
		}
		buildList();
	}						
}


void CSchemeBankDlg::OnRemove() 
{
	UpdateData();
	if (m_SchemeList.GetCurSel() == LB_ERR) return;
	SchemeManager.remove((NL3D::CPSAttribMakerBase *) m_SchemeList.GetItemData(m_SchemeList.GetCurSel()));
	m_SchemeList.DeleteString(m_SchemeList.GetCurSel());
	_CurrScheme = NULL;
}

void CSchemeBankDlg::OnRename() 
{
	UpdateData();
	if (m_SchemeList.GetCurSel() == LB_ERR) return;
	CString name;
	m_SchemeList.GetText(m_SchemeList.GetCurSel(), name);
	CChooseName cn((LPCTSTR) name, this);
	if (cn.DoModal() == IDOK)
	{
		NL3D::CPSAttribMakerBase *scheme = (NL3D::CPSAttribMakerBase *) m_SchemeList.GetItemData(m_SchemeList.GetCurSel());
		SchemeManager.rename(scheme, cn.getName());
		int curSel = m_SchemeList.GetCurSel();
		m_SchemeList.DeleteString(curSel);
		int insertedPos = m_SchemeList.InsertString(curSel, cn.getName().c_str());
		m_SchemeList.SetCurSel(insertedPos);
		m_SchemeList.Invalidate();
	}	
	
	
}
