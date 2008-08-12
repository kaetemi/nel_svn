/** \file net_displayer.h
 * Implementation of the CDisplayer (look at displayer.h) that display on a network connection
 *
 * $Id: net_displayer.h,v 1.19 2005/02/22 10:14:13 besson Exp $
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

#ifndef NL_NET_DISPLAYER_H
#define NL_NET_DISPLAYER_H

#include "nel/misc/log.h"
#include "nel/misc/displayer.h"

#include "callback_client.h"

namespace NLNET {


/**
 * Net Displayer. Sends the strings to a logger server (LOGS).
 * \ref log_howto
 * \bug When nlerror is called in a catch block, a connected NetDisplayer becomes an IDisplayer => pure virtual call
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2000
 */
class CNetDisplayer : public NLMISC::IDisplayer
{
public:

	/// Constructor
	CNetDisplayer(bool autoConnect = true);

	/** Sets logging server address. Call this method from outside only if you want to use a LOGS not registered within the NS.
	 * It does nothing if the displayer is already connected to a server.
	 */
	void setLogServer( const CInetAddress& logServerAddr );

	/** Sets logging server with an already connected server.
	 */
	void setLogServer( CCallbackClient *server );

	/// Returns true if the displayer is connected to a Logging Service.
	bool connected () { return _Server->connected(); }

	/// Destructor
	virtual ~CNetDisplayer();
		
protected:

	/** Sends the string to the logging server
	 * \warning If not connected, tries to connect to the logging server each call. It can slow down your program a lot.
	 */
	virtual void doDisplay ( const NLMISC::CLog::TDisplayInfo& args, const char *message);

	 /// Find the server (using the NS) and connect
	void findAndConnect();

private:

	CInetAddress	_ServerAddr;
//	CCallbackClient	_Server;
	CCallbackClient	*_Server;
	bool			_ServerAllocated;
//	uint32			_ServerNumber;
};


} // NLNET


#endif // NL_NET_DISPLAYER_H

/* End of net_displayer.h */
