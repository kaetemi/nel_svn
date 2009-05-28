/** \file sha1.h
 *
 *      This is the header file for code which implements the Secure
 *      Hashing Algorithm 1 as defined in FIPS PUB 180-1 published
 *      April 17, 1995.
 *
 *      Many of the variable names in this code, especially the
 *      single character names, were used because those were the names
 *      used in the publication.
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

#ifndef NL_SHA1_H
#define NL_SHA1_H

#include <string>

#include "common.h"
#include "stream.h"

struct CHashKey
{
	CHashKey () { HashKeyString.resize(20); }

	CHashKey (const unsigned char Message_Digest[20])
	{
		HashKeyString = "";
		for(sint i = 0; i < 20 ; ++i)
		{
			HashKeyString += Message_Digest[i];
		}
	}

	// Init the hash key with a binary key format or a text key format
	CHashKey (const std::string &str)
	{
		if (str.size() == 20)
		{
			HashKeyString = str;
		}
		else if (str.size() == 40)
		{
			HashKeyString = "";
			for(uint i = 0; i < str.size(); i+=2)
			{
				uint8 val;
				if (isdigit((unsigned char)str[i+0]))
					val = str[i+0]-'0';
				else
					val = 10+tolower(str[i+0])-'a';
				val *= 16;
				if (isdigit((unsigned char)str[i+1]))
					val += str[i+1]-'0';
				else
					val += 10+tolower(str[i+1])-'a';

				HashKeyString += val;
			}
		}
		else
		{
			nlwarning ("SHA: Bad hash key format");
		}
	}

	// return the hash key in text format
	std::string toString() const
	{
		std::string str;
		for (uint i = 0; i < HashKeyString.size(); i++)
		{
			str += NLMISC::toString("%02X", (uint8)(HashKeyString[i]));
		}
		return str;
	}

	// serial the hash key in binary format
	void serial (NLMISC::IStream &stream)
	{
		stream.serial (HashKeyString);
	}

	bool	operator==(const CHashKey &v) const
	{
		return HashKeyString == v.HashKeyString;
	}

	// this string is always 20 bytes long and is the code in binary format (can't print it directly)
	std::string HashKeyString;
};

inline bool operator <(const struct CHashKey &a,const struct CHashKey &b)
{
	return a.HashKeyString<b.HashKeyString;
}

// This function get a filename (it works with big files) and returns his SHA hash key
// when forcePath is true, it doesn't use NLMISC::lookup
CHashKey getSHA1(const std::string &filename, bool forcePath = false);

// This function get a buffer with size and returns his SHA hash key
CHashKey getSHA1(const uint8 *buffer, uint32 size);

#endif // NL_SHA1_H
