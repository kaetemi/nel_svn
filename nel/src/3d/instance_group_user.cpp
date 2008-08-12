/** \file instance_group_user.cpp
 * Implementation of the user interface managing instance groups.
 *
 * $Id: instance_group_user.cpp,v 1.42 2005/02/22 10:19:10 besson Exp $
 */

/* Copyright, 2001 Nevrax Ltd.
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

#include "std3d.h"

#include "nel/misc/debug.h"
#include "nel/3d/instance_group_user.h"
#include "nel/3d/scene_user.h"
#include "nel/3d/mesh_multi_lod_instance.h"
#include "nel/3d/text_context_user.h"
#include "nel/3d/particle_system_model.h"
#include "nel/misc/path.h"
#include "nel/misc/file.h"
#include "nel/3d/u_instance.h"

using namespace NLMISC;
using namespace std;

namespace NL3D 
{

// ***************************************************************************

UInstanceGroup	*UInstanceGroup::createInstanceGroup (const std::string &instanceGroup)
{
	NL3D_MEM_IG
	// Create the instance group
	CInstanceGroupUser *user=new CInstanceGroupUser;

	// Init the class
	if (!user->init (instanceGroup))
	{
		// Prb, erase it
		delete user;

		// Return error code
		return NULL;
	}

	// return the good value
	return user;
}

// ***************************************************************************

void UInstanceGroup::createInstanceGroupAsync (const std::string &instanceGroup, UInstanceGroup	**pIG)
{
	NL3D_MEM_IG
	CAsyncFileManager3D::getInstance().loadIGUser (instanceGroup, pIG);
}

// ***************************************************************************

void UInstanceGroup::stopCreateInstanceGroupAsync (UInstanceGroup **ppIG)
{
	NL3D_MEM_IG
	// Theorically should stop the async file manager but the async file manager can only be stopped
	// between tasks (a file reading) so that is no sense to do anything here
	while (*ppIG == NULL)
	{
		nlSleep (2);
	}
	if (*ppIG != (UInstanceGroup*)-1)
	{
		delete *ppIG;
	}
}

// ***************************************************************************
CInstanceGroupUser::CInstanceGroupUser()
{
	/* ***********************************************
	 *	WARNING: This Class/Method must be thread-safe (ctor/dtor/serial): no static access for instance
	 *	It can be loaded/called through CAsyncFileManager for instance
	 * ***********************************************/
	
	NL3D_MEM_IG
	_AddToSceneState = StateNotAdded;

	// set user info for possible get
	_InstanceGroup.setUserInterface(this);
}

// ***************************************************************************
CInstanceGroupUser::~CInstanceGroupUser()
{
	/* ***********************************************
	 *	WARNING: This Class/Method must be thread-safe (ctor/dtor/serial): no static access for instance
	 *	It can be loaded/called through CAsyncFileManager for instance
	 * ***********************************************/
	
	// ensure all instances proxys are deleted
	removeInstancesUser();
}

// ***************************************************************************
bool CInstanceGroupUser::init (const std::string &instanceGroup, bool async)
{
	NL3D_MEM_IG
	// Create a file
	CIFile file;
	if(async)
	{
		file.setAsyncLoading(true);
		file.setCacheFileOnOpen(true);
	}
	std::string path = CPath::lookup (instanceGroup, false);
	if (!path.empty() && file.open (path))
	{
		// Serialize this class
		try
		{
			// Read the class
			_InstanceGroup.serial (file);
		}
		catch (EStream& e)
		{
			// Avoid visual warning
			EStream ee=e;

			// Serial problem
			return false;
		}
	}
	else
	{
		// Failed.
		return false;
	}

	// Ok
	return true;
}

// ***************************************************************************
void CInstanceGroupUser::setTransformNameCallback (ITransformName *pTN)
{
	NL3D_MEM_IG
	_InstanceGroup.setTransformNameCallback (pTN);
}


// ***************************************************************************
void CInstanceGroupUser::setAddRemoveInstanceCallback(IAddRemoveInstance *callback)
{
	NL3D_MEM_IG
	_InstanceGroup.setAddRemoveInstanceCallback(callback);
}


// ***************************************************************************
void CInstanceGroupUser::setIGAddBeginCallback(IIGAddBegin *callback)
{
	NL3D_MEM_IG
	_InstanceGroup.setIGAddBeginCallback(callback);
}



// ***************************************************************************
void CInstanceGroupUser::addToScene (class UScene& scene, UDriver *driver, uint selectedTexture)
{
	NL3D_MEM_IG
	// Get driver pointer
	IDriver *cDriver= driver ? NLMISC::safe_cast<CDriverUser*>(driver)->getDriver() : NULL;

	// Add to the scene
	addToScene (((CSceneUser*)&scene)->getScene(), cDriver, selectedTexture);
}

