/** \file event_emitter.h
 * class CEventEmitter
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

#ifndef NL_EVENT_EMITTER_H
#define NL_EVENT_EMITTER_H

#include "types_nl.h"
#include "event_server.h"
#include "smart_ptr.h"



namespace NLMISC {

/*===================================================================*/

class CEventServer;

/**
 * CEventEmitter
 * Send events to the event server
 *
 */
/* *** IMPORTANT ********************
 * *** IF YOU MODIFY THE STRUCTURE OF THIS CLASS, PLEASE INCREMENT IDriver::InterfaceVersion TO INVALIDATE OLD DRIVER DLL
 * **********************************
 */
class IEventEmitter	: public NLMISC::CRefCount
{
public:
	/// dtor
	virtual ~IEventEmitter() {}
	/** 
	 * sends all events to server
	 * (should call CEventServer method postEvent() ) 
	 * \param server
	 */	
	virtual void submitEvents(CEventServer & server, bool allWindows) = 0;
		
};


} // NLMISC


#endif // NL_EVENT_EMITTER_H

/* End of event_emitter.h */
