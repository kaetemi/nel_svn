/** \file scheme_manager.h
 * a collection of scheme (to set particle atributes)
 *
 * $Id: scheme_manager.h,v 1.2 2001/09/13 14:29:25 vizerie Exp $
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

#ifndef SCHEME_MANAGER_H
#define SCHEME_MANAGER_H

#include <nel/misc/stream.h>

#include <string>
#include <map>
#include <algorithm>

namespace NL3D
{
	class CPSAttribMakerBase;
}

class CSchemeManager
{
public:
	/// dtor
	~CSchemeManager();

	typedef std::pair<std::string, NL3D::CPSAttribMakerBase *> TSchemeInfo;
	// insert a new scheme in the collection. The scheme is then owned by this object
	void insertScheme(const std::string &name, NL3D::CPSAttribMakerBase *scheme);
	// get all the schemes with the given type
	void getSchemes(const std::string &type, std::vector<TSchemeInfo> &dest);
	// serial this collection
	void serial(NLMISC::IStream &f) throw(NLMISC::EStream);
	// swap this collection with another one
	void	swap(CSchemeManager &other);
	// remove a scheme from the bank, given a pointer on it
	void    remove(NL3D::CPSAttribMakerBase *am);
	// rename a scheme, given a pointer on it
	void    rename(NL3D::CPSAttribMakerBase *am, const std::string &newName);
protected:	
	typedef std::pair<std::string, NL3D::CPSAttribMakerBase *> TSchemeInfo;
	typedef std::multimap<std::string, TSchemeInfo> TSchemeMap;
	TSchemeMap		_SchemeMap;	
};

extern CSchemeManager SchemeManager;




#endif