// ***************************************************************************
void CInstanceGroupUser::getInstanceMatrix(uint instanceNb,NLMISC::CMatrix &dest) const
{
	NL3D_MEM_IG
	_InstanceGroup.getInstanceMatrix(instanceNb, dest);	
}


// ***************************************************************************
void CInstanceGroupUser::addToScene (class CScene& scene, IDriver *driver, uint selectedTexture)
{
	NL3D_MEM_IG
	if (!_InstanceGroup.addToScene (scene, driver, selectedTexture))
		return;
	// Fill in the vector and the map accelerating search of instance by names
	for( uint32 i = 0; i < _InstanceGroup._Instances.size(); ++i)
	{
		string stmp;
		if (_InstanceGroup._Instances[i] != NULL)
		{
			// insert in map (may fail if double name)
			stmp = _InstanceGroup.getInstanceName (i);
			_InstanceMap.insert (map<string,CTransformShape*>::value_type(stmp, _InstanceGroup._Instances[i]));
		}
	}
}

// ***************************************************************************
void CInstanceGroupUser::addToSceneAsync (class UScene& scene, UDriver *driver, uint selectedTexture)
{
	NL3D_MEM_IG
	IDriver *cDriver= driver ? NLMISC::safe_cast<CDriverUser*>(driver)->getDriver() : NULL;
	// Add to the scene
	_InstanceGroup.addToSceneAsync (((CSceneUser*)&scene)->getScene(), cDriver, selectedTexture);
	_AddToSceneState = StateAdding;
	_AddToSceneTempScene = &scene;
	_AddToSceneTempDriver = driver;
}

// ***************************************************************************
void CInstanceGroupUser::stopAddToSceneAsync ()
{
	NL3D_MEM_IG
	_InstanceGroup.stopAddToSceneAsync ();
}

// ***************************************************************************
UInstanceGroup::TState CInstanceGroupUser::getAddToSceneState ()
{
	NL3D_MEM_IG
	UInstanceGroup::TState newState = (UInstanceGroup::TState)_InstanceGroup.getAddToSceneState ();
	if ((_AddToSceneState == StateAdding) && (newState == StateAdded))
	{
		// Fill in the vector and the map accelerating search of instance by names
		for( uint32 i = 0; i < _InstanceGroup._Instances.size(); ++i)
		{
			string stmp;
			if (_InstanceGroup._Instances[i] != NULL)
			{
				// create but don't want to delete from scene, since added/removed with _InstanceGroup
				// insert in map (may fail if double name)
				stmp = _InstanceGroup.getInstanceName (i);
				_InstanceMap.insert (map<string,CTransformShape*>::value_type(stmp, _InstanceGroup._Instances[i]));
			}
		}
		_AddToSceneState = StateAdded;
	}
	return newState;
}

// ***************************************************************************
void CInstanceGroupUser::removeFromScene (class UScene& scene)
{
	NL3D_MEM_IG
	_InstanceGroup.removeFromScene (((CSceneUser*)&scene)->getScene());
	// Remove all instance user object in the array/map
	removeInstancesUser();
}

// ***************************************************************************
uint CInstanceGroupUser::getNumInstance () const
{
	NL3D_MEM_IG
	return _InstanceGroup.getNumInstance ();
}

// ***************************************************************************

const std::string& CInstanceGroupUser::getShapeName (uint instanceNb) const
{
	NL3D_MEM_IG
	// Check args
	if (instanceNb>=_InstanceGroup.getNumInstance ())
		nlerror("getShapeName*(): bad instance Id");
	
	return _InstanceGroup.getShapeName (instanceNb);
}

// ***************************************************************************
const std::string& CInstanceGroupUser::getInstanceName (uint instanceNb) const
{
	NL3D_MEM_IG
	// Check args
	if (instanceNb>=_InstanceGroup.getNumInstance ())
		nlerror("getInstanceName*(): bad instance Id");
	
	return _InstanceGroup.getInstanceName (instanceNb);
}

// ***************************************************************************
const NLMISC::CVector& CInstanceGroupUser::getInstancePos (uint instanceNb) const
{
	NL3D_MEM_IG
	// Check args
	if (instanceNb>=_InstanceGroup.getNumInstance ())
		nlerror("getInstancePos*(): bad instance Id");
	
	return _InstanceGroup.getInstancePos (instanceNb);
}

