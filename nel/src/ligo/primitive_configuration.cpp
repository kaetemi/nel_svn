/** \file primitive_configuration.cpp
 * Ligo primitive configuration description.
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#include "nel/ligo/primitive_configuration.h"
#include "nel/ligo/ligo_config.h"
#include "nel/ligo/primitive.h"
#include "nel/misc/i_xml.h"

using namespace std;
using namespace NLMISC;
using namespace NLLIGO;

extern bool ReadColor (CRGBA &color, xmlNodePtr node);

// ***************************************************************************

bool CPrimitiveConfigurations::read (xmlNodePtr configurationNode, const char *filename, const char *name, NLLIGO::CLigoConfig &config)
{
	// The name
	Name = name;

	// Read the color
	ReadColor (Color, configurationNode);

	// Get the first matching pair
	MatchPairs.reserve (CIXml::countChildren (configurationNode, "MATCH_GROUP"));
	xmlNodePtr matchGroups = CIXml::getFirstChildNode (configurationNode, "MATCH_GROUP");
	if (matchGroups)
	{
		do
		{
			// Add a pair
			MatchPairs.push_back(CMatchGroup());
			CMatchGroup &matchGroup = MatchPairs.back();

			// Get the first matching pair
			matchGroup.Pairs.reserve (CIXml::countChildren (matchGroups, "MATCH"));
			xmlNodePtr match = CIXml::getFirstChildNode (matchGroups, "MATCH");
			if (match)
			{
				do
				{
					// Add the match
					matchGroup.Pairs.resize (matchGroup.Pairs.size()+1);
					std::pair<std::string, std::string> &pair = matchGroup.Pairs.back();

					// Get the match name
					std::string name;
					if (config.getPropertyString (name, filename, match, "NAME"))
					{
						pair.first = name;
					}
					else
					{
						config.syntaxError (filename, match, "Missing match name in configuration (%s)", name.c_str());
						return false;
					}

					// Get the match value
					if (config.getPropertyString (name, filename, match, "VALUE"))
					{
						pair.second = name;
					}
				}
				while ((match = CIXml::getNextChildNode (match, "MATCH")));
			}
		}
		while ((matchGroups = CIXml::getNextChildNode (matchGroups, "MATCH_GROUP")));
	}
	return true;
}

// ***************************************************************************

bool	CPrimitiveConfigurations::belong (const IPrimitive &primitive) const
{
	// For each match group
	uint group;
	const uint numGroup = MatchPairs.size();
	for (group=0; group<numGroup; group++)
	{
		const CMatchGroup &matchGroup = MatchPairs[group];

		// For each rules
		uint rules;
		const uint numRules = matchGroup.Pairs.size();
		for (rules=0; rules<numRules; rules++)
		{
			const std::pair<std::string, std::string> &pairs = matchGroup.Pairs[rules];
			string key = toLower(pairs.second);

			// Get the property
			string value;
			if (primitive.getPropertyByName (pairs.first.c_str(), value))
			{
				if (toLower(value) == key)
					continue;
			}

			// Get the property
			const std::vector<string> *array = NULL;
			if (primitive.getPropertyByName (pairs.first.c_str(), array) && array)
			{
				uint i;
				for (i=0; i<array->size(); i++)
				{
					if (toLower((*array)[i]) == key)
						break;
				}
				if (i!=array->size())
					continue;
			}

			// Don't match
			break;
		}

		// Match ?
		if (rules == numRules)
			return true;
	}
	return false;
}

// ***************************************************************************

