/** \file login_system/client.cpp
 * Login system example
 *
 * $Id: client.cpp,v 1.1 2002/04/17 08:08:32 lecroart Exp $
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
 * Login system example, client.
 *
 * This client connects to a front-end server using login system.
 *
 * Before running this client, the front end service sample must run,
 * and also the NeL naming_service, time_service, login_service, welcome_service.
 *
 */

//
// Includes
//

#include <string>

#include "nel/misc/types_nl.h"
#include "nel/misc/debug.h"
#include "nel/misc/config_file.h"
#include "nel/misc/bit_mem_stream.h"

#include "nel/net/login_client.h"
#include "nel/net/login_cookie.h"

#include "nel/net/udp_sock.h"


//
// Namespaces
//

using namespace std;
using namespace NLMISC;
using namespace NLNET;


//
// Functions
//

//#define USE_UDP
#undef USE_UDP

/*
 * main
 */
void main (int argc, char **argv)
{
	string result;

	CConfigFile ConfigFile;
	
	ConfigFile.load ("client.cfg");

	string LSHost(ConfigFile.getVar("LSHost").asString());

	char	buf[256];
	printf("Login: ");
	gets(buf);
	string	Login(buf);

	printf("Password: ");
	gets(buf);
	string	Password(buf);

	if (Login.empty ())
	{
		Login = ConfigFile.getVar("Login").asString();
	}

	if (Password.empty ())
	{
		Password = ConfigFile.getVar("Password").asString();
	}

	/* Try to connect to the login service and check the login, password and version of the client.
	 * return an empty string if all go well
	 */
	result = CLoginClient::authenticate(LSHost+":49999", Login, Password, 1);
	
	if(!result.empty()) nlerror ("*** Authenticate failed '%s' ***", result.c_str());

	// CLoginClient::ShardList contains all available shards
	for (uint i = 0; i < CLoginClient::ShardList.size (); i++)
	{
		nlinfo ("*** shard %d is: %s (%s) ***", i, CLoginClient::ShardList[i].ShardName.c_str (), CLoginClient::ShardList[i].WSAddr.c_str ());
	}

	printf("Shard number: ");
	gets(buf);
	uint32 sn = atoi(buf);

	/* Try to connect to the shard number 0 in the list.
	 * return an empty string if all go well
	 */

#ifndef USE_UDP
	
	CCallbackClient *cnx = new CCallbackClient();
	result = CLoginClient::connectToShard (sn, *cnx);

	if(!result.empty()) nlerror ("*** Connection to the shard failed '%s' ***", result.c_str());

	nlinfo ("*** Connection granted! You are connected on the frond end ***");

	while (cnx->connected ())
	{
		cnx->update ();
		nlSleep(10);
	}

	if( cnx->connected ())
		cnx->disconnect ();

#else // USE_UDP

	CUdpSock *cnx = new CUdpSock();
	CLoginCookie lc;
	result = CLoginClient::connectToShard (0, *cnx, lc);

	if(!result.empty()) nlerror ("*** Connection to the shard failed '%s' ***", result.c_str());

	// we have to talk with the FES to send the cookie

	CBitMemStream msgout;
	msgout.serial (lc);
	while (true)
	{
		// send the cookie
		uint32 len = msgout.length ();
		cnx->send (msgout.buffer (), len);

		uint8 buf[64000];
		if (cnx->dataAvailable ())
		{
			// manage answer
			len = 64000;
			cnx->receive (buf, len);

			CBitMemStream msgin (true);
			msgin.clear ();
			memcpy (msgin.bufferToFill (len), &buf[0], len);

			msgin.serial (result);
			break;
		}

		// sleep
		nlSleep (1000);
	}

	if(!result.empty()) nlerror ("*** Connection to the shard failed '%s' ***", result.c_str());

	nlinfo ("*** Connection granted! You are connected on the frond end ***");

	while (cnx->connected ())
	{
		// do want you want!

		nlSleep(10);
	}


#endif // USE_UDP

	delete cnx;
}
