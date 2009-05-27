/** \file create_file_dlg.h
 *
 * $Id: create_file_dlg.h,v 1.1 2004/06/17 08:15:05 vizerie Exp $
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

#if !defined(AFX_CREATE_FILE_DLG_H__AB5F0D7B_8B35_48B9_8ABB_DE9367A8F9FA__INCLUDED_)
#define AFX_CREATE_FILE_DLG_H__AB5F0D7B_8B35_48B9_8ABB_DE9367A8F9FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// create_file_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateFileDlg dialog

class CCreateFileDlg : public CDialog
{
// Construction
public:
	CCreateFileDlg(const CString &title, const std::string &defaultBasePath, const std::string &extension, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateFileDlg)
	enum { IDD = IDD_CREATE_FILE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// get chosen filename without path
	std::string getFileName() const { return _Filename; }	
	// get chosen path
	std::string getPath() const { return _Path; }
	// get full path (path + filename)
	std::string getFullPath() const { return _FullPath; }
	// Touch the selected file after DoModal() has been called.
	// The user will be asked confirmation if file already exists.
	// Appropriate error msgs will be issued if creation fails.
	bool touchFile();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	

// Implementation
protected:
	std::string _Extension;
	std::string _Filename;
	std::string _Path;
	std::string _FullPath;
	std::string _DefaultBasePath;
	// Generated message map functions
	//{{AFX_MSG(CCreateFileDlg)
	afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// from CDialog
	void OnOK();
	void OnCancel();
private:
	CString _Title;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATE_FILE_DLG_H__AB5F0D7B_8B35_48B9_8ABB_DE9367A8F9FA__INCLUDED_)
