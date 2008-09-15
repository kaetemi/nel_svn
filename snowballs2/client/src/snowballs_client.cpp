/** \file snowballs_client.cpp
 * CSnowballsClient
 * 
 * This file is part of NEVRAX SNOWBALLS.
 * NEVRAX SNOWBALLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * NEVRAX SNOWBALLS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NEVRAX SNOWBALLS; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 * $Id: snowballs_client.cpp 417 2007-12-29 19:37:37Z Kaetemi $
 */

#include <nel/misc/types_nl.h>
#include "snowballs_client.h"
#include "snowballs_config.h"

#include "component_manager.h"

#include <nel/misc/config_file.h>
#include <nel/misc/path.h>
#include <nel/misc/debug.h>

void switchGameState(); // temp
extern NLMISC::CConfigFile *ConfigFile; // temp
extern SBCLIENT::CComponentManager *ComponentManager; // temp

using namespace std;
using namespace NLMISC;

namespace SBCLIENT {

CSnowballsClient::CSnowballsClient() 
:
#ifdef SBCLIENT_USE_LOG
_FileDisplayer(NULL),
#endif
_ComponentManager(NULL)
{
	// use log.log if NEL_LOG_IN_FILE and SBCLIENT_USE_LOG_LOG defined as 1
	createDebug(NULL, SBCLIENT_USE_LOG_LOG, false);

#if SBCLIENT_USE_LOG
	// create snowballs_client.log
	// filedisplayer only deletes the 001 etc
	if (CFile::isExists(SBCLIENT_LOG_FILE))
		CFile::deleteFile(SBCLIENT_LOG_FILE);
	// initialize the log file
	_FileDisplayer = new CFileDisplayer();
	_FileDisplayer->setParam(SBCLIENT_LOG_FILE, SBCLIENT_ERASE_LOG);
	DebugLog->addDisplayer(_FileDisplayer);
	InfoLog->addDisplayer(_FileDisplayer);
	WarningLog->addDisplayer(_FileDisplayer);
	AssertLog->addDisplayer(_FileDisplayer);
	ErrorLog->addDisplayer(_FileDisplayer);
#endif	
	nlinfo("Starting Snowballs!");
	// end of debug/log initialization

	_ComponentManager = new CComponentManager(SBCLIENT_CONFIG_FILE);
	ConfigFile = &_ComponentManager->ConfigFile;

	::ComponentManager = _ComponentManager; // temp
}

CSnowballsClient::~CSnowballsClient()
{
	// if they're null, something must've seriously went wrong at some point
	nlassert(_ComponentManager); delete _ComponentManager;

	// begin of debug/log destruction
	nlinfo("See you later!");
#if SBCLIENT_USE_LOG
	nlassert(_FileDisplayer); delete _FileDisplayer;
#endif
}

int CSnowballsClient::run()
{
	// loop with some important things
	// and call the componentmanager update

	switchGameState(); // temp

	return EXIT_SUCCESS;
}

}

#ifdef NL_OS_WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdline, int nCmdShow)
#else
int main(int argc, char **argv)
#endif
{
	SBCLIENT::CSnowballsClient *client = new SBCLIENT::CSnowballsClient();
	int result = client->run(); delete client; return result;
}
