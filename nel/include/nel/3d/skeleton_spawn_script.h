/** \file skeleton_spawn_script.h
 * TODO: File description
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

#ifndef NL_SKELETON_SPAWN_SCRIPT_H
#define NL_SKELETON_SPAWN_SCRIPT_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"

#include "nel/3d/transform_shape.h"

namespace NL3D
{


class CScene;
class CSkeletonModel;


// ***************************************************************************
/**
 * For each skeleton, an animation of script can be assigned to spawn and unspawn models, which are sticked
 *	to some bones of the skeleton.
 *	This is the managers which read the scripts, spawn and unspawn instances according to changes of scripts
 *	(changes which are made through animation)
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2004
 */
class CSkeletonSpawnScript
{
public:
	CSkeletonSpawnScript();
	~CSkeletonSpawnScript();

	/// evaluate the current skeleton script
	void			evaluate(CSkeletonModel *skeleton);

	/// Must call it at destruction of the owner skeleton
	void			release(CScene *scene);

private:
	friend class CSSSModelRequest;

	// script cache to compare at each evaluate()
	std::string			_Cache;
	// List of instance spawned
	struct CInstance
	{
		// the 3D model created (NULL if failed). NB: a CRefPtr is used, in case of "AutoDeletable ParticleSystem" usage
		NLMISC::CRefPtr<CTransformShape>		Model;
		// this is a copy of the line in script, to compare for possible deletion
		std::string								ScriptLine;
		class CParticleSystemModel				*PS;
		CInstance()
		{
			Model= NULL;
			PS= NULL;
		}
	};
	std::vector<CInstance>	_Instances;


	// real parse stuff from _Cache
	void	parseCache(CScene *scene, CSkeletonModel *skeleton);

	// execute the request, or append to scene
	void	addModelCreationRequest(class CSSSModelRequest &req, CScene *scene);
};


// ***************************************************************************
/** Used by CSkeletonSpawnScript, to delay model creation
 */
class CSSSModelRequest
{
public:
	// Name o shape to create
	std::string				Shape;
	// Skeleton to bind to
	NLMISC::CRefPtr<NL3D::CSkeletonModel>	Skel;
	// Bone Id to stick to
	uint					BoneId;
	// where to store the instance result
	uint					InstanceId;
	// SSSWO mode
	bool					SSSWO;

	// execute the creation request
	void		execute();
};


} // NL3D


#endif // NL_SKELETON_SPAWN_SCRIPT_H

/* End of skeleton_spawn_script.h */
