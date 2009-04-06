/** \file class_transport/gd_service.cpp
 * Transport class example
 *
 * $Id: gd_service.cpp,v 1.1 2002/04/17 08:08:32 lecroart Exp $
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


/*
 * Transport class example, gd server.
 *
 * This service have a class (CSharedClass) that send to other service when online.
 *
 * To run this program, ensure there is a file "gd_service.cfg"
 * containing the location of the naming service (NSHost, NSPort)
 * in the working directory. The naming service must be running.
 */

//
// Includes
//

// We're using the NeL Service framework, and layer 5
#include "nel/net/service.h"
#include "nel/misc/time_nl.h"
#include "nel/misc/displayer.h"

#include "nel/net/transport_class.h"

#ifndef NL_CT_CFG
#define NL_CT_CFG ""
#endif // NL_CT_CFG

//
// Namespace
//

using namespace std;
using namespace NLNET;
using namespace NLMISC;

//
// Shared Class
//

struct CSharedClass : public CTransportClass
{
	uint32	i1, i2, i3;
	float	f1;

	vector<uint32> vi1;

	string str;

	CEntityId eid;

	CSharedClass () : i1(10), i2(10), f1(10), i3(10), str("str10") { vi1.push_back(111); vi1.push_back(222); vi1.push_back(255); }

	virtual void description ()
	{
		className ("SharedClass");
		property ("i1", PropUInt32, (uint32)11, i1);
		property ("f1", PropFloat,  1.5f, f1);
//		property ("i2", PropUInt32, (uint32)12, i2);
		property ("i3", PropUInt32, (uint32)13, i3);
		propertyCont ("vi1", PropUInt32, vi1);
		property ("str", PropString, (string)"str12", str);
//		property ("eid", PropEntityId, CEntityId::Unknown, eid);
	}

	virtual void callback (const string &name, uint8 sid)
	{
		nlinfo ("Yes! I receive a Shared class from '%s' %d", name.c_str(), sid);
	}
};

//
// Variables
//

static CSharedClass SharedClass;

//
// Functions
//

static void cbUpService (const std::string &serviceName, uint16 sid, void *arg)
{
	// When a service comes, send the new class
	CSharedClass foo;
	foo.send((TServiceId)sid);
}

//
// Service class
//

struct CGDService : public IService
{
	void init()
	{
		// callback when a new service comes
		CUnifiedNetwork::getInstance()->setServiceUpCallback("*", (TUnifiedNetCallback)cbUpService, NULL);

		// init the class transport system
		CTransportClass::init ();

		// register the shared class
		TRANSPORT_CLASS_REGISTER (CSharedClass);
	}

	void release ()
	{
		// release all the class transport system
		CTransportClass::release ();
	}
};


/*
 * Declare a service with the class IService, the names "GDS" (short) and "gd_service" (long).
 * The port is automatically allocated (0) and the main callback array is empty.
 */
NLNET_SERVICE_MAIN( CGDService, "GDS", "gd_service", 0, EmptyCallbackArray, NL_CT_CFG, "" )
