/** \file u_particle_system_instance.cpp
 * Interface for particule system.
 *
 * $Id: u_particle_system_instance.cpp,v 1.3 2005/02/22 10:19:12 besson Exp $
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#include "nel/3d/u_particle_system_instance.h"
#include "particle_system.h"
#include "particle_system_shape.h"
#include "ps_emitter.h"
#include "particle_system_model.h"

#define NL3D_MEM_PS_INSTANCE						NL_ALLOC_CONTEXT( 3dPS )

namespace NL3D {


// ***************************************************************************
bool		UParticleSystemInstance::isSystemPresent(void) const
{
	NL3D_MEM_PS_INSTANCE			
	if (!_Object) return false; // the system is not even valid
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	return object->getPS() != NULL;
}

// ***************************************************************************
bool		UParticleSystemInstance::getSystemBBox(NLMISC::CAABBox &bbox)
{
	NL3D_MEM_PS_INSTANCE			
	if (!_Object) return false;
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	if (!object->getPS()) return false;
	object->getPS()->computeBBox(bbox);
	return true;
}


// ***************************************************************************
void UParticleSystemInstance::setUserColor(NLMISC::CRGBA userColor)
{
	NL3D_MEM_PS_INSTANCE
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	object->setUserColor(userColor);
}

// ***************************************************************************
NLMISC::CRGBA UParticleSystemInstance::getUserColor() const
{
	NL3D_MEM_PS_INSTANCE
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	return object->getUserColor();
}

// ***************************************************************************
void		UParticleSystemInstance::setUserParam(uint index, float value)
{	
	NL3D_MEM_PS_INSTANCE
	if (index >= MaxPSUserParam)
	{
		nlwarning("invalid user param index");
		return;
	}	
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	// object->getPS()->setUserParam(index, value);
	IAnimatedValue *av = object->getValue(CParticleSystemModel::PSParam0 + index);
	NLMISC::safe_cast<CAnimatedValueFloat *>(av)->Value = value;
	object->touch(CParticleSystemModel::PSParam0 + index, CParticleSystemModel::OwnerBit);	
}

// ***************************************************************************
float		UParticleSystemInstance::getUserParam(uint index) const
{
	NL3D_MEM_PS_INSTANCE
	if (index >= MaxPSUserParam)
	{
		nlwarning("invalid user param index");
		return 0.f;
	}
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object) ;
	//return object->getPS()->getUserParam(index) ;
	IAnimatedValue *av = object->getValue(CParticleSystemModel::PSParam0 + index);
	return NLMISC::safe_cast<CAnimatedValueFloat *>(av)->Value;
}

// ***************************************************************************
static inline uint32 IDToLittleEndian(uint32 input)
{
	NL3D_MEM_PS_INSTANCE			
	#ifdef NL_LITTLE_ENDIAN
		return input;
	#else
		return ((input & (0xff<<24))>>24)
				| ((input & (0xff<<16))>>8)
				| ((input & (0xff<<8))<<8)
				| ((input & 0xff)<<24);
	#endif
}

// ***************************************************************************
bool	UParticleSystemInstance::emit(uint32 anId, uint quantity)
{
	NL3D_MEM_PS_INSTANCE			
	const uint32 id = IDToLittleEndian(anId);
	nlassert(isSystemPresent());
	CParticleSystem *ps = (NLMISC::safe_cast<CParticleSystemModel *>(_Object))->getPS();
	uint numLb  = ps->getNumLocatedBindableByExternID(id);
	if (numLb == 0) return false; // INVALID ID !!
	for (uint k = 0; k < numLb; ++k)
	{
		CPSLocatedBindable *lb = ps->getLocatedBindableByExternID(id, k);		
		if (lb->getType() == PSEmitter)
		{
			CPSEmitter *e = NLMISC::safe_cast<CPSEmitter *>(lb);
			nlassert(e->getOwner());
			uint nbInstances = e->getOwner()->getSize();
			for (uint l = 0; l < nbInstances; ++l)
			{
				e->singleEmit(l, quantity);
			}
		}
	}
	return true;
}



// ***************************************************************************
bool UParticleSystemInstance::removeByID(uint32 anId)
{
	NL3D_MEM_PS_INSTANCE			
	const uint32 id = IDToLittleEndian(anId);
	if (!isSystemPresent()) return false;
	CParticleSystem *ps = (NLMISC::safe_cast<CParticleSystemModel *>(_Object))->getPS();
	uint numLb  = ps->getNumLocatedBindableByExternID(id);
	if (numLb == 0) return false; // INVALID ID !!
	for (uint k = 0; k < numLb; ++k)
	{
		CPSLocatedBindable *lb = ps->getLocatedBindableByExternID(id, k);
		CPSLocated *owner = lb->getOwner();
		nlassert(owner);
		uint nbInstances  =  owner->getSize();
		for (uint l = 0; l < nbInstances; ++l)
		{
			owner->deleteElement(0);
		}		
	}
	return true;
}

// ***************************************************************************
uint UParticleSystemInstance::getNumID() const
{
	NL3D_MEM_PS_INSTANCE			
	if (!isSystemPresent()) return 0;
	CParticleSystem *ps = (NLMISC::safe_cast<CParticleSystemModel *>(_Object))->getPS();
	return ps->getNumID();
}

// ***************************************************************************
uint32 UParticleSystemInstance::getID(uint index) const
{
	NL3D_MEM_PS_INSTANCE			
	if (!isSystemPresent()) return 0;
	CParticleSystem *ps = (NLMISC::safe_cast<CParticleSystemModel *>(_Object))->getPS();
	return ps->getID(index);
}

// ***************************************************************************
bool UParticleSystemInstance::getIDs(std::vector<uint32> &dest) const
{
	NL3D_MEM_PS_INSTANCE			
	if (!isSystemPresent()) return false;
	CParticleSystem *ps = (NLMISC::safe_cast<CParticleSystemModel *>(_Object))->getPS();
	ps->getIDs(dest);
	return true;
}

// ***************************************************************************
bool UParticleSystemInstance::setActive(uint32 anId, bool active)
{
	NL3D_MEM_PS_INSTANCE
	const uint32 id = IDToLittleEndian(anId);
	if (!isSystemPresent()) return false;
	CParticleSystem *ps = (NLMISC::safe_cast<CParticleSystemModel *>(_Object))->getPS();
	uint numLb  = ps->getNumLocatedBindableByExternID(id);
	if (numLb == 0) return false; // INVALID ID !!
	for (uint k = 0; k < numLb; ++k)
	{
		CPSLocatedBindable *lb = ps->getLocatedBindableByExternID(id, k);
		lb->setActive(active);		
	}
	return true;
}

// ***************************************************************************
void UParticleSystemInstance::activateEmitters(bool active)
{	
	NL3D_MEM_PS_INSTANCE	
	(NLMISC::safe_cast<CParticleSystemModel *>(_Object))->activateEmitters(active);
}

// ***************************************************************************
bool UParticleSystemInstance::hasActiveEmitters() const
{
	NL3D_MEM_PS_INSTANCE	
	return (NLMISC::safe_cast<CParticleSystemModel *>(_Object))->hasActiveEmitters();
}

// ***************************************************************************
bool UParticleSystemInstance::hasParticles() const
{
	NL3D_MEM_PS_INSTANCE
	if (!isSystemPresent()) return false;
	CParticleSystem *ps = (NLMISC::safe_cast<CParticleSystemModel *>(_Object))->getPS();
	return ps->hasParticles();
}

// ***************************************************************************
bool UParticleSystemInstance::hasEmmiters() const
{
	NL3D_MEM_PS_INSTANCE
	if (!isSystemPresent()) return false;
	CParticleSystem *ps = (NLMISC::safe_cast<CParticleSystemModel *>(_Object))->getPS();
	return ps->hasEmitters();
}
// ***************************************************************************
bool UParticleSystemInstance::isShared() const
{
	NL3D_MEM_PS_INSTANCE
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	if(object->Shape)
	{
		return NLMISC::safe_cast<CParticleSystemShape *>((IShape *) object->Shape)->isShared();
	}	
	return false;
}

// ***************************************************************************
void UParticleSystemInstance::setGlobalUserParamValue(const std::string &name, float value)
{
	NL3D_MEM_PS_INSTANCE
	if (name.empty())
	{
		nlwarning("invalid name");
		return;
	}
	CParticleSystem::setGlobalValue(name, value);
}

// ***************************************************************************
float UParticleSystemInstance::getGlobalUserParamValue(const std::string &name)
{
	NL3D_MEM_PS_INSTANCE
	if (name.empty())
	{
		nlwarning("invalid name");
		return 0.f;
	}
	return CParticleSystem::getGlobalValue(name);
}

// ***************************************************************************
void UParticleSystemInstance::setGlobalVectorValue(const std::string &name,const NLMISC::CVector &v)
{
	NL3D_MEM_PS_INSTANCE
	if (name.empty())
	{
		nlwarning("invalid name");
	}
	CParticleSystem::setGlobalVectorValue(name, v);
}

// ***************************************************************************
void UParticleSystemInstance::forceDisplayBBox(bool on)
{
	CParticleSystem::forceDisplayBBox(on);
}


// ***************************************************************************
NLMISC::CVector UParticleSystemInstance::getGlobalVectorValue(const std::string &name)
{
	NL3D_MEM_PS_INSTANCE
	if (name.empty())
	{
		nlwarning("invalid name");
		return NLMISC::CVector::Null;
	}
	else return CParticleSystem::getGlobalVectorValue(name);
}

// ***************************************************************************
void UParticleSystemInstance::bypassGlobalUserParamValue(uint userParamIndex, bool byPass /*=true*/)
{
	NL3D_MEM_PS_INSTANCE
	if (userParamIndex >= MaxPSUserParam)
	{
		nlwarning("invalid user param index");
		return;
	}
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	object->bypassGlobalUserParamValue(userParamIndex, byPass);
}

