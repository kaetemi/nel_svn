/** \file ps_iterator.h
 * Iterator that have a integral or fixed-point step. They are used to managed LOD
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


#ifndef NL_PS_ITERATOR_H
#define NL_PS_ITERATOR_H

#include "nel/3d/animation_time.h"

namespace NL3D
{

	#ifdef NL_OS_WINDOWS
		#define GET_INLINE __forceinline
	#else
		#define GET_INLINE
	#endif



	/** Class that manage iterator progression with a step of 1
	  * We assume that T::value_type gives the operator* return type
	  * T is the type of the iterator.
	  * NOTE: this iterator is not intended to serves with STL algo, it doesn't support all the needed features,
	  *       ++ and * operator are provided as syntaxic sugars..
	  * This iterator is READ-ONLY
	  * TP is the type pointed by T
	  */
	template <typename T, typename PT>
	struct CAdvance1Iterator
	{
		T It;

		CAdvance1Iterator() {}
		/// create this iterator from the start of a container, and a given position (expressed in fixed point)
		CAdvance1Iterator(T it, uint32 index = 0)
		{
			It = it + index;
		}
		const PT &get() const { return *It; }
		void advance() { ++It; }
		void advance(uint numSteps)
		{
			It = It + numSteps;
		}
		CAdvance1Iterator &operator++() { advance(); return *this; }
		CAdvance1Iterator operator++(int) { CAdvance1Iterator tmp = this; advance(); return tmp; }
		const PT &operator * () const { return get(); }
	///	const T &operator -> () const { return It; }
		/// return the step in a 16:16 format

		bool operator==(const CAdvance1Iterator &other) const { return other.It == It; }
		bool operator!=(const CAdvance1Iterator &other) const { return !(*this == other); }
		CAdvance1Iterator operator+(sint quantity) { return CAdvance1Iterator(It + quantity); }
		CAdvance1Iterator &operator+=(sint quantity) { It = It + quantity; return *this; }
	};



	/** Class that manage iterator progression with a step of 16:16 in fixed point
	  * We assume that T::value_type gives the operator* return type
	  * T is the type of the iterator
	  * This iterator is READ-ONLY
	  * NOTE: this iterator is not intended to serves with STL algo, it doesn't support all the needed features,
	  *       ++ and * operator are provided as syntaxic sugars..
	  */
	template<typename T, typename PT>
	struct CAdvance1616Iterator
	{
		T It;
		uint32 CurrPos;
		uint32 Step;
		CAdvance1616Iterator() {}
		/// create this iterator from the start of a container, and a given position (expressed in fixed point)
		CAdvance1616Iterator(T it, uint32 index, uint32 step)
		{
			It = it;
			CurrPos = index * step;
			Step = step;
		}

		const PT &get() const { return *(It + (CurrPos >> 16)); }
		void advance() { CurrPos += Step; }
		void advance(uint numSteps)
		{
			CurrPos = CurrPos + numSteps * Step;
		}
		const PT &operator * () const { return get(); }
	///	T operator -> () const { return It + (CurrPos >> 16); }
		CAdvance1616Iterator &operator++() { advance(); return *this; }
		CAdvance1616Iterator operator++(int) { CAdvance1616Iterator tmp = this; advance(); return tmp; }
		bool operator==(const CAdvance1616Iterator &other) const
		{
			#ifdef _DEBUG
				nlassert(other.It == It);
				nlassert(other.Step == Step);
			#endif
			return other.CurrPos == CurrPos;
		}
		bool operator!=(const CAdvance1616Iterator &other) const { return !(*this == other); }
		CAdvance1616Iterator operator+(sint quantity)
		{
			CAdvance1616Iterator res;
			res.It = It;
			res.CurrPos = CurrPos + Step * quantity;
			res.Step = Step;
			return res;
		}
		CAdvance1616Iterator &operator+=(sint quantity)
		{
			CurrPos += quantity * Step;
			return *this;
		}
	};



	//////////////////////////////////////////////////
	//////////////////////////////////////////////////

	/// Some typedefs
	typedef CAdvance1Iterator<TPSAttribFloat::const_iterator, float> TIteratorFloatStep1;
	typedef CAdvance1Iterator<TPSAttribFloat::const_iterator, TAnimationTime> TIteratorFloatStep1;
	typedef CAdvance1Iterator<TPSAttribVector::const_iterator, NLMISC::CVector> TIteratorVectStep1;
	typedef CAdvance1616Iterator<TPSAttribFloat::const_iterator, float> TIteratorFloatStep1616;
	typedef CAdvance1616Iterator<TPSAttribFloat::const_iterator, TAnimationTime> TIteratorTimeStep1616;
	typedef CAdvance1616Iterator<TPSAttribVector::const_iterator, NLMISC::CVector> TIteratorVectStep1616;

} // NL3D


#endif