// ***************************************************************************
const NLMISC::CQuat& CInstanceGroupUser::getInstanceRot (uint instanceNb) const
{
	NL3D_MEM_IG
	// Check args
	if (instanceNb>=_InstanceGroup.getNumInstance ())
		nlerror("getInstanceRot*(): bad instance Id");
	
	return _InstanceGroup.getInstanceRot (instanceNb);
}

// ***************************************************************************
const NLMISC::CVector& CInstanceGroupUser::getInstanceScale (uint instanceNb) const
{
	NL3D_MEM_IG
	// Check args
	if (instanceNb>=_InstanceGroup.getNumInstance ())
		nlerror("getInstanceScale*(): bad instance Id");
	
	return _InstanceGroup.getInstanceScale (instanceNb);
}

// ***************************************************************************

UInstance CInstanceGroupUser::getByName (const std::string &name) const
{
	NL3D_MEM_IG
	map<string,CTransformShape*>::const_iterator it = _InstanceMap.find (name);
	if (it != _InstanceMap.end())
		return UInstance (it->second);
	else
		return UInstance ();
}

// ***************************************************************************
sint CInstanceGroupUser::getIndexByName(const std::string &name) const
{
	NL3D_MEM_IG
	map<string,CTransformShape*>::const_iterator it = _InstanceMap.find (name);
	if (it == _InstanceMap.end()) return -1;
	for(uint k = 0; k < _InstanceGroup._Instances.size(); ++k)
	{
		if (_InstanceGroup._Instances[k] == it->second) return (sint) k;
	}
	return -1;	
}


// ***************************************************************************
void CInstanceGroupUser::setBlendShapeFactor (const std::string &bsName, float rFactor)
{
	NL3D_MEM_IG
	_InstanceGroup.setBlendShapeFactor (bsName, rFactor);
}

// ***************************************************************************

void CInstanceGroupUser::createRoot (UScene &scene)
{
	NL3D_MEM_IG
	_InstanceGroup.createRoot (((CSceneUser*)&scene)->getScene());
}

// ***************************************************************************
void CInstanceGroupUser::setClusterSystemForInstances (UInstanceGroup *pClusterSystem)
{
	NL3D_MEM_IG
	_InstanceGroup.setClusterSystemForInstances (&((CInstanceGroupUser*)pClusterSystem)->_InstanceGroup);
}

// ***************************************************************************
bool CInstanceGroupUser::linkToParentCluster(UInstanceGroup *father)
{
	NL3D_MEM_IG
	if (father)
		return _InstanceGroup.linkToParent(&(NLMISC::safe_cast<CInstanceGroupUser *>(father)->_InstanceGroup));
	else
	{
		nlwarning("Trying to link a cluster system to a NULL parent cluster");
		return false;
	}
}

// ***************************************************************************
void CInstanceGroupUser::getDynamicPortals (std::vector<std::string> &names)
{
	NL3D_MEM_IG
	_InstanceGroup.getDynamicPortals (names);
}

// ***************************************************************************
void CInstanceGroupUser::setDynamicPortal (std::string& name, bool opened)
{
	NL3D_MEM_IG
	_InstanceGroup.setDynamicPortal (name, opened);
}

// ***************************************************************************
bool CInstanceGroupUser::getDynamicPortal (std::string& name)
{
	NL3D_MEM_IG
	return _InstanceGroup.getDynamicPortal (name);
}

// ***************************************************************************
void CInstanceGroupUser::setPos (const NLMISC::CVector &pos)
{
	NL3D_MEM_IG
	_InstanceGroup.setPos (pos);
}

// ***************************************************************************
void CInstanceGroupUser::setRotQuat (const NLMISC::CQuat &q)
{
	NL3D_MEM_IG
	_InstanceGroup.setRotQuat (q);
}

// ***************************************************************************
CVector CInstanceGroupUser::getPos ()
{
	NL3D_MEM_IG
	return _InstanceGroup.getPos ();
}

// ***************************************************************************
CQuat CInstanceGroupUser::getRotQuat ()
{
	NL3D_MEM_IG
	return _InstanceGroup.getRotQuat();
}


// ***************************************************************************
void			CInstanceGroupUser::freezeHRC()
{
	NL3D_MEM_IG
	_InstanceGroup.freezeHRC();
}

// ***************************************************************************
void			CInstanceGroupUser::unfreezeHRC()
{
	NL3D_MEM_IG
	_InstanceGroup.unfreezeHRC();
}