// ***************************************************************************
bool UParticleSystemInstance::isGlobalUserParamValueBypassed(uint userParamIndex) const
{
	NL3D_MEM_PS_INSTANCE
	if (userParamIndex >= MaxPSUserParam)
	{
		nlwarning("invalid user param index");
		return 0.f;
	}
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	return isGlobalUserParamValueBypassed(userParamIndex);
}

// ***************************************************************************
void UParticleSystemInstance::setUserMatrix(const NLMISC::CMatrix &userMat)
{
	NL3D_MEM_PS_INSTANCE
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	object->setUserMatrix(userMat);
}

// ***************************************************************************
void UParticleSystemInstance::forceSetUserMatrix(const NLMISC::CMatrix &userMat)
{
	NL3D_MEM_PS_INSTANCE
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	object->forceSetUserMatrix(userMat);	
}


// ***************************************************************************
void UParticleSystemInstance::forceInstanciate()
{
	NL3D_MEM_PS_INSTANCE
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	object->forceInstanciate();
}

// ***************************************************************************
void UParticleSystemInstance::setZBias(float value)
{
	NL3D_MEM_PS_INSTANCE
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	object->setZBias(value);
}

// ***************************************************************************

void UParticleSystemInstance::cast(UInstance object)
{
	attach(dynamic_cast<CParticleSystemModel*> (object.getObjectPtr()));
}

// ***************************************************************************
bool UParticleSystemInstance::isValid() const
{
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);
	return !object->isInvalid();
}

// ***************************************************************************
void UParticleSystemInstance::stopSound()
{
	if (!_Object) return;
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);	
	object->stopSound();
}

// ***************************************************************************
void UParticleSystemInstance::reactivateSound()
{
	if (!_Object) return;
	CParticleSystemModel *object = NLMISC::safe_cast<CParticleSystemModel *>(_Object);	
	object->reactivateSound();
}


// ***************************************************************************

} // NL3D
