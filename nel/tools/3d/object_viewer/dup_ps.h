/** \file dup_ps.h
 *
 * $Id: dup_ps.h,v 1.2 2006/02/06 13:54:09 vizerie Exp $
 */

/* Copyright, 2000, 2001, 2002 Nevrax Ltd.
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




#ifndef NL_DUP_PS_H
#define NL_DUP_PS_H


namespace NL3D
{
	class CParticleSystemProcess;
	class CPSLocatedBindable;
}


/** For now there is no duplication method in particle system.
  * These are needed for edition, though..
  * These functions provide a way to do this (by serializing the system in a memory stream).
  * NB this is slow
  * These may be removed, but this provide a easy way to accomplish our goal
  */

/** temp : duplicate a process of a particle system.
  * return NULL if the copy failed
  */
NL3D::CParticleSystemProcess	*DupPSLocated(const NL3D::CParticleSystemProcess *in);
	
/** temp : duplicate a located bindable of a particle system
  * return NULL if the copy failed
  */
NL3D::CPSLocatedBindable	*DupPSLocatedBindable(NL3D::CPSLocatedBindable *in);





#endif