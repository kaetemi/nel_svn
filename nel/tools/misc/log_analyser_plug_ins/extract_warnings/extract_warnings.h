/** \file extract_warnings.h
 * Interface of the DLL application
 *
 * $Id: extract_warnings.h,v 1.1 2003/08/06 14:07:21 cado Exp $
 */

/* Copyright, 2003 Nevrax Ltd.
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


#ifndef EXTRACT_WARNINGS_H
#define EXTRACT_WARNINGS_H

#include <nel/misc/types_nl.h>
#include <vector>
#include <string>


// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CONNECTION_STATS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CONNECTION_STATS_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef LOG_ANALYSER_PLUGIN_EXPORTS
#define LOG_ANALYSER_PLUGIN_API __declspec(dllexport)
#else
#define LOG_ANALYSER_PLUGIN_API __declspec(dllimport)
#endif


LOG_ANALYSER_PLUGIN_API std::string getInfoString();
LOG_ANALYSER_PLUGIN_API bool doAnalyse( const std::vector<const char *>& vec, std::string& res, std::string& log );

#endif