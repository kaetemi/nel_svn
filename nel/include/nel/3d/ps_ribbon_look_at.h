/** \file ps_ribbon_look_at.h
 * Ribbons that faces the user.
 *
 * $Id: ps_ribbon_look_at.h,v 1.14 2005/02/22 10:19:11 besson Exp $
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

#ifndef NL_PS_PARTICLE_RIBBON_LOOK_AT_H
#define NL_PS_PARTICLE_RIBBON_LOOK_AT_H


#include "ps_ribbon_base.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include <hash_map>


namespace NL3D 
{

/** A ribbon look at particle. It is like a ribbon, but textured (with no animation), and it always faces the user
  */
class CPSRibbonLookAt : public  CPSRibbonBase, public CPSSizedParticle, public CPSColoredParticle,
						public  CPSMaterial, public CPSTexturedParticleNoAnim
{
public:	
	///\name Object
	///@{
		/// ctor
		CPSRibbonLookAt();
		/// dtor
		~CPSRibbonLookAt();
		/// serialisation. Derivers must override this, and call their parent version
		virtual void		serial(NLMISC::IStream &f) throw(NLMISC::EStream);
		//
		NLMISC_DECLARE_CLASS(CPSRibbonLookAt);
	///@}

	///\name Texture
	///@{
		/// set the texture for this particle
		void						setTexture(CSmartPtr<ITexture> tex);
		/// get the texture used for this particle
		ITexture *getTexture(void) { return _Tex;}
		const ITexture		*getTexture(void) const { return _Tex;}
	///@}		

	///\name Behaviour
	///@{
			/** (de)activate color fading
			* when its done, colors fades to black along the tail.
			* NOT SUPPORTED FOR NOW
			*/
			virtual void setColorFading(bool onOff = true) {}

			/** Test wether color fading is activated.
			  * NOT SUPPORTED FOR NOW
			  */
			virtual bool getColorFading(void) const { return false; }

			/** tells in which basis is the tail
			*  It requires one transform per particle if it is not the same as the located that hold that particle
	  	    *  The default is false. With that you can control if a rotation of the system will rotate the tail
			*/
			virtual void setSystemBasis(bool yes) {}
		
			/// return true if the tails are in the system basis
			virtual bool isInSystemBasis(void) const { return true; }
		
		//void setPersistAfterDeath(bool persit = true);

		/** return true if the ribbon light persist after death 
		 *  \see _PersistAfterDeath()
		 */
		//bool getPersistAfterDeath(void) const { return _DyingRibbons != NULL; }
		
	///@}

	/// inherited from CPSParticle
	virtual void			step(TPSProcessPass pass);

	/// return true if there are transparent faces in the object
	virtual bool			hasTransparentFaces(void);

	/// return true if there are Opaque faces in the object
	virtual bool			hasOpaqueFaces(void);

	virtual uint32			getNumWantedTris() const;

	/// from CPSParticle : return true if there are lightable faces in the object
	virtual bool hasLightableFaces() { 	return false; }
	//
	virtual bool					supportGlobalColorLighting() const { return true; }	
	// from CPSLocatedBindable
	virtual void enumTexs(std::vector<NLMISC::CSmartPtr<ITexture> > &dest, IDriver &drv);

	// from CPSParticle
	virtual void setZBias(float value) { CPSMaterial::setZBias(value); }	
	virtual float getZBias() const { return CPSMaterial::getZBias(); }

protected:		

	CSmartPtr<ITexture>				_Tex;

	// the number of dying ribbons that are present
	//uint32							_NbDyingRibbons;
	// a counter to tell how much frame is left for each ribbon
	//std::vector<uint32>				_DyingRibbonsLifeLeft;
	/// inherited from CPSLocatedBindable
	virtual void					newElement(const CPSEmitterInfo &info);
	/// inherited from CPSLocatedBindable
	virtual void					deleteElement(uint32 index);
	/// inherited from CPSLocatedBindable	
	virtual void					resize(uint32 size);
	virtual CPSLocated				*getSizeOwner(void) { return _Owner; }
	virtual CPSLocated				*getColorOwner(void) { return _Owner; }	
private:	

	/// update the material and the vb so that they match the color scheme. Inherited from CPSColoredParticle
	virtual void					updateMatAndVbForColor(void);	

	/// display a set of ribbons
	void							displayRibbons(uint32 nbRibbons, uint32 srcStep);

	/**\name Vertex buffers & their corresponding index buffers. We keep a map of pretextured vertex buffer (with or without colors).
	  * Vb for ribbons that have the same size are shared.
	  */
		
	//@{

			/** a struct containing a vertex buffer and a primitive block
			  * \todo: primitive blocks can be shared for several vbs...
			  */
			class CVBnPB
			{
			public:
				CVertexBuffer		VB;
				CIndexBuffer		PB;
			public:
				CVBnPB()
				{
					NL_SET_IB_NAME(PB, "CPSRibbonLookAt::CVBnPB::PB");
					VB.setName("CPSRibbonLookAt::CVBnPB::VB");
				}
			};
			typedef std::hash_map<uint, CVBnPB> TVBMap;

			static TVBMap					_VBMap;			  // index buffers with no color
			static TVBMap					_ColoredVBMap;    // index buffer + colors			

			/// get a vertex buffer and a primitive suited for the current ribbon
			CVBnPB &getVBnPB();

			/// get the number of ribbons contained in a vb for a given length. (e.g the number of ribbons that can be batched)
			uint	getNumRibbonsInVB() const;
	//@}		
};



} // NL3D


#endif // NL_PS_RIBBON_LOOK_AT_H

/* End of ps_ribbon_look_at.h */
