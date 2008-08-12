/** \file form_loader.cpp
 * Georges form loader implementation
 *
 * $Id: form_loader.cpp,v 1.15 2005/01/17 16:39:42 lecroart Exp $
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

#include "stdgeorges.h"

#include "nel/misc/file.h"
#include "nel/misc/path.h"
#include "nel/misc/i_xml.h"

#include "nel/georges/u_form.h"

#include "form_loader.h"
#include "type.h"
#include "form.h"
#include "form_dfn.h"

using namespace NLMISC;
using namespace std;

namespace NLGEORGES 
{

// ***************************************************************************

void warning (bool exception, const char *format, ... );

// ***************************************************************************
// UFormLoader
// ***************************************************************************

UFormLoader *UFormLoader::createLoader ()
{
	return new CFormLoader;
}

// ***************************************************************************

void UFormLoader::releaseLoader (UFormLoader *loader)
{
	delete ((CFormLoader*)loader);
}

// ***************************************************************************
// CFormLoader
// ***************************************************************************
CFormLoader::~CFormLoader()
{
}

CType *CFormLoader::loadType (const char *filename)
{
	// Lower string filename
	string lowerStr = toLower((string)filename);
	lowerStr = CFile::getFilename (lowerStr);

	// Already in the map ?
	TTypeMap::iterator ite = _MapType.find (lowerStr);
	if (ite != _MapType.end() && (ite->second != NULL) )
	{
		// Return the pointer
		return ite->second;
	}
	else
	{
		// Create the type
		CType *type = new CType;

		// Load the type
		try
		{
			// Open the file
			string name = CPath::lookup (filename, false, false);
			if (name.empty())
				name = filename;
			CIFile file;
			if (file.open (name))
			{
				// Init an xml stream
				CIXml read;
				read.init (file);

				// Read the type
				type->read (read.getRootNode ());
			}
			else
			{
				// Output error
				warning (false, "loadType", "Can't open the form file (%s).", filename);

				// Delete the type
				delete type;
				type = NULL;
			}
		}
		catch (Exception &e)
		{
			// Output error
			warning (false, "loadType", "Error while loading the form (%s): %s", filename, e.what());

			// Delete the type
			delete type;
			type = NULL;
		}

		// Loaded ?
		if (type)
		{
			// Insert a new entry
			_MapType[lowerStr]= type;
			ite = _MapType.find (lowerStr);
			//CType *typeType = ite->second;
			//			int toto = 0;
		}
		return type;
	}
}

// ***************************************************************************

CFormDfn *CFormLoader::loadFormDfn (const char *filename, bool forceLoad)
{
	// Lower string filename
	string lowerStr = toLower((string)filename);
	lowerStr = CFile::getFilename (lowerStr);

	// Already in the map ?
	TFormDfnMap::iterator ite = _MapFormDfn.find (lowerStr);
	if (ite != _MapFormDfn.end() && ite->second)
	{
		// Return the pointer
		return ite->second;
	}
	else
	{
		// Create the formDfn
		CFormDfn *formDfn = new CFormDfn;

		// Insert the form first
		_MapFormDfn[lowerStr] = formDfn;

		// Load the type
		try
		{
			// Open the file
			string name = CPath::lookup (filename, false, false);
			if (name.empty())
				name = filename;
			CIFile file;
			if (file.open (name))
			{
				// Init an xml stream
				CIXml read;
				read.init (file);

				// Read the type
				formDfn->read (read.getRootNode (), *this, forceLoad, filename);
			}
			else
			{
				// Output error
				warning (false, "loadFormDfn", "Can't open the form file (%s).", filename);

				// Delete the formDfn
				delete formDfn;
				formDfn = NULL;
				_MapFormDfn.erase (lowerStr);
			}
		}
		catch (Exception &e)
		{
			// Output error
			warning (false, "loadFormDfn", "Error while loading the form (%s): %s", filename, e.what());

			// Delete the formDfn
			delete formDfn;
			formDfn = NULL;
			_MapFormDfn.erase (lowerStr);
		}

		return formDfn;
	}
}

// ***************************************************************************

UForm *CFormLoader::loadForm (const char *filename)
{
	// Lower string filename
	string lowerStr = toLower((string)filename);
	lowerStr = CFile::getFilename (lowerStr);

	// Already in the map ?
	TFormMap::iterator ite = _MapForm.find (lowerStr);
	if (ite != _MapForm.end() && ite->second)
	{
		// Return the pointer
		return (CForm*)ite->second;
	}
	else
	{
		// Create the form
		CForm *form = new CForm;

		// Insert the form first
		_MapForm[lowerStr] = form;

		// Load the type
		try
		{
			// Get the form DFN filename
			string name = CFile::getFilename (filename);
			uint index = name.rfind ('.');
			if (index == string::npos)
			{
				// Output error
				warning (false, "loadForm", "Form name is invalid (%s). It should have the extension of its DFN type.", name.c_str ());

				// Delete the form
				delete form;
				form = NULL;
				_MapForm.erase (lowerStr);
			}
			name = name.substr (index+1);
			name += ".dfn";

			// Load the dfn
			CFormDfn	*dfn = loadFormDfn (name.c_str (), false);
			if (dfn)
			{
				// Open the file
				name = CPath::lookup (filename, false, false);
				if (name.empty())
					name = filename;
				CIFile file;
				if (file.open (name))
				{
					// Init an xml stream
					CIXml read;
					read.init (file);

					// Read the form
					form->read (read.getRootNode (), *this, dfn, filename);
				}
				else
				{
					// Output error
					warning (false, "loadForm", "Can't open the form file (%s).", filename);

					// Delete the form
					delete form;
					form = NULL;
					_MapForm.erase (lowerStr);
				}
			}
			else
			{
				// Output error
				warning (false, "loadForm", "Can't open the dfn file (%s).", name.c_str ());

				// Delete the form
				delete form;
				form = NULL;
				_MapForm.erase (lowerStr);
			}
		}
		catch (Exception &e)
		{
			// Output error
			warning (false, "loadForm", "Error while loading the form (%s): %s", filename, e.what());

			// Delete the form
			delete form;
			form = NULL;
			_MapForm.erase (lowerStr);
		}

		return form;
	}
}

// ***************************************************************************

UFormDfn *CFormLoader::loadFormDfn (const char *filename)
{
	return loadFormDfn (filename, false);
}

// ***************************************************************************

UType *CFormLoader::loadFormType (const char *filename)
{
	return loadType (filename);
}

// ***************************************************************************

void CFormLoader::warning (bool exception, const char *function, const char *format, ... ) const
{
	// Make a buffer string
	va_list args;
	va_start( args, format );
	char buffer[1024];
	vsnprintf( buffer, 1024, format, args );
	va_end( args );

	// Set the warning
	NLGEORGES::warning (exception, "(CFormLoader::%s) : %s", function, buffer);
}

// ***************************************************************************

} // NLGEORGES
