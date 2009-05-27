/** \file net_layer4/client.cpp
 * Layer4 example
 *
 * $Id: client.cpp,v 1.2 2004/05/07 12:56:21 cado Exp $
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
 * Layer 4 example, client.
 *
 * This client connects to a front-end server at localhost:37000.
 * It sends pings and expects pongs (ping replies).
 */


// We're using NeL
#include "nel/misc/types_nl.h"
#include "nel/misc/debug.h"
using namespace NLMISC;

// We're using the layer 4
#include "nel/net/net_manager.h"
using namespace NLNET;


// Name of the front-end service
const char SVC [3] = "FS";


/*
 * Callback function called when receiving a "PONG" message
 *
 * Arguments:
 * - msgin:	the incoming message
 * - from: the "sockid" of the sender (usually useless for a CCallbackClient)
 * - client: the CCallbackNetBase object (which really is a CCallbackClient object, for a client)
 *
 * Input (expected message): PONG
 * - uint32: ping counter
 *
 * Output (sent message): PING
 * - uint32: new ping counter
 */
void cbPong( CMessage& msgin, TSockId from, CCallbackNetBase& client )
{
	uint32 counter;

	// Input
	msgin.serial( counter );
	nlinfo( "Received PONG number %u", counter );

	counter++;

	// Output
	CMessage msgout ( "PING" );
	msgout.serial( counter );
	CNetManager::send( SVC, msgout );
	nlinfo( "Sent PING number %u", counter );
}


/*
 * Callback array
 */
TCallbackItem CallbackArray[] =
{
	{ "PONG", cbPong }	// when receiving a "PONG" message, call cbPong()
};


/*
 * main
 */
void main( int argc, char **argv )
{
	try
	{
		// Initialize (we don't call CNetManager::init() because we don't use the naming service)

		// Connect to the front-end server at localhost:37000
		CNetManager::addClient( SVC, "localhost:37000" );
		CNetManager::addCallbackArray( SVC, CallbackArray, sizeof(CallbackArray)/sizeof(CallbackArray[0]) );

		// Send a PING message
		uint32 counter = 0;
		CMessage msg( "PING" );	// create the message
		msg.serial( counter );						// serialize the counter into the message
		CNetManager::send( SVC, msg );							// put into the send queue
		nlinfo( "Sent PING number %u", counter );

		// Main loop
		while ( CNetManager::getNetBase( SVC )->connected() )
		{
			// Perform sends and receives, call callbacks
			CNetManager::update();
		}

		nlinfo( "Disconnected" );

		// We don't call CNetManager::release() because we didn't call CNetManager::init()
	}
	catch ( Exception &e )
	{
		nlerror( "Error: %s", e.what() );
	}
}
