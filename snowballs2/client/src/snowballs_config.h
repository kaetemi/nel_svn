/** \file snowballs_config.h
 * Snowballs build configuration. Used for debug features.
 * This file is only supposed to be used in snowballs_client.h/cpp.
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
 * $Id: snowballs_config.h 444 2008-01-04 18:35:00Z Kaetemi $
 */

#include <nel/misc/types_nl.h>



// use the default log.log file (not erased on use)
// #define SBCLIENT_USE_LOG_LOG false



// the config file name
// #define SBCLIENT_CONFIG_FILE "snowballs_client.cfg"
// #define SBCLIENT_CONFIG_FILE_DEFAULT "snowballs_client_default.cfg"



// enable compiling sound related things
#define SBCLIENT_WITH_SOUND 1



// use snowballs log file
// #define SBCLIENT_USE_LOG 1

// snowballs log file name
#define SBCLIENT_LOG_FILE "snowballs_client.log"

// clear snowballs log before use
#define SBCLIENT_ERASE_LOG true

// version number
#define SBCLIENT_VERSION "2.1.537"


// some default defines
#if FINAL_VERSION
#	if !defined(SBCLIENT_USE_LOG_LOG)
#		define SBCLIENT_USE_LOG_LOG false
#	endif
#	if !defined(SBCLIENT_USE_LOG)
#		define SBCLIENT_USE_LOG 0
#	endif
#endif

#if !defined(SBCLIENT_USE_LOG_LOG)
#	define SBCLIENT_USE_LOG_LOG true
#endif
#if !defined (SBCLIENT_USE_LOG)
#	define SBCLIENT_USE_LOG 1
#endif

// for compatibility with old configuration
#ifndef SBCLIENT_CONFIG_FILE
#	ifndef SNOWBALLS_CONFIG
#		define SBCLIENT_CONFIG_FILE "snowballs_client.cfg"
#	else
#		define SBCLIENT_CONFIG_FILE SNOWBALLS_CONFIG "client.cfg"
#	endif
#endif

#ifndef SBCLIENT_CONFIG_FILE_DEFAULT
#	define SBCLIENT_CONFIG_FILE_DEFAULT "snowballs_client_default.cfg"
#endif
