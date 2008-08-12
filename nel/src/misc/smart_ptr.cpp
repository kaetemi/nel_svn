/** \file smart_ptr.cpp
 * CSmartPtr and CRefPtr class.
 *
 * $Id: smart_ptr.cpp,v 1.5 2004/10/15 13:23:28 berenguier Exp $
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

#include "stdmisc.h"

#include "nel/misc/smart_ptr.h"


namespace NLMISC
{

// Use a Raw structure, to be sure it is initialized before any constructor calls...
//CPtrInfo() {Ptr=NULL; RefCount=0x7FFFFFFF; IsNullPtrInfo=true;}
CRefCount::CPtrInfoBase		CRefCount::NullPtrInfo= {NULL, 0x7FFFFFFF, true};


// must not be static
void	dummy_to_avoid_stupid_4768_smart_ptr_cpp()
{
}


}

