/** \file login_client.cpp
 * CLoginClient is the interface used by the client to identifies itself to the login_sytem and
 * connects to the shard.
 *
 * $Id: login_client.cpp,v 1.20 2004/05/10 15:46:08 distrib Exp $
 *
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

#include "stdnet.h"

#include "nel/misc/system_info.h"

#include "nel/net/callback_client.h"

#include "nel/net/login_cookie.h"
#include "nel/net/login_client.h"

#include "nel/net/udp_sock.h"

using namespace std;
using namespace NLMISC;

namespace NLNET {


// Callback for answer of the request shard
bool ShardValidate;
string ShardValidateReason;
void cbShardValidate (CMessage &msgin, TSockId from, CCallbackNetBase &netbase)
{
	//
	// S14: receive "SV" message from FES
	//

	msgin.serial (ShardValidateReason);
	ShardValidate = true;
}

static TCallbackItem FESCallbackArray[] =
{
	{ "SV", cbShardValidate },
};

string CLoginClient::connectToShard (CLoginCookie &lc, const std::string &addr, CCallbackClient &cnx)
{
	nlassert (!cnx.connected());
	
	try
	{
		//
		// S12: connect to the FES and send "SV" message to the FES
		//
		cnx.connect (CInetAddress(addr));
		cnx.addCallbackArray (FESCallbackArray, sizeof(FESCallbackArray)/sizeof(FESCallbackArray[0]));

		// send the cookie
		CMessage msgout2 ("SV");
		msgout2.serial (lc);
		cnx.send (msgout2);

		// wait the answer of the connection
		ShardValidate = false;
		while (cnx.connected() && !ShardValidate)
		{
			cnx.update ();
			nlSleep(10);
		}
		
		// have we received the answer?
		if (!ShardValidate) return "FES disconnect me";
	}
	catch (ESocket &e)
	{
		return string("FES refused the connection (") + e.what () + ")";
	}

	return ShardValidateReason;
}

string CLoginClient::connectToShard (const std::string &addr, CUdpSock &cnx)
{
	nlassert (!cnx.connected());
	
	try
	{
		//
		// S12: connect to the FES. Note: In UDP mode, it's the user that have to send the cookie to the front end
		//
		// If a personal firewall such as ZoneAlarm is installed and permission not granted yet,
		// the connect blocks until the user makes a choice.
		// If the user denies the connection, the exception ESocket is thrown.
		// Other firewalls such as Kerio make the send() fail instead.
		//
		cnx.connect (CInetAddress(addr));
	}
	catch (ESocket &e)
	{
		return string("FES refused the connection (") + e.what () + ")";
	}

	return ShardValidateReason;
}

string CLoginClient::connectToShard (const std::string &addr, CUdpSimSock &cnx)
{
	nlassert (!cnx.connected());
	
	try
	{
		//
		// S12: connect to the FES. Note: In UDP mode, it's the user that have to send the cookie to the front end
		//
		// See firewall comment in connectToShard(string,CUdpSock)
		//
		cnx.connect (CInetAddress(addr));
	}
	catch (ESocket &e)
	{
		return string("FES refused the connection (") + e.what () + ")";
	}

	return ShardValidateReason;
}

} // NLNET
