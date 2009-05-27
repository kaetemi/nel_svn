/** \file simlag.h
 * This file create manage the UDP connection and lag/packet lost simulation
 *
 * $Id: simlag.h,v 1.1 2002/04/17 08:08:32 lecroart Exp $
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

#ifndef NL_SIMLAG_H
#define NL_SIMLAG_H

//
// Includes
//

#include <nel/misc/types_nl.h>

#include <nel/net/inet_address.h>
#include <nel/net/udp_sock.h>

//
// Variables
//

//
// Functions
//

// Call this function evenly to flush messages that are laged
void updateBufferizedPackets ();

// Set the packet lost and lag values for the simluation
void setSimlagValues (sint32 lag, sint8 packetLoss, sint8 packetDuplication, sint8 packetDisordering);

// Send a message using UDP connection with sim lag
void sendUDP (NLNET::CUdpSock *client, const uint8 *packet, uint32 packetSize, const NLNET::CInetAddress *addr = NULL);


#endif // NL_SIMLAG_H

/* End of simlag.h */
