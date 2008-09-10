/** \file ps_wrapper.h
 *  here we define interface that helps to create wrappers between the particle system interface and 
 *	 a dialog.
 *
 *
 * $Id: ps_wrapper.h,v 1.8 2007/03/19 09:55:26 boucher Exp $
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



#ifndef _PS_WRAPPER_H
#define _PS_WRAPPER_H




#include "nel/misc/rgba.h"
#include "nel/misc/vector.h"
//
#include "nel/3d/ps_attrib_maker.h"
#include "nel/3d/texture.h"
//
#include "particle_workspace.h"


// wrapper to read/write a value of type T
template <class T> class IPSWrapper
{
public:
	CParticleWorkspace::CNode *OwnerNode; // Owner node of the property. When the property is modified, then the node will be marked as 'modified'
public:
	IPSWrapper() : OwnerNode(NULL)
	{
	}
	// for derivers : get a value
	virtual T get(void) const = 0;
	void setAndUpdateModifiedFlag(const T &value)
	{
		if (OwnerNode)
		{
			OwnerNode->setModified(true);
		}
		set(value);
	}
protected:
	// for derivers : set a value
	virtual void set(const T &) = 0;
};


// wrapper to read/write a scheme of type T
template <class T> class IPSSchemeWrapper
{
public:
	CParticleWorkspace::CNode *OwnerNode; // Owner node of the property. When the property is modified, then the node will be marked as 'modified'
public:
	IPSSchemeWrapper() : OwnerNode(NULL) {}
	typedef NL3D::CPSAttribMaker<T> scheme_type;
	virtual scheme_type *getScheme(void) const = 0;
	void setSchemeAndUpdateModifiedFlag(scheme_type *s)	
	{
		if (OwnerNode)
		{
			OwnerNode->setModified(true);
		}
		setScheme(s);
	}
protected:
	virtual void setScheme(scheme_type *s) = 0;
};



// RGBA wrapper
typedef IPSWrapper<NLMISC::CRGBA> IPSWrapperRGBA;
typedef IPSSchemeWrapper<NLMISC::CRGBA> IPSSchemeWrapperRGBA;

// float wrapper
typedef IPSWrapper<float> IPSWrapperFloat;
typedef IPSSchemeWrapper<float> IPSSchemeWrapperFloat;

// uint wrapper
typedef IPSWrapper<uint32> IPSWrapperUInt;
typedef IPSSchemeWrapper<uint32> IPSSchemeWrapperUInt;


// texture
class IPSWrapperTexture
{
public:
	CParticleWorkspace::CNode *OwnerNode;
public:
	// ctor
	IPSWrapperTexture() : OwnerNode(NULL) {}
	virtual NL3D::ITexture *get(void) = 0;
	virtual void setAndUpdateModifiedFlag(NL3D::ITexture *tex)
	{
		if (OwnerNode) OwnerNode->setModified(true);
		set(tex);
	}
protected:
	virtual void set(NL3D::ITexture *) = 0;
};

#endif