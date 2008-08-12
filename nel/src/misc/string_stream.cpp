/** \file string_stream.cpp
 * Class CStringStream (plain text memory streams)
 *
 * $Id: string_stream.cpp,v 1.11 2005/08/19 15:30:04 cado Exp $
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

// DEPRECATED
#if 0

#include "nel/misc/string_stream.h"
#include "nel/misc/object_vector.h"

#include <vector>

namespace NLMISC {


//static const char SEPARATOR = ' ';
//static const int SEP_SIZE = 1; // the code is easier to read with that



/*
 * Input: read from the stream until the next separator, and return the number of bytes read. The separator is then skipped.
 */
uint CStringStream::serialSeparatedBufferIn( uint8 *buf, uint len )
{
	nlassert( isReading() );

	// Check that we don't read more than there is to read
	if ( ( _BufPos == _Buffer.end() ) || // we are at the end
		 ( lengthS()+len+SEP_SIZE > length() ) && (_Buffer[_Buffer.size()-1] != SEPARATOR ) ) // we are before the end // calls virtual length (cf. sub messages)
	{
		throw EStreamOverflow();
	}
	// Serialize in
	uint32 i = 0;
	while ( (i<len) && (*_BufPos) != SEPARATOR )
	{
		*(buf+i) = *_BufPos;
		i++;
		_BufPos++;
	}
	// Exceeds len
	if ( (*_BufPos) != SEPARATOR )
	{
		throw EStreamOverflow();
	}
	_BufPos += SEP_SIZE;
	return i;
}

/*
 * Output: writes len bytes from buf into the stream
 */
void CStringStream::serialSeparatedBufferOut( uint8 *buf, uint len )
{
	nlassert( ! isReading() );
	
	// Serialize out
	_Buffer.resize( _Buffer.size() + len + SEP_SIZE );
	_BufPos = _Buffer.end() - len - SEP_SIZE;
	memcpy( &(*_BufPos), buf, len );
	_Buffer[_Buffer.size()-1] = SEPARATOR;
	_BufPos = _Buffer.end();
}


// Input
#define readnumber(dest,thetype,digits,convfunc) \
	char number_as_cstring [digits+1]; \
	uint realdigits = serialSeparatedBufferIn( (uint8*)&number_as_cstring, digits ); \
	number_as_cstring[realdigits] = '\0'; \
	dest = (thetype)convfunc( number_as_cstring );

// Output
#define writenumber(src,format,digits) \
	char number_as_cstring [digits+1]; \
	sprintf( number_as_cstring, format, src ); \
	serialSeparatedBufferOut( (uint8*)&number_as_cstring, strlen(number_as_cstring) );

/// \todo cado: NLMISC::CStringStream: Use strtoul() functions instead of atoi(), to handle conversion errors

/*
 * atoihex
 */
inline int atoihex( const char* ident )
{
	int number;
	sscanf( ident, "%x", &number );
	return number;
}

inline uint32 atoui( const char *ident)
{
	return (uint32) strtoul (ident, NULL, 10);
}

// ======================================================================================================
void		CStringStream::serial(uint8 &b) 
{
	if ( isReading() )
	{
		readnumber( b, uint8, 3, atoi ); // 255
	}
	else
	{
		writenumber( (uint16)b,"%hu", 3 );
	}
}

// ======================================================================================================
void		CStringStream::serial(sint8 &b) 
{
	if ( isReading() )
	{
		readnumber( b, sint8, 4, atoi ); // -128
	}
	else
	{
		writenumber( (sint16)b, "%hd", 4 );
	}
}

// ======================================================================================================
void		CStringStream::serial(uint16 &b) 
{
	// No byte swapping in text mode
	if ( isReading() )
	{
		readnumber( b, uint16, 5, atoi ); // 65535
	}
	else
	{
		writenumber( b, "%hu", 5 );
	}
}

// ======================================================================================================
void		CStringStream::serial(sint16 &b) 
{
	if ( isReading() )
	{
		readnumber( b, sint16, 6, atoi ); // -32768
	}
	else
	{
		writenumber( b, "%hd", 6 );
	}
}

// ======================================================================================================
void		CStringStream::serial(uint32 &b) 
{
	if ( isReading() )
	{
		readnumber( b, uint32, 10, atoui ); // 4294967295
	}
	else
	{
		writenumber( b, "%u", 10 );
	}
}

// ======================================================================================================
void		CStringStream::serial(sint32 &b) 
{
	if ( isReading() )
	{
		readnumber( b, sint32, 11, atoi ); // -2147483648
	}
	else
	{
		writenumber( b, "%d", 11 );
	}
}

