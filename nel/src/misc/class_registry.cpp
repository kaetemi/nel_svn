/** \file class_registry.cpp
 * This File handles CClassRegistry.
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

#include "stdmisc.h"

#include "nel/misc/class_registry.h"

#include <typeinfo>

using namespace std;

namespace NLMISC
{


// ======================================================================================================
CClassRegistry::TClassMap		*CClassRegistry::RegistredClasses = NULL;


// ======================================================================================================
void		CClassRegistry::init()
{
	if (RegistredClasses == NULL)
		RegistredClasses = new TClassMap;
}

// ======================================================================================================
void		CClassRegistry::release()
{
	if( RegistredClasses )
		delete RegistredClasses;
	RegistredClasses = NULL;
}

// ======================================================================================================
IClassable	*CClassRegistry::create(const string &className)  throw(ERegistry)
{
	init();

	TClassMap::iterator	it;

	it=RegistredClasses->find(className);

	if(it==RegistredClasses->end())
		return NULL;
	else
	{
		IClassable	*ptr;
		ptr=it->second.Creator();
		#ifdef NL_DEBUG
			nlassert(CClassRegistry::checkObject(ptr));
		#endif
		return ptr;
	}

}

// ======================================================================================================
void		CClassRegistry::registerClass(const string &className, IClassable* (*creator)(), const string &typeidCheck)  throw(ERegistry)
{
	init();

	CClassNode	node;
	node.Creator=creator;
	node.TypeIdCheck= typeidCheck;
	std::pair<TClassMap::iterator, bool> result;
	result = RegistredClasses->insert(TClassMap::value_type(className, node));
	if(!result.second)
	{
		nlstop;
		throw ERegisteredClass();
	}
}

// ======================================================================================================
bool		CClassRegistry::checkObject(IClassable* obj)
{
	init();

	TClassMap::iterator	it;
	it=RegistredClasses->find(obj->getClassName());
	if(it==RegistredClasses->end())
		return false;

	if( it->second.TypeIdCheck != string(typeid(*obj).name()) )
		return false;

	return true;
}



}






















