/** \file dummy_tcp_sock.h
 * Dummy TCP socket, used by the message recorder for playback
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

#ifndef NL_DUMMY_TCP_SOCK_H
#define NL_DUMMY_TCP_SOCK_H

#include "nel/misc/types_nl.h"
#include "tcp_sock.h"


namespace NLNET {


/**
 * Dummy CTcpSock replacement for replay mode
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class CDummyTcpSock : public CTcpSock
{
public:

	// Constructor
	CDummyTcpSock( bool logging = true ) : CTcpSock(logging) {}

	// Dummy connection
	virtual void			connect( const CInetAddress& addr );

	// Dummy disconnection
	virtual void			disconnect();

	// Nothing
	virtual void			setNoDelay( bool /* value */ ) {}

	// Nothing
	virtual void			close() {}

};


} // NLNET


#endif // NL_DUMMY_TCP_SOCK_H

/* End of dummy_tcp_sock.h */
