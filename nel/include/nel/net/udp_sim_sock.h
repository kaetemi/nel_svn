/** \file udp_sim_sock.h
 * This class provides the same function as CUdpSock but can simulate
 * lag and other parameter like packet lost.
 */

/* Copyright, 2002 Nevrax Ltd.
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

#ifndef NL_UDP_SIM_SOCK_H
#define NL_UDP_SIM_SOCK_H

#include "nel/misc/config_file.h"
#include <queue>

#include "sock.h"
#include "udp_sock.h"


namespace NLNET {


struct CBufferizedOutPacket;

/**
 * CUdpSimSock: Unreliable datagram socket via UDP but packet lost, lag simulation.
 * See class CUdpSock.
 *
 * Notes: InLag must be >0 to use the InPacketLoss variable
 *
 * \author Vianney Lecroart
 * \author Nevrax France
 * \date 2002
 */
class CUdpSimSock
{
public:
	
	CUdpSimSock (bool logging = true) : UdpSock(logging) { }

	// this function is to call to set the simulation values
	static void			setSimValues (NLMISC::CConfigFile &cf);

	// CUdpSock functions wrapping
	void				connect( const CInetAddress& addr );
	void				close();
	bool				dataAvailable();
	bool				receive( uint8 *buffer, uint32& len, bool throw_exception=true );
	CSock::TSockResult	send( const uint8 *buffer, uint32& len, bool throw_exception=true );
	void				sendTo (const uint8 *buffer, uint32& len, const CInetAddress& addr);
	bool				connected();
	const CInetAddress&	localAddr() const {	return UdpSock.localAddr(); }

	// Used to call CUdpSock functions that are not wrapped in this class
	CUdpSock			UdpSock;

private:

	std::queue<CBufferizedOutPacket*> _BufferizedOutPackets;
	std::queue<CBufferizedOutPacket*> _BufferizedInPackets;

	static uint32	_InLag;
	static uint8	_InPacketLoss;

	static uint32	_OutLag;
	static uint8	_OutPacketLoss;
	static uint8	_OutPacketDuplication;
	static uint8	_OutPacketDisordering;

	void updateBufferizedPackets ();
	void sendUDP (const uint8 *buffer, uint32& len, const CInetAddress *addr = NULL);
	void sendUDPNow (const uint8 *buffer, uint32 len, const CInetAddress *addr = NULL);

	friend void cbSimVar (NLMISC::CConfigFile::CVar &var);
};


} // NLNET


#endif // NL_SIM_SOCK_H

/* End of udp_sim_sock.h */
