/** \file mysql_helper.h
 * <File description>
 *
 * $Id: mysql_helper.h,v 1.20 2004-12-13 10:42:06 lecroart Exp $
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX NeL Network Services.
 * NEVRAX NeL Network Services is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NeL Network Services is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NeL Network Services; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef NL_MYSQL_HELPER_H
#define NL_MYSQL_HELPER_H


//
// Includes
//

// we have to include windows.h because mysql.h uses it but not include it
#ifdef NL_OS_WINDOWS
#	define NOMINMAX
#	include <windows.h>
#endif

#include <mysql.h>

#include "nel/misc/types_nl.h"


//
// Variables
//

extern MYSQL *DatabaseConnection;


//
// Classes
//

class CMysqlResult
{
public:
	CMysqlResult() : Result(0) { }
	CMysqlResult(MYSQL_RES *result)
	{
		if(Result) mysql_free_result(Result);
		Result = result;
	};

	~CMysqlResult()
	{
		if(Result) mysql_free_result(Result);
	}

	CMysqlResult& operator=(MYSQL_RES *result)
	{
		if(Result) mysql_free_result(Result);
		Result = result;
		return *this;
	}

	operator MYSQL_RES*() { return Result; }

private:
	//we don't want user to do a copy
	CMysqlResult(const CMysqlResult &mysqlResult){};
	MYSQL_RES *Result;
};


//
// Functions
//

void sqlInit();
std::string sqlQuery(const std::string &query);
std::string sqlQuery(const std::string &query, sint32 &nbRow, MYSQL_ROW &firstRow, CMysqlResult &result);

#endif // NL_MYSQL_HELPER_H

/* End of mysql_helper.h */
