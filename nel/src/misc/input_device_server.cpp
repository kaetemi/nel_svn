/** \file input_device_server.cpp
 * TODO: File description
 *
 * $Id: input_device_server.cpp,v 1.3 2004/11/15 10:25:04 lecroart Exp $
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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
#include "nel/misc/input_device_server.h"
#include "nel/misc/input_device.h"



namespace NLMISC 
{
//=======================================================================
void	CInputDeviceServer::registerDevice(IInputDevice *device)
{
	nlassert(!isDevice(device));
	_Devices.push_back(device);
}

//=======================================================================
void	CInputDeviceServer::removeDevice(IInputDevice *device)
{
	TDeviceCont::iterator it = std::find(_Devices.begin(), _Devices.end(), device);
	nlassert(it != _Devices.end());
	_Devices.erase(it);
}

//=======================================================================
bool	CInputDeviceServer::isDevice(IInputDevice *device) const
{
	TDeviceCont::const_iterator it = std::find(_Devices.begin(), _Devices.end(), device);
	return it != _Devices.end();
}

//=======================================================================
// Predicate to compare vents dates
struct CInputDeviceEventLess
{
	bool operator()(const IInputDeviceEvent *lhs, const IInputDeviceEvent *rhs) const
	{
		return *lhs < *rhs;
	}
};

//=======================================================================
void	CInputDeviceServer::poll(CEventServer *server)
{
	nlassert(_Events.empty());
	TDeviceCont::iterator deviceIt;
	for (deviceIt = _Devices.begin(); deviceIt != _Devices.end(); ++deviceIt)
	{
		(*deviceIt)->begin(server);
		(*deviceIt)->poll(this);
	}			
	// Sort the messages to get the right dates.
	std::sort(_Events.begin(), _Events.end(), CInputDeviceEventLess());
	// submit the result to the server
	IInputDevice *lastVisitedDevice = NULL;
	TEventCont::iterator eventIt;
	for (eventIt = _Events.begin(); eventIt != _Events.end(); ++eventIt)
	{
		// see if this message is from a previous device then the last we visited.
		if (lastVisitedDevice && (*eventIt)->Emitter != lastVisitedDevice)
		{
			// yes, tells that a transition occured
			lastVisitedDevice->transitionOccured(server, *eventIt);
			lastVisitedDevice = (*eventIt)->Emitter;
		}
		nlassert((*eventIt)->Emitter != NULL);
		(*eventIt)->Emitter->submit(*eventIt, server);
	}
	//
	for (deviceIt = _Devices.begin(); deviceIt != _Devices.end(); ++deviceIt)
	{
		(*deviceIt)->transitionOccured(server, NULL);
	}
	// delete the messages
	for (eventIt = _Events.begin(); eventIt != _Events.end(); ++eventIt)
	{
		delete *eventIt;		
	}
	//
	_Events.clear();
}

//=======================================================================
void	CInputDeviceServer::submitEvent(IInputDeviceEvent *deviceEvent)
{
	_Events.push_back(deviceEvent);
}


} // NLMISC
