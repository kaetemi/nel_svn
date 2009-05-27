/** \file choose_name.cpp
 * A dialog that allow to choose a name
 *
 * $Id: choose_name.cpp,v 1.2 2002/11/04 15:40:44 boucher Exp $
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

#include "std_afx.h"
#include "object_viewer.h"
#include "choose_name.h"

/////////////////////////////////////////////////////////////////////////////
// CChooseName dialog


CChooseName::CChooseName(const char *initialName, CWnd* pParent /*=NULL*/)
	: CDialog(CChooseName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseName)
	m_Name = _T(initialName);
	//}}AFX_DATA_INIT
}


std::string CChooseName::getName()
{
	return std::string(m_Name);
}

void CChooseName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseName)
	DDX_Text(pDX, IDC_NAME_CHOSEN, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseName, CDialog)
	//{{AFX_MSG_MAP(CChooseName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseName message handlers
