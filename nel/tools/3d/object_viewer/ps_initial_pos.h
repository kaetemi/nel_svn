/** \file ps_initial_pos.h
 *
 * $Id: ps_initial_pos.h,v 1.2 2004/06/18 09:51:50 vizerie Exp $
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

#ifndef NL_PS_INITIAL_POS
#define NL_PS_INITIAL_POS

namespace NL3D
{
	class CParticleSystem;
	class CPSLocated;
	class CPSLocatedBindable;
	struct IPSMover;
}


/** this class helps to copy the position of initial instances in a particle
 *  system. This enable a system to run, and have its parameter modified.
 *  When the user press stop, he will find the system at t = 0, with the new parameters
 */
class CPSInitialPos
{
public:
	CPSInitialPos() : _PS(NULL) {}
	// construct this by copying the datas of the system
	void copySystemInitialPos(NL3D::CParticleSystem *ps);
	/** reinitialize the system with its initial instances positions
	  * Works only once per copySystemInitialPos() call
	  */	  
	void restoreSystem();
	/// send back true when bbox display is enabled
	bool isBBoxDisplayEnabled();
	/// update data when a located in a particle system has been removed	
	void removeLocated(NL3D::CPSLocated *loc);
	/// update data when a located bindable in a particle system has been removed	
	void removeLocatedBindable(NL3D::CPSLocatedBindable *lb);		
	// initial position and speed of a located instance in a particle system
	struct CInitPSInstanceInfo
	{	
		uint32 Index;
		NL3D::CPSLocated *Loc;
		NLMISC::CVector Speed;
		NLMISC::CVector Pos;		
	};
	// rotation and scale of an element
	struct CRotScaleInfo
	{	
		uint32 Index;
		NL3D::CPSLocated *Loc;
		NL3D::CPSLocatedBindable *LB;
		NL3D::IPSMover *Psm;
		NLMISC::CMatrix Rot;
		NLMISC::CVector Scale;
	};
	NL3D::CParticleSystem *getPS() { return _PS; }
	const NL3D::CParticleSystem *getPS() const { return _PS; }
	bool isStateMemorized() const { return _PS != NULL; }
private:
	typedef std::vector<CInitPSInstanceInfo> TInitInfoVect;
	typedef std::vector<CRotScaleInfo> TRotScaleInfoVect;
	typedef std::vector< std::pair<NL3D::CPSLocated *, uint32> > TInitialLocatedSizeVect;
	TInitInfoVect _InitInfoVect;
	TRotScaleInfoVect _RotScaleInfoVect;
	// initial number of instances for each located
	TInitialLocatedSizeVect  _InitialSizeVect;
	NL3D::CParticleSystem *_PS;	
	// reset all initial infos
	void reset();	
};





#endif