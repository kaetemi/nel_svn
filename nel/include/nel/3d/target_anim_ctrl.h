/** \file target_anim_ctrl.h
 * TODO: File description
 */

/* Copyright, 2000-2003 Nevrax Ltd.
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

#ifndef NL_TARGET_ANIM_CTRL_H
#define NL_TARGET_ANIM_CTRL_H

#include "nel/misc/types_nl.h"
#include "nel/misc/matrix.h"
#include "nel/misc/quat.h"
#include "nel/3d/anim_ctrl.h"


namespace NL3D {


// ***************************************************************************
/**
 * AnimCtrl used to constraint a bone to follow a target, either given by Position or Direction. Typical use for Head control
 *	Use TargetMode is better than computing Direction from Previous rendered Bone WorldMatrix (one frame late).
 *	The ctrl support AngleBlocking, and MaxBoneAngularSpeed (avoid strange head pop).
 *	The Bone must be in RotQuat mode, else the ctrl does nothing.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2003
 */
class CTargetAnimCtrl : public IAnimCtrl
{
public:

	enum TMode	{TargetMode=0, DirectionMode, NumMode};

public:
	/// Target controled or direction controled. Default to DirectionMode
	TMode			Mode;

	/// \name Target and Direction specific
	// @{
	/// For TargetMode, the world Position of the target.
	CVector			WorldTarget;
	/// For TargetMode only, the Pos of eyes relative to the bone controlled. Default to (0,0,0)
	CVector			EyePos;
	/// For DirectionMode, the WorldRotation to apply to the bone. NB: modified in execute() if TargetMode
	CQuat			CurrentWorldDirection;
	// @}

	/// \name Common
	// @{
	/** This enable or disable the ctrl. When disabled or enabled, the ctrl ensure
	 *	that the movement does not "pop", respecting MaxAngularVelocity. Default to true.
	 */
	bool			Enabled;
	/// This give The World Orientation when the Mesh is in bind Pos (default to "LookBack").
	CQuat			DefaultWorldDirection;
	///	The Maximum angle of rotation that can be performed between the Default Direction and Current Direction. Default to Pi/3
	float			MaxAngle;
	/// The Maximum Angular Velocity the ctrl can perform. Default to 2*Pi per second.
	float			MaxAngularVelocity;
	// @}


public:
	/// Constructor
	CTargetAnimCtrl();
	virtual ~CTargetAnimCtrl();

	/// Called at compute() time.
	virtual	void	execute(CSkeletonModel *model, CBone *bone);


private:

	/// The last rotation computed (in LocalSkeleton Space). Used to smooth transition
	CQuat			_LastLSRotation;

	/// This tells that a Enable/Disable transition is in progress.
	bool			_LastEnabled;
	bool			_EnableToDisableTransition;

	CQuat			getCurrentLSRotationFromBone(CSkeletonModel *model, CBone *bone);
};


} // NL3D


#endif // NL_TARGET_ANIM_CTRL_H

/* End of target_anim_ctrl.h */
