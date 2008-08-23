/** \file module_socket.h
 * module socket interface
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


#ifndef NL_FILE_MODULE_SOCKET_H
#define NL_FILE_MODULE_SOCKET_H

#include "nel/net/message.h"
#include "module_common.h"

namespace NLNET
{
	class IModuleSocket
	{
	public:
		virtual ~IModuleSocket() {}
		/** Register the socket in the module manager socket registry
		 */
		virtual void registerSocket() =0;
		/** Unregister the socket in the module manager socket registry
		 */
		virtual void unregisterSocket() =0;

		/** Ask derived class to obtain the socket name.
		 */
		virtual const std::string &getSocketName() =0;

		/** A plugged module send a message to another module.
		 *	If the destination module is not accessible through this socket,
		 *	an exception is thrown.
		 */
		virtual void sendModuleMessage(IModule *senderModule, TModuleId destModuleProxyId, const NLNET::CMessage &message ) 
			throw (EModuleNotPluggedHere)
			=0;
		/** A plugged module send a message to all the module reachable
		 *	with this socket.
		 */
		virtual void broadcastModuleMessage(IModule *senderModule, const NLNET::CMessage &message)
			throw (EModuleNotPluggedHere)
			=0;

		/** Fill the resultList with the list of module that are
		 *	reachable with this socket.
		 *	Note that the result vector is not cleared before filling.
		 */
		virtual void getModuleList(std::vector<IModuleProxy*> &resultList) =0;

		//@name Callback for socket implementation
		//@{
		/// Called just after a module is plugged in the socket.
		virtual void onModulePlugged(IModule *pluggedModule) =0;
		/// Called just before a module is unplugged from the socket.
		virtual void onModuleUnplugged(IModule *unpluggedModule) =0;
		//@}
	};

//	const TModuleSocketPtr	NullModuleSocket;


	/** A base class for socket.
	 *	It provide plugged module management to
	 *	implementors.
	 */
	class CModuleSocket : public IModuleSocket
	{
	protected:
		typedef NLMISC::CTwinMap<TModuleId, TModulePtr>	TPluggedModules;
		/// The list of plugged modules
		TPluggedModules			_PluggedModules;

		bool					_SocketRegistered;

		friend class CModuleBase;

		CModuleSocket();
		~CModuleSocket();

		virtual void registerSocket();
		virtual void unregisterSocket();


		virtual void _onModulePlugged(const TModulePtr &pluggedModule);
		virtual void _onModuleUnplugged(const TModulePtr &pluggedModule);

		virtual void _sendModuleMessage(IModule *senderModule, TModuleId destModuleProxyId, const NLNET::CMessage &message )
			throw (EModuleNotPluggedHere, NLNET::EModuleNotReachable)
			=0;

		virtual void _broadcastModuleMessage(IModule *senderModule, const NLNET::CMessage &message)
			throw (EModuleNotPluggedHere)
			=0;
	
		virtual void sendModuleMessage(IModule *senderModule, TModuleId destModuleProxyId, const NLNET::CMessage &message ) 
			throw (EModuleNotPluggedHere);
		/** A plugged module send a message to all the module reachable
		 *	with this socket.
		 */
		virtual void broadcastModuleMessage(IModule *senderModule, const NLNET::CMessage &message)
			throw (EModuleNotPluggedHere);

	};


} // namespace NLNET

#endif // NL_FILE_MODULE_SOCKET_H
