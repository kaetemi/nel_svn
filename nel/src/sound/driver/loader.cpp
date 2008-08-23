/** \file driver/loader.cpp
 * TODO: File description
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

#include "buffer.h"
#include "loader.h"
#include "nel/misc/debug.h"


namespace NLSOUND {


/*
 * Set the destination buffer
 */
void ILoader::setBuffer( IBuffer *buffer )
{
	nlassert( buffer!=NULL );
	_Buffer = buffer;
}


/**
 * Fill the buffer up to the specified size, calling fillMore() if the buffer
 * supports it, otherwise, fills the buffer entirely, calling IBuffer::fillBuffer()
 */
bool ILoader::fillBufferPart( uint32 size )
{
	nlassert( (_Buffer != NULL) && (size<=getSize()) );
	if ( _Buffer->isFillMoreSupported() )
	{
		nlassert( _Buffer->getSize() != 0 );
		return _Buffer->fillMore( provideData( size ), size );
	}
	else
	{
		return _Buffer->fillBuffer( provideData( size), size );
	}
}


/*
 * Fills the buffer entirely
 */
bool ILoader::fillBuffer()
{
	nlassert( _Buffer != NULL );
	uint32 size = getSize();
	return _Buffer->fillBuffer( provideData( size ), size );
}


} // NLSOUND
