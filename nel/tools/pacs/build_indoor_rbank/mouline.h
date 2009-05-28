/** \file mouline.h
 * 
 *
 * $Id: mouline.h,v 1.1 2002/01/07 11:17:03 lecroart Exp $
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

#ifndef NL_MOULINE_H
#define NL_MOULINE_H

#include <vector>

#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"
#include "nel/misc/file.h"

// External class declaration
namespace NLPACS
{
	class CCollisionMeshBuild;
	class CLocalRetriever;
};


// Computation functions
void	computeRetriever(NLPACS::CCollisionMeshBuild &cmb,
						 NLPACS::CLocalRetriever &lr,
						 NLMISC::CVector &translation,
						 bool useCmbTrivialTranslation = true);


#endif // NL_MOULINE_H

/* End of mouline.h */
