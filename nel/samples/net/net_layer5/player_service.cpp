/** \file net_layer5/player_service.cpp
 * Layer 5 and IService example
 *
 * $Id: player_service.cpp,v 1.1 2002/04/17 08:08:32 lecroart Exp $
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
 * Layer 4 and Service example, ping server.
 *
 * This ping service expects pings, sends pongs back.
 *
 * To run this program, ensure there is a file "ping_service.cfg"
 * containing the location of the naming service (NSHost, NSPort)
 * in the working directory. The naming service must be running.
 */


// We're using the NeL Service framework, and layer 5
#include "nel/net/service.h"
#include "nel/misc/time_nl.h"
#include "nel/misc/displayer.h"

using namespace std;
using namespace NLNET;
using namespace NLMISC;


CFileDisplayer fd("pls.log");
bool PingServiceUp = false;

//
TTime pingDate;

void cbPong(CMessage &msgin, const std::string &serviceName, TServiceId sid)
{
	nlassert (PingServiceUp);
	uint32	counter;
	msgin.serial( counter );
	TTime	pingTime = CTime::getLocalTime()-pingDate;

	nlinfo("Received PONG %u (%u ms)", counter, pingTime);
}

void sendPing()
{
	nlassert (PingServiceUp);
	pingDate = CTime::getLocalTime();
	uint32 counter = 0;
	CMessage msgout("PING");
	msgout.serial( counter );
	nlinfo( "Send PING 0");
	CUnifiedNetwork::getInstance()->send("PS", msgout);
}

//
void cbPos(CMessage &msgin, const std::string &serviceName, TServiceId sid)
{
	CMessage msgout("POS");
	CUnifiedNetwork::getInstance()->send("GPMS", msgout);

	nlinfo( "Received POS from %s, send POS to GPMS", serviceName.c_str());
}

void cbAckPos(CMessage &msgin, const std::string &serviceName, TServiceId sid)
{
	nlinfo( "Received ACK_POS from %s", serviceName.c_str());
}

//
void cbUpPS(const std::string &serviceName, TServiceId sid, void *arg)
{
	nlinfo("Ping Service connecting");
	PingServiceUp = true;
	sendPing();
}

void cbDownPS(const std::string &serviceName, TServiceId sid, void *arg)
{
	nlinfo("Ping Service disconnecting");
}

//
void cbUpService(const std::string &serviceName, TServiceId sid, void *arg)
{
	nlinfo("Service %s %d is up", serviceName.c_str(), sid.get());
}

void cbDownService(const std::string &serviceName, TServiceId sid, void *arg)
{
	nlinfo("Service %s %d is down", serviceName.c_str(), sid.get());
}


/*
 * Callback array for messages received from a client
 */
TUnifiedCallbackItem CallbackArray[] =
{
	{ "PONG", cbPong },
	{ "POS", cbPos },
	{ "ACK_POS", cbAckPos }
};


//
class CPlayerService : public IService
{
public:

	bool	update()
	{
		static TTime	lastPing = CTime::getLocalTime();

		TTime	ctime = CTime::getLocalTime();

		// check ping every 15 seconds
		if (ctime - lastPing > 15000)
		{
			if (PingServiceUp)
				sendPing();
			lastPing = ctime;
		}

		return true;
	}
	/*
	 * Initialization
	 */
	void init()
	{
		DebugLog->addDisplayer (&fd);
		InfoLog->addDisplayer (&fd);
		WarningLog->addDisplayer (&fd);
		ErrorLog->addDisplayer (&fd);

		// Connect to the ping service
		CUnifiedNetwork	*instance = CUnifiedNetwork::getInstance();

		instance->setServiceUpCallback("PS", cbUpPS, NULL);
		instance->setServiceDownCallback("PS", cbDownPS, NULL);

		instance->setServiceUpCallback("*", cbUpService, NULL);
		instance->setServiceDownCallback("*", cbDownService, NULL);
	}
};


/*
 * Declare a service with the class IService, the names "PS" (short) and "ping_service" (long).
 * The port is automatically allocated (0) and the main callback array is CallbackArray.
 */
NLNET_SERVICE_MAIN( CPlayerService, "PLS", "player_service", 0, CallbackArray, "", "" )
