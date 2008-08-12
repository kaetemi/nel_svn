/** \file ligo/ligo_material.h
 * A ligoscape material
 *
 * $Id: ligo_material.h,v 1.2 2003/09/30 13:49:13 lecroart Exp $
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

#ifndef NL_MATERIAL_LIGO_H
#define NL_MATERIAL_LIGO_H

#include "nel/misc/types_nl.h"
#include "zone_template.h"

// NeL include
//#include "3d/zone.h"

namespace NLLIGO
{

class CLigoError;
class CLigoConfig;

/**
 * A ligoscape material
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class CMaterial
{
public:

	/// Build method
	bool build (const CZoneTemplate &tplt, const CLigoConfig &config, CLigoError &errors);

	/// Return the material edge
	const CZoneEdge& getEdge () const { return _ZoneEdge; }

	/// Serial method
	void serial (NLMISC::IStream &s);

private:

	// The zone template for this material
	CZoneEdge		_ZoneEdge;
};

}

#endif // NL_MATERIAL_LIGO_H

/* End of material.h */
