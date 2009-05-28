/** \file event_emitter_multi.cpp
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

#include "stdmisc.h"
#include "nel/misc/event_emitter_multi.h"


namespace NLMISC
{

// a predicate to find an emitter in a list
struct EmitterEqualPred
{
	EmitterEqualPred(IEventEmitter *e) : E(e) {}
	IEventEmitter *E;
	bool operator()(const std::pair<IEventEmitter *, bool> &el)
	{
		return el.first == E;
	}
};

///============================================================
CEventEmitterMulti::~CEventEmitterMulti()
{
	for (TEmitterCont::iterator it = _Emitters.begin(); it != _Emitters.end(); ++it)
	{
		if (it->second) // asked "must Delete' ?
		{
			delete it->first;
		}
	}
}

///============================================================
void	CEventEmitterMulti::addEmitter(IEventEmitter *e, bool mustDelete)
{
	nlassert(e != this); // avoid infinite recursion
	nlassert(!isEmitter(e));
	_Emitters.push_back(std::make_pair(e, mustDelete));
}

///============================================================
void	CEventEmitterMulti::removeEmitter(IEventEmitter *e)
{
	TEmitterCont::iterator it = std::find_if(_Emitters.begin(), _Emitters.end(), EmitterEqualPred(e));
	nlassert(it!= _Emitters.end());
	if (it->second)
	{
		delete it->first;
	}
	_Emitters.erase(it);
}

///============================================================
bool	CEventEmitterMulti::isEmitter(IEventEmitter *e) const
{
	TEmitterCont::const_iterator it = std::find_if(_Emitters.begin(), _Emitters.end(), EmitterEqualPred(e));
	return it != _Emitters.end();
}

///============================================================
void CEventEmitterMulti::submitEvents(CEventServer &server, bool allWindows)
{
	for (TEmitterCont::iterator it = _Emitters.begin(); it != _Emitters.end(); ++it)
	{
		it->first->submitEvents(server, allWindows);
	}
}
///============================================================
IEventEmitter *CEventEmitterMulti::getEmitter(uint index)
{
	nlassert(index < _Emitters.size());
	return _Emitters[index].first;
}

///============================================================
const IEventEmitter *CEventEmitterMulti::getEmitter(uint index) const
{
	nlassert(index < _Emitters.size());
	return _Emitters[index].first;
}




} // NLMISC
