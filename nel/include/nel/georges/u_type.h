/** \file u_type.h
 * Georges form loader interface
 *
 * $Id: u_type.h,v 1.4 2003/08/27 16:16:25 distrib Exp $
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

#ifndef NL_U_TYPE_H
#define NL_U_TYPE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"

namespace NLGEORGES 
{

/**
 * Georges type interface
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2002
 */
class UType : public NLMISC::CRefCount
{
public:

  virtual ~UType() { }

	// ** Type
	enum TType
	{
		UnsignedInt=0,
		SignedInt,
		Double,
		String,
		Color,
		TypeCount
	};

	/**
	  * Get the type of this type.
	  */
	virtual TType				getType () const = 0;

	/**
	  * Get the default value of this type.
	  */
	virtual const std::string	&getDefault () const = 0;

	/**
	  * Get the min value of this type.
	  */
	virtual const std::string	&getMin () const = 0;

	/**
	  * Get the max value of this type.
	  */
	virtual const std::string	&getMax () const = 0;

	/**
	  * Get the increment value of this type.
	  */
	virtual const std::string	&getIncrement () const = 0;

	/**
	  * Get the definition count for this type.
	  */
	virtual uint				getNumDefinition () const = 0;

	/**
	  * Get a definition for this type.
	  *
	  * index is the index of the defnition you want to get.
	  * If the method returns true, label will be filled with
	  * the definition label and value will be filled with the
	  * defnition value.
	  * The method returns false if the index is invalid. In this 
	  * case, label and value are not changed.
	  */
	virtual bool				getDefinition (uint index, std::string &label, std::string &value) const = 0;

	/**
	  * Get theh comments of type.
	  */
	virtual const std::string	&getComment () const = 0;

	/**
	  * Get dependency files
	  */
	virtual void	getDependencies (std::set<std::string> &dependencies) const = 0;
};


} // NLGEORGES


#endif // NL_U_TYPE_H

/* End of u_type.h */
