/** \file login_system/frontend_service.cpp
 * Login system example
 *
 * $Id: frontend_service.cpp,v 1.1 2002/04/17 08:08:32 lecroart Exp $
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
 * Layer 4 and Service example, front-end server.
 *
 * To run this program, ensure there is a file "frontend_service.cfg"
 * containing the location of the naming service (NSHost, NSPort)
 * in the working directory.
 * The NeL naming_service, time_service, login_service, welcome_service must be running.
 */


// We're using the NeL Service framework and layer 5.
#include "nel/misc/config_file.h"
#include "nel/misc/bit_mem_stream.h"

#include "nel/net/callback_server.h"
#include "nel/net/service.h"
#include "nel/net/login_server.h"

using namespace std;
using namespace NLNET;
using namespace NLMISC;

//#define USE_UDP
#undef USE_UDP


#ifndef USE_UDP

//
// TCP server mode
//

/*
 * Connection callback for a client
 */
void onConnectionClient (TSockId from, const CLoginCookie &cookie)
{
	nlinfo ("The client with uniq Id %d is connected", cookie.getUserId ());

	// store the user id in appId
	from->setAppId (cookie.getUserId ());
}


/*
 * Disonnection callback for a client
 */
void onDisconnectClient (TSockId from, void *arg)
{
	nlinfo ("A client with uniq Id %d has disconnected", from->appId ());

	// tell the login system that this client is disconnected
	CLoginServer::clientDisconnected ((uint32) from->appId ());
}

/*
 * CFrontEndService, based on IService
 */
class CFrontEndService : public IService
{
private:
	/// The server on which the clients connect
	CCallbackServer		_FEServer;

public:

	/*
	 * Initialization
	 */
	void init()
	{
		// connect the front end login system
		uint16	fesPort = 37373;
		try
		{
			fesPort = IService::ConfigFile.getVar("FESPort").asInt();
		}
		catch ( EUnknownVar& )
		{
		}
		_FEServer.init(fesPort);
		CLoginServer::init (_FEServer, onConnectionClient); 

		//
		_FEServer.setDisconnectionCallback(onDisconnectClient, NULL);
	}

	bool	update()
	{
		_FEServer.update();
		return true;
	}
};

#else // USE_UDP

//
// UDP server mode
//

#include "nel/net/udp_sock.h"

/*
 * CFrontEndService, based on IService
 */
class CFrontEndService : public IService
{
private:
	/// The server on which the clients connect
	CUdpSock *_FEServer;

public:

	/*
	 * Initialization
	 */
	void init()
	{
		// connect the front end login system
		uint16	fesPort = 37373;
		try
		{
			fesPort = IService5::ConfigFile.getVar("FESPort").asInt();
		}
		catch ( EUnknownVar& )
		{
		}

		// Socket
		_FEServer = new CUdpSock( false );
		nlassert( _FEServer );

		// Test of multihomed host
		vector<CInetAddress> addrlist;
		addrlist = CInetAddress::localAddresses();
		vector<CInetAddress>::iterator ivi;
		for ( ivi=addrlist.begin(); ivi!=addrlist.end(); ++ivi )
		{
			nlinfo( "%s", (*ivi).asIPString().c_str() );
		}
		addrlist[0].setPort( fesPort );
		_FEServer->bind( addrlist[0] );
		
		CLoginServer::init (*_FEServer, NULL); 
	}

	bool	update()
	{
		uint8 buf[64000];
		uint len;
		CInetAddress addr;

		while (_FEServer->dataAvailable ())
		{
			len = 64000;
			_FEServer->receivedFrom (buf, len, addr);

			CBitMemStream msgin (true);
			msgin.clear ();
			memcpy (msgin.bufferToFill (len), &buf[0], len);

			CLoginCookie lc;
			msgin.serial (lc);

			nlinfo ("Receive the cookie %s from %s", lc.toString ().c_str(), addr.asString ().c_str());

			string res = CLoginServer::isValidCookie (lc);

			// send the result
			CBitMemStream msgout;
			msgout.serial (res);
			uint32 l = msgout.length ();
			_FEServer->sendTo (msgout.buffer (), l, addr);
		}
		return true;
	}
};

#endif // USE_UDP

/*
 * Declare a service with the class CFrontEndService, the names "FS" (short) and "frontend_service" (long).
 * The port is dynamicaly find and there s no callback array.
 */
NLNET_SERVICE_MAIN (CFrontEndService, "FS", "frontend_service", 0, EmptyCallbackArray, "", "")
