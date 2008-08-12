/** \file class_id.h
 * CClassId class
 *
 * $Id: class_id.h,v 1.5 2005/02/22 10:14:12 besson Exp $
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

#ifndef NL_CLASS_ID_H
#define NL_CLASS_ID_H


#include "types_nl.h"


namespace	NLMISC
{

// ***************************************************************************
/**
 * A unique id to specify Object by a uint64.
 * The Deriver should use a Max-like Id generator, to identify his own object.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class	CClassId
{
	uint64	Uid;

public:
	static const	CClassId	Null;

public:
	CClassId() {Uid=0;}
	CClassId(uint32 a, uint32 b) {Uid= ((uint64)a<<32) | b;}
	CClassId(uint64 a) {Uid=a;}
	bool	operator==(const CClassId &o) const {return Uid==o.Uid;}
	bool	operator!=(const CClassId &o) const {return Uid!=o.Uid;}
	bool	operator<=(const CClassId &o) const {return Uid<=o.Uid;}
	bool	operator>=(const CClassId &o) const {return Uid>=o.Uid;}
	bool	operator<(const CClassId &o) const {return Uid<o.Uid;}
	bool	operator>(const CClassId &o) const {return Uid>o.Uid;}
	//CClassId& operator=(const CClassId &o) { Uid = o.Uid; return *this;}
	operator uint64() const {return Uid;}

};


}


#endif // NL_CLASS_ID_H

/* End of class_id.h */
