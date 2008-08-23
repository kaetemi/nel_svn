/** \file ps_light.h
 */

/* Copyright, 2000, 2001, 2002, 2003 Nevrax Ltd.
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

#ifndef NL_PS_LIGHT_H
#define NL_PS_LIGHT_H


#include "nel/3d/ps_located.h"
#include "nel/3d/ps_attrib.h"

namespace NL3D
{
class CPointLightModel;

/**
 * A group of dynamic light created by a particle system
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2003
 */
class CPSLight : public CPSLocatedBindable
{
public:
	///\name object
	//@{
	/// ctor
	CPSLight();
	// dtor
	~CPSLight();
	NLMISC_DECLARE_CLASS(CPSLight);
	/// Serialisation. Derivers must override this, and call their parent version
	virtual void			serial(NLMISC::IStream &f) throw(NLMISC::EStream);
	//@}
	virtual uint32			getType(void) const;
	virtual uint32			getPriority(void) const { return 600; }
	/** From CPSLocatedBindable.
	  * For lights, this update their pos, colors and attenuation distances in the engine
	  */
	virtual void			step(TPSProcessPass pass);	
	///\name Attributes
	//@{
		// Set a constant color, this removes any previous color scheme.
		void					setColor(NLMISC::CRGBA color);
		// Get last contant color set
		NLMISC::CRGBA			getColor() const { return _Color; }	
		// Use an attribute maker for the color (NULL to discard)
		void					setColorScheme(CPSAttribMaker<NLMISC::CRGBA> *scheme);
		// Get attribute maker that generate colors (or NULL if constant color is used)
		CPSAttribMaker<NLMISC::CRGBA>  *getColorScheme() const { return _ColorScheme; }
		// Set a constant radius for attenuation start, must be > 0
		void					setAttenStart(float radius);
		// Get last set radius for attenuation start
		float					getAttenStart() const { return _AttenStart; }
		// Set an attribute maker that generate the radius at which light attenuation starts (or NULL to discard)
		void					setAttenStartScheme(CPSAttribMaker<float> *scheme);
		// Get attribute maker that generate the radius for attenuation start (or NULL if constant radius is used)
		CPSAttribMaker<float>  *getAttenStartScheme() const { return _AttenStartScheme; }
		// Set a constant radius for attenuation end
		void					setAttenEnd(float radius);
		// Get last set radius for attenuation end
		float					getAttenEnd() const { return _AttenEnd; }
		// Set an attribute maker that generate the radius at which light attenuation ends (or NULL to discard)
		void					setAttenEndScheme(CPSAttribMaker<float> *scheme);
		// Get attribute maker that generate the radius for attenuation end (or NULL if constant radius is used)
		CPSAttribMaker<float>  *getAttenEndScheme() const { return _AttenEndScheme; }		
	//@}	
	// from CPSLocatedBindable
	virtual void onShow(bool shown);
protected:
	virtual void				newElement(const CPSEmitterInfo &info);
	virtual void				deleteElement(uint32 index);
	virtual void				resize(uint32 size);
	virtual void				releaseAllRef();
	/// Show the lights (edition mode)
	void						show();
private:
	CPSAttrib<CPointLightModel *>	_Lights;
	NLMISC::CRGBA					_Color;
	CPSAttribMaker<NLMISC::CRGBA>	*_ColorScheme;
	float							_AttenStart;
	CPSAttribMaker<float>			*_AttenStartScheme;
	float							_AttenEnd;
	CPSAttribMaker<float>			*_AttenEndScheme;
};



} // namespace NL3D


#endif
