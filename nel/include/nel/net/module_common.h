/** \file module_common.h
 * basic type and forward declaration for module system
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


#ifndef NL_MODULE_COMMON_H
#define NL_MODULE_COMMON_H

#include "nel/misc/smart_ptr.h"
#include "nel/misc/common.h"

namespace NLNET
{
	/// General type definition
	/// Module identifier
	typedef uint32	TModuleId;

	/// A module ID of 0 mean 'not valid module ID'
	const TModuleId	INVALID_MODULE_ID = 0;

	/// Forward smart ptr definition
	class IModule;
	typedef NLMISC::CSmartPtr<IModule>			TModulePtr;

	class IModuleProxy;
	typedef NLMISC::CSmartPtr<IModuleProxy>		TModuleProxyPtr;

	class IModuleSocket;
	class IModuleFactory;
	class IModuleGateway;
	struct TSecurityData;

	/// The destination module for a message cannot be reached by socket used
	class EModuleNotReachable : public NLMISC::Exception
	{
	};
	/// A module use a socket where it is not plugged in
	class EModuleNotPluggedHere : public NLMISC::Exception
	{
	};


	/** Structure for pre-parsed command line parameters
	 *	Support in memory representation of parameter line like :
	 *	'tag1(x=1 y=2 z=3) tag2=6 tag3(a=abc b=xyz tag4)'
	 */
	class TParsedCommandLine
	{
	public:

		// copy constructor is needed because SubParams contains pointers
		TParsedCommandLine(const TParsedCommandLine& copy);

		TParsedCommandLine()
		{

		};

		~TParsedCommandLine();

		/// The parameter name
		std::string		ParamName;
		/// The parameter value, empty in the case of a sub param header
		std::string		ParamValue;

		/// The list of sub parameters. Empty in the case of a single param.
		std::vector<TParsedCommandLine*>	SubParams;

		/// Cleanup
		void clear();

		/// Parse a NeL argument list to build a module init object.
		bool parseParamList(const std::string &rawParamString);

		/** Ask the command line for a parameter
		 *	If the parameter doesn't exist, the method return NULL.
		 *	You can request a sub param directly by
		 *	concatenating the header(s) name separated by dot.
		 *	e.g. in the param string "a(b(c=4)", you can
		 *	query directly with 'a.b.c' to retrieve the value 4.
		 */
		const TParsedCommandLine *getParam(const std::string &name) const;

		/** Add or replace a parameter in the set.
		 *	The name can be any valid name (e.g 'a' or 'a.b.c').
		 *	If any sub part of the name didn't exist, the function
		 *	will create the appropriate sub object.
		 */
		void setParam(const std::string &name, const std::string &value);

		/** Rebuild the raw command line string */
		std::string toString() const;

	private:
		bool _parseParamList(const std::string &rawParamString);
		const TParsedCommandLine *_getParam(std::vector<std::string>::iterator it, std::vector<std::string>::iterator end) const;
		TParsedCommandLine *_getParam(std::vector<std::string>::iterator it, std::vector<std::string>::iterator end);

	};

} // namespace NLNET

#endif // NL_MODULE_COMMON_H
