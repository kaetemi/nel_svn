/** \file moulinette.h
 * 
 *
 * $Id: build_rbank.h,v 1.4 2004/01/13 16:36:59 legros Exp $
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

#ifndef NL_MOULINETTE_H
#define NL_MOULINETTE_H

#include <string>

void		processAllPasses(std::string &zoneName);
/*
void		tessellateAndMoulineZone(std::string &zoneName);
void		processRetriever(std::string &zoneName);
*/
void		processGlobalRetriever();
void		updateRetrieverBank();

#endif // NL_MOULINETTE_H

/* End of moulinette.h */
