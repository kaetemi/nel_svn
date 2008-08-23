/** \file u_form_loader.h
 * Georges form loader interface
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

#ifndef NL_U_FORM_LOADER_H
#define NL_U_FORM_LOADER_H

#include "nel/misc/types_nl.h"


namespace NLGEORGES 
{

class UType;
class UForm;
class UFormDfn;

/**
 * Georges form loader interface
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2002
 */
class UFormLoader
{
public:
	virtual ~UFormLoader() {};

	/** Load a form, use NMISC::CPath to find the file.
	  * 
	  * The pointer on the form must be held in a CSmartPtr<UForm>. Returns NULL if the form can't be loaded.
	  */
	virtual UForm *loadForm (const char *filename) = 0;

	/** Load a DFN, use NMISC::CPath to find the file.
	  * 
	  * The pointer on the form must be held in a CSmartPtr<UFormDfn>. Returns NULL if the DFN can't be loaded.
	  */
	virtual UFormDfn *loadFormDfn (const char *filename) = 0;

	/** Load a type, use NMISC::CPath to find the file.
	  * 
	  * The pointer on the form must be held in a CSmartPtr<UType>. Returns NULL if the type can't be loaded.
	  */
	virtual UType *loadFormType (const char *filename) = 0;

	/// Create a form loader
	static UFormLoader *createLoader ();

	/// Create a form loader
	static void releaseLoader (UFormLoader *loader);
};


} // NLGEORGES


#endif // NL_U_FORM_LOADER_H

/* End of u_form_loader.h */
