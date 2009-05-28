/** \file variable.cpp
 * TODO: File description
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

#include "stdmisc.h"

#include "nel/misc/variable.h"

using namespace std;
using namespace NLMISC;

namespace NLMISC {


void cbVarChanged (CConfigFile::CVar &cvar)
{
	CCommandRegistry &cr = CCommandRegistry::getInstance();
	for (CCommandRegistry::TCommand::iterator comm = cr._Commands.begin(); comm != cr._Commands.end(); comm++)
	{
		if (comm->second->Type == ICommand::Variable && comm->second->getName() == cvar.Name)
		{
			IVariable *var = static_cast<IVariable*>(comm->second);
			string val = cvar.asString();
			nlinfo ("VAR: Setting variable '%s' with value '%s' from config file", cvar.Name.c_str(), val.c_str());
			var->fromString(val, true);
		}
	}
}


void IVariable::init (NLMISC::CConfigFile &configFile)
{
	CCommandRegistry::getInstance().initVariables(configFile);
}

void CCommandRegistry::initVariables(NLMISC::CConfigFile &configFile)
{
	for (TCommand::iterator comm = _Commands.begin(); comm != _Commands.end(); comm++)
	{
		if (comm->second->Type == ICommand::Variable)
		{
			IVariable *var = static_cast<IVariable *>(comm->second);
			if (var->_UseConfigFile)
			{
				configFile.setCallback(var->_CommandName, cbVarChanged);
				CConfigFile::CVar *cvar = configFile.getVarPtr(var->_CommandName);
				if (cvar != 0)
				{
					string val = cvar->asString();
					//nldebug("VAR: Setting variable '%s' with value '%s' from config file '%s'", var->_CommandName.c_str(), val.c_str(), configFile.getFilename().c_str());
					var->fromString(val, true);
				}
				else
				{
					//nldebug("VAR: No variable '%s' in config file '%s'", var->_CommandName.c_str(), configFile.getFilename().c_str());
				}
			}
		}
	}
}

} // NLMISC