// ======================================================================================================
void		CStringStream::serial(uint64 &b) 
{
	if ( isReading() )
	{
		readnumber( b, uint64, 20, atoiInt64 ); // 18446744073709551615
	}
	else
	{
		writenumber( b, "%"NL_I64"u", 20 );
	}
}

// ======================================================================================================
void		CStringStream::serial(sint64 &b) 
{
	if ( isReading() )
	{
		readnumber( b, sint64, 20, atoiInt64 ); // -9223372036854775808
	}
	else
	{
		writenumber( b, "%"NL_I64"d", 20 );
	}
}

// ======================================================================================================
void		CStringStream::serial(float &b) 
{
	if ( isReading() )
	{
		readnumber( b, float, 128, atof ); // ?
	}
	else
	{
		writenumber( (double)b, "%f", 128 );
	}
}

// ======================================================================================================
	void		CStringStream::serial(double &b) 
{
	if ( isReading() )
	{
		readnumber( b, double, 128, atof ); //
	}
	else
	{
		writenumber( b, "%f", 128 );
	}
}

// ======================================================================================================
void		CStringStream::serial(bool &b) 
{
	serialBit(b);
}


// ======================================================================================================
void			CStringStream::serialBit(bool &bit)
{
	uint8 u;
	if ( isReading() )
	{
		serial( u );
		bit = (u!=0);
	}
	else
	{
		u = (uint8)bit;
		serial( u );
	}
}


#ifndef NL_OS_CYGWIN
// ======================================================================================================
void		CStringStream::serial(char &b) 
{
	char buff [2];
	if ( isReading() )
	{
		serialBuffer( (uint8*)buff, 2 );
		b = buff[0];
	}
	else
	{
		buff[0] = b;
		buff[1] = SEPARATOR;
		serialBuffer( (uint8*)buff, 2 );
	}

}
#endif

// ======================================================================================================
void		CStringStream::serial(std::string &b) 
{
	uint32	len=0;
	// Read/Write the length.
	if(isReading())
	{
		serial(len);
		if (len>1000000)
			throw NLMISC::EInvalidDataStream( "CStringStream: Trying to read a string of %u bytes", len );
		b.resize(len);
	}
	else
	{
		len= b.size();
		if (len>1000000)
			throw NLMISC::EInvalidDataStream( "CStringStream: Trying to write a string of %u bytes", len );
		serial(len);
	}
	
	// Read/Write the string.
	for(uint i=0;i!=len;++i)
		serialBuffer( (uint8*)&(b[i]), sizeof(b[i]) );

	char sep = SEPARATOR;
	serialBuffer( (uint8*)&sep, 1 );
}


// ======================================================================================================
void		CStringStream::serial(ucstring &b) 
{
	uint32	len=0;
	// Read/Write the length.
	if(isReading())
	{
		serial(len);
		if (len>1000000)
			throw NLMISC::EInvalidDataStream( "CStringStream: Trying to read an ucstring of %u bytes", len );
		b.resize(len);
	}
	else
	{
		len= b.size();
		if (len>1000000)
			throw NLMISC::EInvalidDataStream( "CStringStream: Trying to write an ucstring of %u bytes", len );
		serial(len);
	}
	// Read/Write the string.
	for(uint i=0;i!=len;++i)
		serialBuffer( (uint8*)&b[i], sizeof( sizeof(b[i]) ) );

	char sep = SEPARATOR;
	serialBuffer( (uint8*)&sep, 1 );
}


// Specialisation of serialCont() for vector<bool>
void	CStringStream::serialCont(std::vector<bool> &cont)
{
	uint32	len=0;
	if(isReading())
	{
		serial(len);
		// special version for vector: adjut good size.
		contReset(cont);
		cont.reserve(len);

		for(uint i=0;i!=len;++i)
		{
			bool	v;
			serial(v);
			cont.insert(cont.end(), v);
		}
	}
	else
	{
		len= cont.size();
		serial(len);

		std::vector<bool>::iterator it= cont.begin();
		for(uint i=0;i!=len;++i, ++it)
		{
			bool b = *it;
			serial( b );
		}
	}
}


/*
 * Serialisation in hexadecimal
 */
void	CStringStream::serialHex(uint32 &b)
{
	if ( isReading() )
	{
		readnumber( b, uint32, 10, atoihex ); // 4294967295
	}
	else
	{
		writenumber( b, "%x", 10 );
	}
}


} // NLMISC

#endif
