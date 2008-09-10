/** \file auto_lod_dlg.h
 * A dialog to tune auto-lod options of particle systems.
 *
 * $Id: auto_lod_dlg.h,v 1.4 2007/03/19 09:55:26 boucher Exp $
 */

/* Copyright, 2000 - 2002 Nevrax Ltd.
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

#if !defined(AFX_AUTO_LOD_DLG_H__BCD6DB9A_FA8A_47AD_9E95_317A8B94047A__INCLUDED_)
#define AFX_AUTO_LOD_DLG_H__BCD6DB9A_FA8A_47AD_9E95_317A8B94047A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "ps_wrapper.h"
#include "dialog_stack.h"
#include "nel/3d/particle_system.h"
#include "particle_workspace.h"

namespace NL3D
{
	class CParticleSystem;
}
struct IPopupNotify;

class CAutoLODDlg : public CDialog, public CDialogStack
{
// Construction
public:
	CAutoLODDlg(CParticleWorkspace::CNode *ownerNode, NL3D::CParticleSystem *ps, IPopupNotify *pn, CWnd* pParent = NULL);   // standard constructor

	void init(CWnd *pParent);
// Dialog Data
	//{{AFX_DATA(CAutoLODDlg)
	enum { IDD = IDD_AUTO_LOD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoLODDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CParticleWorkspace::CNode *_Node;
	NL3D::CParticleSystem	  *_PS;
	IPopupNotify		      *_PN;	
	


	struct CDistRatioWrapper : IPSWrapperFloat
	{
		NL3D::CParticleSystem *PS;
		virtual float get() const  { return PS->getAutoLODStartDistPercent(); }
		virtual void  set(const float &v) { PS->setupAutoLOD(v, PS->getAutoLODDegradationExponent()); }
	} _DistRatioWrapper;

	struct CMaxDistLODBiasWrapper : IPSWrapperFloat
	{
		NL3D::CParticleSystem *PS;
		virtual float get() const  { return PS->getMaxDistLODBias(); }
		virtual void  set(const float &v) { PS->setMaxDistLODBias(v); }
	} _MaxDistLODBiasWrapper;

	// Generated message map functions
	//{{AFX_MSG(CAutoLODDlg)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDegradationExponent();
	afx_msg void OnSkipParticles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTO_LOD_DLG_H__BCD6DB9A_FA8A_47AD_9E95_317A8B94047A__INCLUDED_)
