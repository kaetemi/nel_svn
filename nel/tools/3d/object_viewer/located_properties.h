/** \file located_properties.h
 * a dialog that allow to tune a located properties. In a aprticle system, a located is an object that has :
 *  - a position
 *  - a mass
 *  - a speed vector
 *  - a lifetime
 *
 * $Id: located_properties.h,v 1.13 2004/06/17 08:12:16 vizerie Exp $
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


#if !defined(AFX_LOCATED_PROPERTIES_H__772D6C3B_6CFD_47B5_A132_A8D2352EACF9__INCLUDED_)
#define AFX_LOCATED_PROPERTIES_H__772D6C3B_6CFD_47B5_A132_A8D2352EACF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// located_properties.h : header file
//
#include "editable_range.h"
#include "particle_tree_ctrl.h"
#include "dialog_stack.h"
#include "start_stop_particle_system.h"
#include "particle_workspace.h"

namespace  NL3D
{
	class CPSLocated;
}; 


class CAttribDlgFloat;

/////////////////////////////////////////////////////////////////////////////
// CLocatedProperties dialog

class CLocatedProperties : public CDialog, public CObjectViewer::IMainLoopCallBack
{
// Construction
public:
	CLocatedProperties(CParticleWorkspace::CNode *node, NL3D::CPSLocated *loc, CParticleDlg *pdlg);   // standard constructor

	~CLocatedProperties();

	void init(uint32 x, uint32 y);

	CEditableRangeUInt *getParticleCountDlg() const { return _MaxNbParticles; }
	
// Dialog Data
	//{{AFX_DATA(CLocatedProperties)
	enum { IDD = IDD_LOCATED_PROPERTIES };
	CButton	m_EditTriggerOnDeath;
	CButton	m_TriggerOnDeathCtrl;
	CButton	m_ParametricMotionCtrl;
	CStatic	m_MaxNbParticles;
	BOOL	m_LimitedLifeTime;
	BOOL	m_SystemBasis;
	BOOL	m_DisgradeWithLOD;
	BOOL	m_ParametricIntegration;
	BOOL	m_ParametricMotion;
	BOOL	m_TriggerOnDeath;
	int		m_MatrixMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocatedProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CParticleWorkspace::CNode *_Node;
	//
	CEditableRangeUInt *_MaxNbParticles;
	CEditableRangeUInt *_SkipFramesDlg;
	//
	CAttribDlgFloat *_MassDialog;
	CAttribDlgFloat *_LifeDialog;
	//
	CParticleDlg *_ParticleDlg;
	/// some wrappers used to read / write value from / to the particle system

		
		/////////////////////////////////////////////////
		// wrapper to tune the max number of particles //
		/////////////////////////////////////////////////


		struct CMaxNbParticlesWrapper : public IPSWrapperUInt
		{
			CParticleWorkspace::CNode *Node;
			NL3D::CPSLocated *Located;
			CParticleTreeCtrl *TreeCtrl;
			uint32 get(void) const { return Located->getMaxSize(); }
			void set(const uint32 &v) 
			{ 
				// if the max new size is lower than the current number of instance, we must suppress item
				// in the the CParticleTreeCtrl

				if (v < Located->getSize())
				{
					nlassert(Node);
					TreeCtrl->suppressLocatedInstanceNbItem(*Node, v);
				}

				Located->resize(v); 
			}
		} _MaxNbParticlesWrapper;


		/////////////////////////////////////////////////
		// wrapper to tune the mass of particles	   //
		/////////////////////////////////////////////////

		struct CMassWrapper : public IPSWrapperFloat, IPSSchemeWrapperFloat
		{
		   NL3D::CPSLocated *Located;
		   float get(void) const { return Located->getInitialMass(); }
		   void set(const float &v) { Located->setInitialMass(v); }
		   virtual scheme_type *getScheme(void) const { return Located->getMassScheme(); }
		   virtual void setScheme(scheme_type *s) { Located->setMassScheme(s); }
		} _MassWrapper;

		struct CLifeWrapper : public IPSWrapperFloat, IPSSchemeWrapperFloat
		{
		   CStartStopParticleSystem *SSPS;
		   NL3D::CPSLocated *Located;
		   CParticleWorkspace::CNode *Node;
		   float get(void) const { return Located->getInitialLife(); }
		   void set(const float &v) { Located->setInitialLife(v); SSPS->resetAutoCount(Node); }
		   virtual scheme_type *getScheme(void) const { return Located->getLifeScheme(); }
		   virtual void setScheme(scheme_type *s) { Located->setLifeScheme(s); SSPS->resetAutoCount(Node); }
		} _LifeWrapper;											


	// the located this dialog is editing
	NL3D::CPSLocated *_Located;


	/// update the integrable check box
	void updateIntegrable(void);

	/// update the 'trigger on death' control
	void updateTriggerOnDeath(void);

	// from CObjectViewer::IMainLoopCallBack
	virtual void goPostRender();
	virtual void goPreRender() {}


	// Generated message map functions
	//{{AFX_MSG(CLocatedProperties)
	virtual BOOL OnInitDialog();
	afx_msg void OnLimitedLifeTime();
	afx_msg void OnSystemBasis();
	afx_msg void OnDisgradeWithLod();
	afx_msg void OnParametricMotion();
	afx_msg void OnEditTriggerOnDeath();
	afx_msg void OnTriggerOnDeath();
	afx_msg void OnAssignCount();
	afx_msg void OnSelchangeMatrixMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void touchPSState();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCATED_PROPERTIES_H__772D6C3B_6CFD_47B5_A132_A8D2352EACF9__INCLUDED_)
