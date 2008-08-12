/** \file mutable_container.h
 *
 * $Id: mutable_container.h,v 1.2 2006/05/31 12:03:13 boucher Exp $
 */

/* Copyright, 2000-2004 Nevrax Ltd.
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

#ifndef NL_MUTABLE_CONTAINER_H
#define NL_MUTABLE_CONTAINER_H

namespace NLMISC
{
	/** Container wrapper that allow read/write access to element stored in 
	 *	a const container.
	 *	In fact, the template only allow calling begin() and end() over
	 *	a const container.
	 *	This prevent the user to change the structure of the container.
	 *	Usage :
	 *		
	 *		class foo
	 *		{
	 *			typedef TMutableContainer<vector<string> > TMyCont;
	 *			TMyCont	_MyCont;
	 *	
	 *		public:
	 *			// return the container with mutable item content but const item list
	 *			const TMyCont getContainer() const { return _MyCont; };
	 *		}
	 *			
	 */
	template <class BaseContainer>
	struct TMutableContainer : public BaseContainer
	{
		typename BaseContainer::iterator begin() const
		{
			return const_cast<BaseContainer*>(static_cast<const BaseContainer*>(this))->begin();
		}

		typename BaseContainer::iterator end() const
		{
			return const_cast<BaseContainer*>(static_cast<const BaseContainer*>(this))->end();
		}
	};

} // namespace NLMISC

#endif // NL_MUTABLE_CONTAINER_H
