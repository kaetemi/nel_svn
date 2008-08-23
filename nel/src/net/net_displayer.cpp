/** \file net_displayer.cpp
 * CNetDisplayer class
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

#include "nel/net/net_displayer.h"
#include "nel/net/message.h"
#include "nel/net/naming_client.h"


using namespace std;
using namespace NLMISC;

namespace NLNET {


/* This index must correspond to the index for "LOG" in CallbackArray in the Logging Service
 * (see CNetDisplayer::display())
 */
const sint16 LOG_CBINDEX = 0;


/*
 * Constructor
 */
CNetDisplayer::CNetDisplayer(bool autoConnect) :
	_Server(NULL), _ServerAllocated (false) // disable logging otherwise an infinite recursion may occur
{
	if (autoConnect) findAndConnect();
}


/*
 * Find the server (using the NS) and connect
 */
void CNetDisplayer::findAndConnect()
{
	if (_Server == NULL)
	{
		_Server = new CCallbackClient();
		_ServerAllocated = true;
	}

	if ( CNamingClient::lookupAndConnect( "LOGS", *_Server ) )
	{
		nldebug( "Connected to logging service" );
	}
}

/*
 * Sets logging server address
 */
void CNetDisplayer::setLogServer (const CInetAddress& logServerAddr)
{
	if (_Server != NULL && _Server->connected()) return;

	_ServerAddr = logServerAddr;

	if (_Server == NULL)
	{
		_Server = new CCallbackClient();
		_ServerAllocated = true;
	}
	
	try
	{
		_Server->connect (_ServerAddr);
	}
	catch( ESocket& )
	{
		// Silence
	}
}

void CNetDisplayer::setLogServer (CCallbackClient *server)
{
	if (_Server != NULL && _Server->connected()) return;

	_Server = server;
}


/*
 * Destructor
 */
CNetDisplayer::~CNetDisplayer ()
{
	if (_ServerAllocated)
	{
		_Server->disconnect ();
		delete _Server;
	}
}


/*
 * Sends the string to the logging server
 *
 * Log format: "2000/01/15 12:05:30 <LogType> <ProcessName>: <Msg>"
 */
void CNetDisplayer::doDisplay ( const CLog::TDisplayInfo& args, const char *message)
{
	try
	{
		if (_Server == NULL || !_Server->connected())
		{
			return;
		}

		bool needSpace = false;
		//stringstream ss;
		string str;

		if (args.Date != 0)
		{
			str += dateToHumanString(args.Date);
			needSpace = true;
		}

		if (args.LogType != CLog::LOG_NO)
		{
			if (needSpace) { str += " "; needSpace = false; }
			str += logTypeToString(args.LogType);
			needSpace = true;
		}

		if (!args.ProcessName.empty())
		{
			if (needSpace) { str += " "; needSpace = false; }
			str += args.ProcessName;
			needSpace = true;
		}
		
		if (needSpace) { str += ": "; needSpace = false; }

		str += message;

		CMessage msg("LOG" );
		string s = str;
		msg.serial( s );
		_Server->send (msg, 0, false);
	}
	catch( NLMISC::Exception& )
	{
		// Silence
	}
}


} // NLNET
