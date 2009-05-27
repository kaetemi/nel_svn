/** \file main_dlg.cpp
 * TODO: File description
 *
 * $Id: main_dlg.cpp,v 1.11 2007/03/19 09:55:26 boucher Exp $
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
#include "main_dlg.h"
#include "nel/3d/channel_mixer.h"

using namespace NLMISC;
using namespace NL3D;

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog


CMainDlg::CMainDlg(CObjectViewer* main, CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Main=main;
}


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Get size
	RECT rect;
		
	// Init Slots
	for (uint s=0; s<CChannelMixer::NumAnimationSlot; s++)
	{
		// Init the slot s
		BOOL initialized=Slots[s].Create (IDD_SLOT, this);

		// Position
		Slots[s].init (s, Main);
		Slots[s].GetClientRect (&rect);
		Slots[s].SetWindowPos( NULL, 0, s*(rect.bottom-rect.top), 0, 0, SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_NOZORDER|SWP_SHOWWINDOW);
	}

	// Resize the main window
	RECT client;
	RECT window;
	GetClientRect (&client);
	GetWindowRect (&window);
	SetWindowPos( NULL, 0, 0, rect.right-rect.left+window.right-window.left-client.right+client.left, 
		NL3D::CChannelMixer::NumAnimationSlot*(rect.bottom-rect.top)+window.bottom-window.top-client.bottom+client.top, 
		SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOZORDER);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainDlg::setAnimTime (float animStart, float animEnd)
{
	// Init Slots
	for (uint s=0; s<CChannelMixer::NumAnimationSlot; s++)
		Slots[s].setAnimTime (animStart, animEnd);
}

void CMainDlg::OnDestroy() 
{
	setRegisterWindowState (this, REGKEY_OBJ_VIEW_SLOT_DLG);

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style&=~WS_VISIBLE;
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CMainDlg::refresh (BOOL update)
{
	for (uint s=0; s<CChannelMixer::NumAnimationSlot; s++)
		Slots[s].refresh (update);
}
