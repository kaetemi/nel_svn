/** \file primitive_configuration.h
 * Ligo primitive configuration description.
 */

/* Copyright, 2000, 2001 Nevrax Ltd.
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

#ifndef NL_PRIMITIVE_CONFIGURATION_H
#define NL_PRIMITIVE_CONFIGURATION_H

#include "nel/misc/types_nl.h"
#include "nel/misc/rgba.h"
#include <vector>

// Include from libxml2
#include <libxml/parser.h>

namespace NLLIGO
{

class CLigoConfig;
class IPrimitive;

/**
 * Ligo primitive configuration description.
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class CPrimitiveConfigurations
{
public:
	
	// The name of the matching values
	std::string	Name;		

	// The configuration color
	NLMISC::CRGBA	Color;

	// Matching pairs
	class CMatchGroup
	{
	public:
		std::vector<std::pair<std::string, std::string>	>	Pairs;
	};

	// The pair of name / value parameter to match
	std::vector<CMatchGroup>	MatchPairs;

	// Read from a xml tree
	bool	read (xmlNodePtr configurationNode, const char *filename, const char *name, class CLigoConfig &config);

	// Test if this primitive belong this configuration
	bool	belong (const IPrimitive &primitive) const;
};

}

#endif // NL_PRIMITIVE_CONFIGURATION_H

/* End of ligo_config.h */
