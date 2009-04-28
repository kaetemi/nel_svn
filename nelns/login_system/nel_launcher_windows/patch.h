/** \file patch.h
 *
 * $Id: patch.h,v 1.2 2003/04/08 18:25:56 lecroart Exp $
 */

/* Copyright, 2000 Nevrax Ltd.
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

#ifndef NL_PATCH_H
#define NL_PATCH_H

#include <string>

#include "nel/misc/types_nl.h"
#include "nel/misc/config_file.h"

extern NLMISC::CConfigFile ConfigFile;

void startPatchThread (const std::string &serverPath, const std::string &serverVersion, const std::string &urlOk, const std::string &urlFailed, const std::string &logSeparator);
bool patchEnded (std::string &url, bool &ok);
bool patchState (std::string &state, std::string &stateLog);




// get the version with the VERSION file
std::string getVersion ();

// set the VERSION file with the version
void setVersion (const std::string &version);

#endif // NL_PATCH_H

/* End of patch.h */
