/** \file range_manager.h
 * the range manager helps to store user defined preference in an CEditableRange dialog
 *
 * $Id: range_manager.cpp,v 1.4 2001/06/27 16:40:10 vizerie Exp $
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

#include "std_afx.h"
#include "range_manager.h"


// here instanciate static fields of tange_manager

// the range manager for floats
CRangeManager<float>::TRangeMap CRangeManager<float>::_RangeMap ;

// the range manager for unsigned ints
CRangeManager<uint32>::TRangeMap CRangeManager<uint32>::_RangeMap ;

// the range manager for signed ints
CRangeManager<sint32>::TRangeMap CRangeManager<sint32>::_RangeMap ;
