/** \file module_socket.cpp
 * module socket implementation
 */

/* Copyright, 2001 Nevrax Ltd.
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
#include "nel/net/module_socket.h"
#include "nel/net/module.h"
#include "nel/net/module_manager.h"
#include "nel/net/module_gateway.h"
#include "nel/net/module_common.h"

using namespace std;
using namespace NLMISC;

namespace NLNET
{

	CModuleSocket::CModuleSocket()
		: _SocketRegistered(false)
	{
	}

	CModuleSocket::~CModuleSocket()
	{
		unregisterSocket();
	}


	void CModuleSocket::registerSocket()
	{
		if (!_SocketRegistered)
		{
			_SocketRegistered = true;
			IModuleManager::getInstance().registerModuleSocket(this);
		}
	}

	void CModuleSocket::unregisterSocket()
	{
		if (_SocketRegistered)
		{
			IModuleManager::getInstance().unregisterModuleSocket(this);
			_SocketRegistered = false;
		}
	}

	void CModuleSocket::_onModulePlugged(const TModulePtr &pluggedModule)
	{
		TPluggedModules::TBToAMap::const_iterator it(_PluggedModules.getBToAMap().find(pluggedModule));
		if (it != _PluggedModules.getBToAMap().end())
		{
			throw IModule::EModuleAlreadyPluggedHere();
		}

		_PluggedModules.add(pluggedModule->getModuleId(), pluggedModule);

		// callback socket implementation
		onModulePlugged(pluggedModule);
	}

	void CModuleSocket::_onModuleUnplugged(const TModulePtr &pluggedModule)
	{
		TPluggedModules::TBToAMap::const_iterator it(_PluggedModules.getBToAMap().find(pluggedModule));
		if (it == _PluggedModules.getBToAMap().end())
		{
			throw EModuleNotPluggedHere();
		}

		// callback socket implementation
		onModuleUnplugged(pluggedModule);

		_PluggedModules.removeWithB(pluggedModule);
	}

	void CModuleSocket::sendModuleMessage(IModule *senderModule, TModuleId destModuleProxyId, const NLNET::CMessage &message )
			throw (EModuleNotPluggedHere)
	{
		TPluggedModules::TBToAMap::const_iterator it(_PluggedModules.getBToAMap().find(senderModule));
		if (it == _PluggedModules.getBToAMap().end())
		{
			throw EModuleNotPluggedHere();
		}

		// forward to socket implementation
		_sendModuleMessage(senderModule, destModuleProxyId, message);

	}

	void CModuleSocket::broadcastModuleMessage(IModule *senderModule, const NLNET::CMessage &message)
			throw (EModuleNotPluggedHere)
	{
		TPluggedModules::TBToAMap::const_iterator it(_PluggedModules.getBToAMap().find(senderModule));
		if (it == _PluggedModules.getBToAMap().end())
		{
			throw EModuleNotPluggedHere();
		}

		// forward to socket implementation
		_broadcastModuleMessage(senderModule, message);
	}

} // namespace NLNET
