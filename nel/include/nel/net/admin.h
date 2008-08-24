/** \file admin.h
 * manage services admin
 */

/* Copyright, 2003 Nevrax Ltd.
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

#ifndef NL_ADMIN_H
#define NL_ADMIN_H


//
// Inlcudes
//

#include <string>
#include <vector>


namespace NLNET {


//
// Structures
//

struct CAlarm
{
	CAlarm (const std::string &n, sint l, bool gt) : Name(n), Limit(l), GT(gt), Activated(false) { }

	std::string Name;		// variable name
	int	 Limit;				// limit value where the alarm is setted
	bool GT;				// true if the error is produce when var is greater than bound

	bool Activated;			// true if the limit is exceeded (mail is send everytimes the actived bool change from false to true)
};

struct CGraphUpdate
{
	CGraphUpdate (const std::string &n, sint u) : Name(n), Update(u), LastUpdate(0) { }

	std::string Name;		// variable name
	int	 Update;			// delta time in second when we have to check variable

	uint32	LastUpdate;		// in second
};

typedef void (*TRemoteClientCallback) (uint32 rid, const std::string &cmd, const std::string &entityNames);


//
// Externals
//

extern std::vector<CGraphUpdate> GraphUpdates;
extern std::vector<CAlarm> Alarms;


//
// Types
//

typedef std::vector<std::string> TAdminViewVarNames;
typedef std::vector<std::string> TAdminViewValues;
struct SAdminViewRow
{
	TAdminViewVarNames	VarNames;
	TAdminViewValues		Values;

	SAdminViewRow() {}
	SAdminViewRow(const TAdminViewVarNames& varNames, const TAdminViewValues& values): VarNames(varNames), Values(values) {}
};
typedef std::vector< SAdminViewRow > TAdminViewResult;


//
// Functions
//

void initAdmin (bool dontUseAES);

void updateAdmin ();

void setInformations (const std::vector<std::string> &alarms, const std::vector<std::string> &graphupdate);

void serviceGetView (uint32 rid, const std::string &rawvarpath, TAdminViewResult& answer, bool async=false);

void setRemoteClientCallback (TRemoteClientCallback cb);

void addRequestAnswer (uint32 rid, const TAdminViewVarNames& varNames, const TAdminViewValues& values);

} // NLNET


#endif // NL_ALARMS_H

/* End of email.h */
