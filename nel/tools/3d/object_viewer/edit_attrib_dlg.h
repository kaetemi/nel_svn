 /** \file edit_attrib_dlg.h
 * base class for attribute edition dialog in a particle system.
 * It gives a basic interface, to position and enable / disable the window
 *
 * $Id: edit_attrib_dlg.h,v 1.3 2001/06/25 13:22:15 vizerie Exp $
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


#if !defined(AFX_EDIT_ATTRIB_DLG_H__0B2EFF2B_FA0E_4AC8_88B8_416605043BF9__INCLUDED_)
#define AFX_EDIT_ATTRIB_DLG_H__0B2EFF2B_FA0E_4AC8_88B8_416605043BF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * a base class for attribute edition dialog in a particle system
 */

class CEditAttribDlg : public CDialog
{
public:
	virtual BOOL EnableWindow( BOOL bEnable = TRUE ) { return CDialog::EnableWindow(bEnable) ; } ;
	virtual void init(uint32 x, uint32 y, CWnd *pParent) = 0 ;
	virtual ~CEditAttribDlg() {}
} ;


#endif 
