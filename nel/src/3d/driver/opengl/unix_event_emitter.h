/** \file unix_event_emitter.h
 * TODO: File description
 *
 * $Id: unix_event_emitter.h,v 1.5 2004/11/15 10:24:56 lecroart Exp $
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

#ifndef NL_UNIX_EVENT_EMITTER_H
#define NL_UNIX_EVENT_EMITTER_H

#include "nel/misc/types_nl.h"
#include "nel/misc/event_emitter.h"

#ifdef NL_OS_UNIX


#include <GL/gl.h>
#include <GL/glx.h>

namespace NLMISC {


/**
 * TODO Class description
 * \author Vianney Lecroart
 * \author Nevrax France
 * \date 2000
 */
class CUnixEventEmitter : public IEventEmitter
{
public:

  /// Constructor
  CUnixEventEmitter();

  void init (Display *dpy, Window win);

	/** 
	 * sends all events to server
	 * (should call CEventServer method postEvent() ) 
	 * \param server
	 */	
	virtual void submitEvents(CEventServer & server, bool allWindows);

public:
	void processMessage (XEvent &event, CEventServer &server);

 private:
	Display *_dpy;
	Window   _win;
};


} // NLMISC

#endif // NL_OS_UNIX

#endif // NL_UNIX_EVENT_EMITTER_H

/* End of unix_event_emitter.h */
