/** \file event_server.cpp
 * events server
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

#include "stdmisc.h"

#include "nel/misc/event_server.h"
#include "nel/misc/event_listener.h"
#include "nel/misc/event_emitter.h"
#include "nel/misc/events.h"


namespace NLMISC {


/*------------------------------------------------------------------*\
							CEventServer()
\*------------------------------------------------------------------*/
CEventServer::CEventServer()
{
	_Pumping= false;
}

CEventServer::~CEventServer()
{
	std::list<CEvent*>::iterator itev = _Events.begin();
	while(itev!=_Events.end())
	{
		delete *itev;
		itev=_Events.erase (itev);
	}
}
	

/*------------------------------------------------------------------*\
							postEvent()
\*------------------------------------------------------------------*/
void CEventServer::postEvent(CEvent * event)
{
	_Events.push_back(event);
}



/*------------------------------------------------------------------*\
							pump()
\*------------------------------------------------------------------*/
void CEventServer::pump(bool allWindows)
{
	// Avoid recurse (can arise if the process of an event decide to pump the server again....)
	nlassert(!_Pumping);
	_Pumping= true;
	
	// **** submit emitters events
	std::list<IEventEmitter*>::iterator item = _Emitters.begin();
	
	// getting events from emitters
	while(item!=_Emitters.end())
	{
		// ask emitters to submit their events to server
		(*item)->submitEvents(*this, allWindows);
		item++;
	}

	// **** process to listeners
	std::list<CEvent*>::iterator itev = _Events.begin();
	while(itev!=_Events.end())
	{
		// pump event
		bool bDelete=pumpEvent(*itev);
		if (bDelete)
			delete *itev;
		itev=_Events.erase (itev);
	}

	// end of pumping
	_Pumping= false;
}


/*------------------------------------------------------------------*\
							pumpEvent()
\*------------------------------------------------------------------*/
bool CEventServer::pumpEvent(CEvent* event)
{
	// taking id
	uint64 id = (uint64) *event;

	// looking for the first occurence of id
	mapListener::iterator it = _Listeners.find(id);

	// calling every callbacks
	while(it!=_Listeners.end() && (uint64)(*it).first == id)
	{
		IEventListener *a = (IEventListener *)((*it).second);
		a->process(*event);
		it++;
	}

	// delete the pointer
	return true;
}



/*------------------------------------------------------------------*\
							addListener()
\*------------------------------------------------------------------*/
void CEventServer::addListener(CClassId id, IEventListener* listener )
{
	_Listeners.insert( mapListener::value_type(id, listener));
}


/*------------------------------------------------------------------*\
							removeListener()
\*------------------------------------------------------------------*/
void CEventServer::removeListener(CClassId id, IEventListener* listener )
{
	// looking for the first occurence of id
	mapListener::iterator it = _Listeners.find(id);

	// looking for occurence with the right callback
	while(it!=_Listeners.end() && (*it).first == id)
	{
		if((*it).second==listener)
		{
			// erasing pair
			_Listeners.erase(it);
			return;
		}
		it++;
	}
}


/*------------------------------------------------------------------*\
							addEmitter()
\*------------------------------------------------------------------*/
void CEventServer::addEmitter(IEventEmitter * emitter)
{
	_Emitters.push_back(emitter);
}


/*------------------------------------------------------------------*\
							removeEmitter()
\*------------------------------------------------------------------*/
void CEventServer::removeEmitter(IEventEmitter * emitter)
{
	_Emitters.remove(emitter);
}


} // NLMISC
