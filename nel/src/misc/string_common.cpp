/** \file string_common.cpp
 *
 */

/* Copyright, 2003 Nevrax Ltd.
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

#include "nel/misc/string_common.h"

using namespace std;

namespace NLMISC
{

string addSlashR (string str)
{
	string formatedStr;
	// replace \n with \r\n
	for (uint i = 0; i < str.size(); i++)
	{
		if (str[i] == '\n' && i > 0 && str[i-1] != '\r')
		{
			formatedStr += '\r';
		}
		formatedStr += str[i];
	}
	return formatedStr;
}

string removeSlashR (string str)
{
	string formatedStr;
	// replace \n with \r\n
	for (uint i = 0; i < str.size(); i++)
	{
		if (str[i] != '\r')
			formatedStr += str[i];
	}
	return formatedStr;
}

}
