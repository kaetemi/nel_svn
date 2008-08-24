/** \file form_loader.h
 * Georges form loader implementation
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#ifndef NL_FORM_LOADER_H
#define NL_FORM_LOADER_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"
#include "nel/georges/u_form_loader.h"


namespace NLGEORGES
{

class UForm;
class CType;
class CFormDfn;
class CForm;

/**
 * Georges form loader implementation
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2002
 */
class CFormLoader : public UFormLoader
{
public:
	virtual ~CFormLoader();
	// From UFormLoader
	UForm		*loadForm (const char *filename);
	UFormDfn	*loadFormDfn (const char *filename);
	UType		*loadFormType (const char *filename);

	// Load type and formDfn
	CType		*loadType (const char *filename);
	CFormDfn	*loadFormDfn (const char *filename, bool forceLoad);

private:

	// Error handling
	virtual void		warning (bool exception, const char *function, const char *format, ... ) const;

	typedef std::map<std::string, NLMISC::CRefPtr<CType> >		TTypeMap;
	typedef std::map<std::string, NLMISC::CRefPtr<CFormDfn> >	TFormDfnMap;
	typedef std::map<std::string, NLMISC::CRefPtr<CForm> >		TFormMap;

	// Map of filename / CRefPtr<CType>
	TTypeMap		_MapType;

	// Map of filename / CRefPtr<CFormDfnCFormDfn>
	TFormDfnMap	_MapFormDfn;

	// Map of form / CRefPtr<CForm>
	TFormMap		_MapForm;
};


} // NLGEORGES


#endif // NL_FORM_LOADER_H

/* End of form_loader.h */
