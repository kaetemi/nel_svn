/**
 * \file snowballs_config.h
 * \brief CSnowballsClient
 * \date 2008-11-26 13:13GMT
 * \author NeL Developers
 * Snowballs compile configuration header.
 */

/* 
 * Copyright (C) 2008  by authors
 * 
 * This file is part of NEVRAX SNOWBALLS.
 * NEVRAX SNOWBALLS is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 * 
 * NEVRAX SNOWBALLS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NEVRAX SNOWBALLS; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
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
#define SBCLIENT_VERSION "2.1.551"



// temporary dev tags
#define SBCLIENT_DEV_SOUND 0
#define SBCLIENT_DEV_STEREO 0



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