// ***************************************************************************
bool			CInstanceGroupUser::getStaticLightSetup(NLMISC::CRGBA sunAmbient,
		uint retrieverIdentifier, sint surfaceId, const NLMISC::CVector &localPos, 
		std::vector<CPointLightInfluence> &pointLightList, uint8 &sunContribution, NLMISC::CRGBA &localAmbient)
{
	NL3D_MEM_IG
	return _InstanceGroup.getStaticLightSetup(sunAmbient, retrieverIdentifier, surfaceId, localPos, pointLightList, 
		sunContribution, localAmbient);
}

// ***************************************************************************
/*virtual*/ void CInstanceGroupUser::setDistMax(uint instance, float dist)
{
	if (instance > _InstanceGroup.getNumInstance())
	{
		nlwarning("CInstanceGroupUser::setDistMax : instance index %d is invalid", instance);
		return;
	}
	if (_InstanceGroup._Instances[instance]) _InstanceGroup._Instances[instance]->setDistMax(dist);	
}

// ***************************************************************************
/*virtual*/ float CInstanceGroupUser::getDistMax(uint instance) const
{
	if (instance > _InstanceGroup.getNumInstance())
	{
		nlwarning("CInstanceGroupUser::getDistMax : instance index %d is invalid", instance);
		return -1.f;
	}
	if (_InstanceGroup._Instances[instance]) return _InstanceGroup._Instances[instance]->getDistMax();
	else return -1.f;
}

// ***************************************************************************
/*virtual*/ void CInstanceGroupUser::setCoarseMeshDist(uint instance, float dist)
{
	if (instance > _InstanceGroup.getNumInstance())
	{
		nlwarning("CInstanceGroupUser::setCoarseMeshDist : instance index %d is invalid", instance);
		return;
	}
	if (_InstanceGroup._Instances[instance]) 
	{	
		CMeshMultiLodInstance *mmli = dynamic_cast<CMeshMultiLodInstance *>(_InstanceGroup._Instances[instance]);
		if (mmli) mmli->setCoarseMeshDist(dist);
	}
}

// ***************************************************************************
/*virtual*/ float CInstanceGroupUser::getCoarseMeshDist(uint instance) const
{
	if (instance > _InstanceGroup.getNumInstance())
	{
		nlwarning("getCoarseMeshDist::getDistMax : instance index %d is invalid", instance);
		return -1.f;
	}
	if (_InstanceGroup._Instances[instance]) 
	{
		CMeshMultiLodInstance *mmli = dynamic_cast<CMeshMultiLodInstance *>(_InstanceGroup._Instances[instance]);
		if (mmli) return mmli->getCoarseMeshDist();
		else return -1.f;
	}		
	else return -1.f;
}

// ***************************************************************************
UInstance	CInstanceGroupUser::getInstance (uint instanceNb) const
{
	if(instanceNb<_InstanceGroup._Instances.size())
		return UInstance (_InstanceGroup._Instances[instanceNb]);
	else
		return UInstance ();
}

// ***************************************************************************
void		CInstanceGroupUser::removeInstancesUser()
{
	/* ***********************************************
	 *	WARNING: This Class/Method must be thread-safe (ctor/dtor/serial): no static access for instance
	 *	It can be loaded/called through CAsyncFileManager for instance
	 * ***********************************************/
	
	// clear the array and the map
	_InstanceMap.clear();
}

// ***************************************************************************
UInstanceGroup *CInstanceGroupUser::getParentCluster() const
{
	CInstanceGroup	*parent= _InstanceGroup.getParentClusterSystem();
	if(parent)
		// NB: return NULL if this is the GlobalInstanceGroup.
		return parent->getUserInterface();
	else
		return NULL;
}

// ***************************************************************************
void			CInstanceGroupUser::displayDebugClusters(UDriver *drv, UTextContext *txtCtx)
{
	if(!drv)
		return;
	CTextContext	*pTxtCtx= NULL;
	if(txtCtx)
		pTxtCtx= &((CTextContextUser*)txtCtx)->getTextContext();
	_InstanceGroup.displayDebugClusters(((CDriverUser*)drv)->getDriver(), pTxtCtx);

	// restore the matrix context cause of font rendering
	((CDriverUser*)drv)->restoreMatrixContext();
}

// ***************************************************************************
bool			CInstanceGroupUser::dontCastShadowForInterior(uint instance) const
{
	NL3D_MEM_IG
	if (instance>=_InstanceGroup.getNumInstance ())
		return false;
	return _InstanceGroup.getInstance(instance).DontCastShadowForInterior;
}

// ***************************************************************************
bool			CInstanceGroupUser::dontCastShadowForExterior(uint instance) const
{
	NL3D_MEM_IG
	if (instance>=_InstanceGroup.getNumInstance ())
		return false;
	return _InstanceGroup.getInstance(instance).DontCastShadowForExterior;
}


} // NL3D
