/** \file LogSessions.h
 * header file
 *
 * $Id: LogSessions.h,v 1.4 2003/08/06 14:05:57 cado Exp $
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

#include <vector>

#if !defined(AFX_LOGSESSIONS_H__24A056CC_9FE8_4A90_B3FF_DAF2BF4929F0__INCLUDED_)
#define AFX_LOGSESSIONS_H__24A056CC_9FE8_4A90_B3FF_DAF2BF4929F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogSessions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogSessions dialog

class CLogSessions : public CDialog
{
// Construction
public:
	CLogSessions(CWnd* pParent = NULL);   // standard constructor

	///
	void		addLogSession( const CString& line );

	///
	void		clear() { Sessions.clear(); }

	///
	CString		getStartDate() const;

	std::vector<CString> Sessions;
	std::vector<CString> Filenames;
	
// Dialog Data
	//{{AFX_DATA(CLogSessions)
	enum { IDD = IDD_LOGSESSIONS };
	CListBox	m_ListBox;
	CString	m_StartDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogSessions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogSessions)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGSESSIONS_H__24A056CC_9FE8_4A90_B3FF_DAF2BF4929F0__INCLUDED_)
