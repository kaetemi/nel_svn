/** \file collision_zone_dlg.h
 * a dialog to edit collision zone properties in a particle system
 *
 * $Id: collision_zone_dlg.h,v 1.7 2007/03/19 09:55:26 boucher Exp $
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

#if !defined(AFX_COLLISION_ZONE_DLG_H__45AFAC35_D67B_40AB_85B6_7A472B7C4B30__INCLUDED_)
#define AFX_COLLISION_ZONE_DLG_H__45AFAC35_D67B_40AB_85B6_7A472B7C4B30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif
namespace NL3D
{
	class CPSZone ;
}

#include "ps_wrapper.h"
#include "dialog_stack.h"
#include "editable_range.h"
#include "particle_workspace.h"
//
#include "nel/3d/ps_zone.h"


class CParticleDlg;

/////////////////////////////////////////////////////////////////////////////
// CCollisionZoneDlg dialog

class CCollisionZoneDlg : public CDialog, public CDialogStack
{
// Construction
public:
	CCollisionZoneDlg(CParticleWorkspace::CNode *ownerNode, NL3D::CPSZone *zone, CParticleDlg *particleDlg) ;   // standard constructor

	void init(sint x, sint y, CWnd *pParent) ;
// Dialog Data
	//{{AFX_DATA(CCollisionZoneDlg)
	enum { IDD = IDD_ZONE };
	CComboBox	m_CollisionBehaviour;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollisionZoneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CParticleWorkspace::CNode *_Node;
	CParticleDlg              *_ParticleDlg;
	// the collision zone being edited
	NL3D::CPSZone             *_Zone ;
	// edition of the bounce factor
	CEditableRangeFloat       *_BounceFactorDlg ;
	// Generated message map functions
	//{{AFX_MSG(CCollisionZoneDlg)
	afx_msg void OnSelchangeCollisionBehaviour();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// wrapper to set the bounce factor of a collision zone
	struct CBounceFactorWrapper : public IPSWrapperFloat
	{
		// the zone being wrapped
		NL3D::CPSZone *Z ;
		float get(void) const { return Z->getBounceFactor() ; }
		void set(const float &v) { Z->setBounceFactor(v) ; }
	} _BounceFactorWrapper ;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLISION_ZONE_DLG_H__45AFAC35_D67B_40AB_85B6_7A472B7C4B30__INCLUDED_)
