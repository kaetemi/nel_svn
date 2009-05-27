/** \file edit_spinner.h
 * a dialog to edit a spinner
 *
 * $Id: edit_spinner.h,v 1.5 2007/03/19 09:55:26 boucher Exp $
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


#if !defined(AFX_EDIT_SPINNER_H__CFDBE30D_F8C9_432E_9F17_0AFACE143BB0__INCLUDED_)
#define AFX_EDIT_SPINNER_H__CFDBE30D_F8C9_432E_9F17_0AFACE143BB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

struct IPopupNotify;

#include "ps_wrapper.h"
#include "nel/3d/ps_plane_basis_maker.h"
#include "editable_range.h"
#include "particle_workspace.h"

class CDirectionAttr;

class CEditSpinner : public CDialog
{
// Construction
public:
	CEditSpinner(NL3D::CPSBasisSpinner *sf, CParticleWorkspace::CNode *ownerNode, CWnd *pParent, IPopupNotify *pn);

	// dtor
	~CEditSpinner();

	/// init this dialog
	void init(CWnd *pParent);

// Dialog Data
	//{{AFX_DATA(CEditSpinner)
	enum { IDD = IDD_EDITSPINNER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditSpinner)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	NL3D::CPSBasisSpinner     *_Spinner; // the spinner being edited
	CDirectionAttr			  *_DirDlg;
	CEditableRangeUInt		  *_NbSamplesDlg;
	IPopupNotify			  *_PN;
	CParticleWorkspace::CNode *_Node;

	// Generated message map functions
	//{{AFX_MSG(CEditSpinner)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG

	// wrapper to set the number of samples in the spinner
	struct CNbSampleWrapper : public IPSWrapperUInt
	{
		NL3D::CPSBasisSpinner     *S;
		uint32 get(void) const { return S->_F.getNumSamples(); }
		void set(const uint32 &val) { S->_F.setNumSamples(val); }
	} _NbSampleWrapper;


	// wrapper to set the axis of the spinner
	struct CAxisWrapper : public IPSWrapper<NLMISC::CVector>
	{
		NL3D::CPSBasisSpinner     *S;
		NLMISC::CVector get(void) const { return S->_F.getAxis(); }
		void set(const NLMISC::CVector &axis) { S->_F.setAxis(axis); }
	} _AxisWrapper;
	

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_SPINNER_H__CFDBE30D_F8C9_432E_9F17_0AFACE143BB0__INCLUDED_)
