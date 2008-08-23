/** \file driver/loader.h
 * ILoader: sound loader interface
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

#ifndef NL_LOADER_H
#define NL_LOADER_H

#include "nel/misc/types_nl.h"


namespace NLSOUND {


class IBuffer;


/**
 * Sound loader interface
 * \deprecated
 *
 * In order to fill a static buffer, just call fillBuffer().
 * In order to stream into a buffer, call fillBufferPart() several times.
 *
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class ILoader
{
public:

	/// Set the destination buffer
	virtual void		setBuffer( IBuffer *buffer );

	/// Return the size of the data to load (or MAXINT32 if unknown)
	virtual uint32		getSize() = 0;

	/**
	 * Fill the buffer up to the specified size, calling fillMore() if the buffer
	 * supports it, otherwise, fills the buffer entirely, calling IBuffer::fillBuffer()
	 */
	bool				fillBufferPart( uint32 size );

	/// Fills the buffer entirely
	bool				fillBuffer();

	/// Constructor
	ILoader() : _Buffer(NULL) {}

	/// Destructor
	virtual				~ILoader() { _Buffer = NULL; }

protected:

	/// Provide data (load)
	virtual void		*provideData( uint32 size ) = 0;


	// Destination buffer
	IBuffer		*_Buffer;
};


} // NLSOUND


#endif // NL_LOADER_H

/* End of loader.h */
