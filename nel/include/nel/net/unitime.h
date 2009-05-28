/** \file unitime.h
 * Manage universal time (synchronized with a centralized time manager)
 * THIS CLASS IS DEPRECATED, DON'T USE IT
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

#ifndef NL_UNITIME_H
#define NL_UNITIME_H

#include "nel/misc/types_nl.h"
#include "nel/misc/time_nl.h"
#include "nel/misc/debug.h"
#include "callback_net_base.h"

namespace NLNET
{

class CInetAddress;
class CCallbackServer;
class CCallbackClient;

/**
 * This class provide a independant universal time system.
 * \author Vianney Lecroart
 * \author Nevrax France
 * \date 2000
 *
 * THIS CLASS IS DEPRECATED, DON'T USE IT
 *
 */
class _CUniTime : public NLMISC::CTime
{
public:

	/// Return the time in millisecond. This time is the same on all computers at the \b same moment.
	static NLMISC::TTime	getUniTime ();

	/// Return the time in a string format to be display
	static const char		*getStringUniTime ();

	/// Return the time in a string format to be display
	static const char		*getStringUniTime (NLMISC::TTime ut);


	/** You need to call this function before calling getUniTime or an assert will occured.
	 * This function will connect to the time service and synchronize your computer.
	 * This function assumes that all services run on server that are time synchronized with NTP for example.
	 * If addr is NULL, the function will connect to the Time Service via the Naming Service. In this case,
	 * the CNamingClient must be connected to a Naming Service.
	 * This function can be called *ONLY* by services that are inside of the shard.
	 * Don't use it for a client or a service outside of the shard.
	 */
	static void				syncUniTimeFromService (CCallbackNetBase::TRecordingState rec=CCallbackNetBase::Off, const CInetAddress *addr = NULL);

	/** Call this function in the init part of the front end service to enable time syncro between
	 * shard and clients.
	 */
	static void				installServer (CCallbackServer *server);

	/** Call this functions in the init part of the client side to synchronize between client and shard.
	 * client is the connection between the client and the front end. The connection must be established before
	 * calling this function.
	 */
	static void				syncUniTimeFromServer (CCallbackClient *client);

	/** \internal used by the time service to set the universal time the first time
	  */
	static void				setUniTime (NLMISC::TTime uTime, NLMISC::TTime lTime);
	/** \internal
	  */
	static void				setUniTime (NLMISC::TTime uTime);

	/**
	 * Call this method before to prevent syncUniTimeFromService() from real synchronization:
	 * syncUniTimeFromService() will still communicate with the time service, as usual,
	 * but the local time will not be synchronized.
	 */
	static void				simulate() { nlstop; _Simulate = true; }

	static bool				Sync;				// true if the synchronization occured
private:

	static NLMISC::TTime	_SyncUniTime;		// time in millisecond when the universal time received
	static NLMISC::TTime	_SyncLocalTime;		// time in millisecond when the syncro with universal time occured

	// If true, do not synchronize
	static bool				_Simulate;
};

} // NLNET

#endif // NL_UNITIME_H

/* End of unitime.h */
