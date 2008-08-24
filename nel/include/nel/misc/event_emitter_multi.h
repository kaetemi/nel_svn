/** \file event_emitter_multi.h
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

#ifndef NL_EVENT_EMITTER_MULTI_H
#define NL_EVENT_EMITTER_MULTI_H

#include "types_nl.h"
#include "event_emitter.h"
#include <vector>


namespace NLMISC {


/** The composite pattern applied to events emmitters.
 * This is useful when you don't have the opportunity to register more than
 * one event emitter to an event server.
 */
class CEventEmitterMulti : public IEventEmitter
{
public:
	/// dtor
	~CEventEmitterMulti();
	/// add an emitter
	void	addEmitter(IEventEmitter *e, bool mustDelete);
	/// remove an emitter (and delete it if necessary)
	void	removeEmitter(IEventEmitter *e);
	/// test wether e is in the emitter list
	bool	isEmitter(IEventEmitter *e) const;
	// Get the number of registered emitters
	uint	getNumEmitters() const { return _Emitters.size(); }
	// Get an emitter
	IEventEmitter *getEmitter(uint index);
	const IEventEmitter *getEmitter(uint index) const;
	/// From IEventEmitter. This call submitEvents on all the emitters
	virtual void submitEvents(CEventServer &server, bool allWindows);
private:
	typedef std::vector<std::pair<IEventEmitter *, bool> > TEmitterCont;
	TEmitterCont	_Emitters;
};


} // NLMISC


#endif // NL_EVENT_EMITTER_MULTI_H

/* End of event_emitter_multi.h */
