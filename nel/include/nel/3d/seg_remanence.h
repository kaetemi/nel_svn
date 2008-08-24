/** \file seg_remanence.h
 * A segment that let a remanence on the screen (for sword trace)

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


#ifndef NL_SEG_REMANENCE_H
#define NL_SEG_REMANENCE_H

#include "nel/misc/vector.h"
#include "nel/3d/transform_shape.h"
#include "nel/3d/transform.h"
#include "nel/3d/animated_material.h"

#include <deque>


namespace NL3D
{

class IDriver;
class CVertexBuffer;
class CIndexBuffer;
class CMaterial;
class CScene;



/** A segment (or a more complicated shape) that let a 'trace' when it is moved.
  * Can be used for fx of a sword stroke for example
  *
  * \author Nicolas Vizerie
  * \author Nevrax France
  * \date 2002
  */

class CSegRemanence : public CTransformShape
{
public:
	///\name object
	//@{
		CSegRemanence();
		~CSegRemanence();
		CSegRemanence(CSegRemanence &other);
		CSegRemanence &operator = (CSegRemanence &other);
	//@}
	/// Call at the begining of the program, to register the model
	static	void			registerBasic();
	/// to instanciate that model from a scene
	static CTransform		*creator() { return new CSegRemanence; }
	// Render this model with currently setupped material and matrix
	void					render(IDriver *drv, CMaterial &mat);
	// sample current position
	void					samplePos(double date);
	/** Setup from the shape (no effect if geometry described in the shape didn't change)
	  */
	void					setupFromShape();


	///\name From CTransformShape
	//@{
		virtual bool				canStartStop() { return true; }
		// start the fx (by default it is off).
		virtual void				start();
		/// Stop the fx and let it unroll
		virtual void				stop();
		/// Stop the fx with no unrolling
		virtual void				stopNoUnroll();
		// Test wether the fx is started
		virtual bool				isStarted() const { return _Started; }
		// Test if the fx is stopping (unrollinh)
		bool						isStopping() const { return _Stopping; }
		// Equivalent to a call to start, then stop
		void						restart();
	//@}

	/** Set an animated material. This is usually called by the 'shape' of this object at instanciation
	  * The material is owned by this object
	  */
	void					setAnimatedMaterial(CAnimatedMaterial *mat);
	//
	CAnimatedMaterial		*getAnimatedMaterial() const { return _AniMat; }

	// Register to a channel mixer.
	void					registerToChannelMixer(CChannelMixer *chanMixer, const std::string &prefix);

	enum	TAnimValues
	{
		OwnerBit= CTransformShape::AnimValueLast,

		AnimValueLast,
	};


	virtual ITrack *getDefaultTrack (uint valueId);


	/// \name CTransform traverse specialisation
	// @{
	//virtual void	traverseHrc();
	virtual void	traverseAnimDetail();
	// @}

	/** \name slice time. Gives the time between 2 sampled position of the trail
	  */
	// @{
	/** Change the sampling period.
	  * NB : if the trail was started, then it is reseted by a call to stopNoUnroll
	  */
	void setSliceTime(float duration);
	float getSliceTime() const { return _SliceTime; }
	// @}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
private:
	class CSample
	{
	public:
		double				 Date;
		std::vector<CVector> Pos;          // sampled pos for each shape corner at the given date
		void swap(CSample &other) { std::swap(Date, other.Date); Pos.swap(other.Pos);}
	};
	CSample					 _Samples[4];    // 4 last sampled positions for all vertices
	uint					 _HeadSample;    // current sample for the head
	float					 _HeadProgress;  // progression of head in current sample (in [0, 1])
	//
	typedef std::vector<CVector> TPosVect;  // positions for each shape vertex at regular dates
	                                       // positions are ordered per date, then per shape


private:
	TPosVect			_Pos;
	uint				_NumSlices;
	uint				_NumCorners;
	bool				_Started;
	bool				_Stopping; // true if the effect is unrolling
	bool				_Restarted;
	float				_StartDate;
	float				_CurrDate;
	float				_UnrollRatio;
	float				_SliceTime;
	CAnimatedMaterial   *_AniMat;
	uint64				_LastSampleFrame;
	//
	static CVertexBuffer _VB;
	static CIndexBuffer  _IB;

private:
	void		updateOpacityFromShape();
	void		copyFromOther(CSegRemanence &other);
public:
	// for anim detail traversal
	void clearAnimatedMatFlag()
	{
		IAnimatable::clearFlag(OwnerBit);
	}
};


}

#endif


