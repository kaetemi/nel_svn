/** \file varpath.h
 * use to manage variable path (ie: [serv1,serv2].*.*.var)
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX NeL Network Services.
 * NEVRAX NeL Network Services is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NeL Network Services is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NeL Network Services; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef NL_VARPATH_H
#define NL_VARPATH_H

#include "nel/misc/types_nl.h"

class CVarPath
{
public:
	
	CVarPath (const std::string &raw) : RawVarPath(raw)
	{
		decode ();
	}

	void decode ();

	std::vector<std::pair<std::string, std::string> > Destination;

	void display ();

	/// returns true if there s no more . in the path
	bool isFinal ();

	bool empty ()
	{
		return Destination.empty();
	}

private:

	std::string getToken ();

	std::string RawVarPath;

	uint32 TokenPos;

};


#endif // NL_VARPATH_H

/* End of varpath.h */
