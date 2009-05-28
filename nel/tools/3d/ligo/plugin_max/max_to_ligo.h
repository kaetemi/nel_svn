/** \file max_to_ligo.h
 * Convert a 3dsmax nel patch mesh in ligo data
 *
 * $Id: max_to_ligo.h,v 1.3 2003/07/03 09:35:08 distrib Exp $
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

#ifndef NL_MAX_TO_LIGO_H
#define NL_MAX_TO_LIGO_H

#include "nel/misc/types_nl.h"

#ifdef NL_NEW
#undef new
#endif


#include <max.h>
#undef min
#undef max

namespace NLLIGO
{

class CZoneTemplate;
class CLigoConfig;
class CLigoError;

/**
 * Convert a 3dsmax nel patch mesh in ligo data
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class CMaxToLigo
{
public:

	/** Convert a 3dsmax NeL patch mesh in a CZoneTemplate
	  * 
	  * \param pNode is the node of the object
	  * \param patchMesh is the patch mesh to convert
	  * \param zoneTemplate is the zone template to build
	  * \param config is the current lingo config file
	  * \param errors is the errors structure returned if the method returns false
	  * \param time is the time of the export
	  * \return true if success else check errors.
	  */
	static bool buildZoneTemplate (INode* pNode, const PatchMesh &patchMesh, CZoneTemplate &zoneTemplate, 
									const CLigoConfig &config, CLigoError &errors, TimeValue time);

	/** Load the config file
	  */
	static bool loadLigoConfigFile (CLigoConfig& config, Interface& it, bool dialog);

	/** Output an error message in a message box or in the system message
	  *
	  * \param msg is the message to display
	  * \param title is the title for the dialog
	  * \param it if a max interface
	  * \param dialog is true to see the message in a dilog, false to see it in the script window.
	  */
	static void errorMessage (const char *msg, const char *title, Interface& it, bool dialog);
};

}

#endif // NL_MAX_TO_LIGO_H

/* End of max_to_ligo.h */
