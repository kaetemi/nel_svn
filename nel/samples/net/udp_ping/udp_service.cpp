/** \file udp_service.cpp
 * This service just listen the port set in the .cfg and display and reply
 * when an UDP datagram is received.
 *
 * $Id: udp_service.cpp,v 1.1 2003/01/21 17:38:08 lecroart Exp $
 */

/* Copyright, 2003 Nevrax Ltd.
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

//
// Includes
//

#include "nel/misc/types_nl.h"

#include "nel/net/service.h"
#include "nel/net/udp_sim_sock.h"

//
// Namespaces
//

using namespace std;
using namespace NLMISC;
using namespace NLNET;

//
// Variables
//

CUdpSock			*UdpSock = NULL;

//
// Main Class
//

class CBenchService : public IService
{
public:
	
	void init()
	{
		uint16 port = ConfigFile.getVar("UdpPort").asInt();
		nlinfo ("Starting external UDP socket on port %d", port);
		UdpSock = new CUdpSock (false);
		nlassert (UdpSock);
		UdpSock->bind (port);
	}

	bool update ()
	{
		try
		{
			uint len;
			CInetAddress addr;
			uint8 buffer[1000];
			
			while (UdpSock->dataAvailable())
			{
				len = 1000;
				UdpSock->receivedFrom((uint8*)buffer, len, addr);
				nlinfo ("Received UDP datagram size %d from %s", len, addr.asString().c_str());

				CMemStream msgout;
				uint32 foo = 10;
				msgout.serial (foo);
				uint32 size = msgout.length();
				UdpSock->sendTo (msgout.buffer(), size, addr);
				nldebug ("Sent UDP datagram size %d to %s", size, addr.asString().c_str());
			}
		}
		catch (Exception &e)
		{
			nlwarning ("Exception catched: '%s'", e.what());
		}
		return true;
	}

	void release ()
	{
		if (UdpSock != NULL)
			delete UdpSock;
	}
};


NLNET_SERVICE_MAIN (CBenchService, "UDPS", "udp_service", 0, EmptyCallbackArray, "", "")
