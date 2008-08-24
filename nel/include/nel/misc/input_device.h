/** \file input_device.h
 * TODO: File description
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

#ifndef NL_INPUT_DEVICE_H
#define NL_INPUT_DEVICE_H

#include "types_nl.h"


namespace NLMISC
{


class  CEventServer;
class  CInputDeviceServer;
struct IInputDeviceEvent;


/**
 * Base class that wrap to a device
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2002
 */

struct IInputDevice
{
	/** Set the buffer size for this device (the number of samples it can retains).
	  * This return true if the size could be set
	  */
	virtual bool setBufferSize(uint size) = 0;
	/// Get the buffer size for this device
	virtual uint getBufferSize() const = 0;

	///\name Device server specifics. You usually don't want to call these
	//@{
		/** For device server usage :
		  * Called at the beginning of each events retrieval.
		  * If a device doesn't support buffered datas, the state changes can be directly send to the event server.
		  * The default does nothing.
		  */
		virtual void begin(CEventServer *server) {}

		/**	For device server usage :
		  * Poll all events from that device, and notify them to the given device server, so that they can be sorted between devices.
		  * This retrieves messages, but do not process them.
		  */
		virtual void poll(CInputDeviceServer *dev) = 0;
		/** For device server usage :
		  * Process an event (eventually update this device state), and translate the message to a IEventServerMessage
		  */
		virtual void submit(IInputDeviceEvent *deviceEvent, CEventServer *server) = 0;
		/** For device server usage :
		  * Says that the next message is for another device, or that it is the last message that will be received.
		  * This allow to pack several messages in one (for example, to sum up mouse moves until a click occurs)
		  * The default does nothing.
		  * The next message can be used to get a time stamp for example. It may be NULL is no next message is available
		  */
		virtual void transitionOccured(CEventServer *server, const IInputDeviceEvent *nextMessage) {}
	//@}

	// dtor
	virtual ~IInputDevice() {};
};

} // NLMISC


#endif // NL_INPUT_DEVICE_H

/* End of input_device.h */
