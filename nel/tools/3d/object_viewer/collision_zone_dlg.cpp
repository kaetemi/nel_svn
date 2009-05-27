/** \file collision_zone_dlg.cpp
 * a dialog to edit collision zone properties in a particle system
 *
 * $Id: collision_zone_dlg.cpp,v 1.5 2004/06/18 13:16:43 vizerie Exp $
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
#include "collision_zone_dlg.h"
#include "editable_range.h"
#include "particle_dlg.h"
#include "start_stop_particle_system.h"

/////////////////////////////////////////////////////////////////////////////
// CCollisionZoneDlg dialog

// standard constructor
CCollisionZoneDlg::CCollisionZoneDlg(CParticleWorkspace::CNode *ownerNode, NL3D::CPSZone *zone, CParticleDlg *particleDlg)
	: _Zone(zone),
	  _Node(ownerNode),
	  _ParticleDlg(particleDlg)
{
	nlassert(particleDlg);
	//{{AFX_DATA_INIT(CCollisionZoneDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCollisionZoneDlg::init(sint x, sint y, CWnd *pParent)
{
	RECT r;
	Create(IDD_ZONE, pParent);
	GetClientRect(&r);
	r.top += y; r.bottom += y;
	r.right += x; r.left += x;
	MoveWindow(&r);

	_BounceFactorDlg = new CEditableRangeFloat(std::string("BOUNCE_FACTOR"), _Node, 0.f, 1.f);
	pushWnd(_BounceFactorDlg);
	_BounceFactorWrapper.Z = _Zone;
	_BounceFactorDlg->setWrapper(&_BounceFactorWrapper);
	_BounceFactorDlg->init(60, 35, this);
	
	m_CollisionBehaviour.SetCurSel((uint) _Zone->getCollisionBehaviour() );

	if (_Zone->getCollisionBehaviour() != NL3D::CPSZone::bounce)
	{
		_BounceFactorDlg->EnableWindow(FALSE);	
	}

	UpdateData();

	ShowWindow(SW_SHOW);
}


void CCollisionZoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCollisionZoneDlg)
	DDX_Control(pDX, IDC_COLLISION_BEHAVIOUR, m_CollisionBehaviour);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCollisionZoneDlg, CDialog)
	//{{AFX_MSG_MAP(CCollisionZoneDlg)
	ON_CBN_SELCHANGE(IDC_COLLISION_BEHAVIOUR, OnSelchangeCollisionBehaviour)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCollisionZoneDlg message handlers

void CCollisionZoneDlg::OnSelchangeCollisionBehaviour() 
{
	UpdateData();
	_Zone->setCollisionBehaviour( (NL3D::CPSZone::TCollisionBehaviour) m_CollisionBehaviour.GetCurSel());
	_BounceFactorDlg->EnableWindow(_Zone->getCollisionBehaviour() == NL3D::CPSZone::bounce ? TRUE : FALSE);	
	_ParticleDlg->StartStopDlg->resetAutoCount(_Node);
}
