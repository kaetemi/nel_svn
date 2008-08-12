/** \file env_effect.h
 * CEnvEffect: environmental effects and where they are applied
 *
 * $Id: env_effect.h,v 1.5 2002/11/04 15:40:44 boucher Exp $
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
#error "Deprecated"

#ifndef NL_ENV_EFFECT_H
#define NL_ENV_EFFECT_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"
#include "bounding_shape.h"

namespace NLSOUND {


/// EAX environmental effect presets
enum TEnvEffectPreset
{
    ENVEFFECT_GENERIC,
    ENVEFFECT_PADDEDCELL,
    ENVEFFECT_ROOM,
    ENVEFFECT_BATHROOM,
    ENVEFFECT_LIVINGROOM,
    ENVEFFECT_STONEROOM,
    ENVEFFECT_AUDITORIUM,
    ENVEFFECT_CONCERTHALL,
    ENVEFFECT_CAVE,
    ENVEFFECT_ARENA,
    ENVEFFECT_HANGAR,
    ENVEFFECT_CARPETEDHALLWAY,
    ENVEFFECT_HALLWAY,
    ENVEFFECT_STONECORRIDOR,
    ENVEFFECT_ALLEY,
    ENVEFFECT_FOREST,
    ENVEFFECT_CITY,
    ENVEFFECT_MOUNTAINS,
    ENVEFFECT_QUARRY,
    ENVEFFECT_PLAIN,
    ENVEFFECT_PARKINGLOT,
    ENVEFFECT_SEWERPIPE,
    ENVEFFECT_UNDERWATER,
    ENVEFFECT_DRUGGED,
    ENVEFFECT_DIZZY,
    ENVEFFECT_PSYCHOTIC,

    ENVEFFECT_COUNT
}; // Note: must follow the EAX enum


/// Enveffect preset and size
struct TEnvEffectRoom
{
	TEnvEffectPreset	Preset;
	float				Size;

	/// Constructor
	TEnvEffectRoom( const TEnvEffectPreset& preset=ENVEFFECT_ROOM, float size=7.5 ) : Preset(preset), Size(size) {}

	/// Serialize
	void serial ( NLMISC::IStream& s )
	{
		uint8 preset8 = (uint8)Preset; // out
		s.serial( preset8 );
		Preset = (TEnvEffectPreset)preset8; // in
		s.serial( Size );
	}
};


/**
 * Environmental effects and where they are applied
 * \deprecated
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class CEnvEffect
{
public:

	/// Constructor
	CEnvEffect();
	/// Destructor
	virtual ~CEnvEffect() {}
	/// Serialize
	void			serial( NLMISC::IStream& s )
	{
		// If you change this, increment the version number in serialFileHeader()
		s.serialPolyPtr( _BoundingShape );
		s.serialCont( _EnvNums );
		s.serialCont( _Tags );
	}
	/// Serialize file header
	static void		serialFileHeader( NLMISC::IStream& s, uint32& nb );
	/// Load several EnvEffects and return the number of effects loaded
	static uint32	load( std::vector<CEnvEffect*>& container, NLMISC::IStream& s );

	/// Return true if the environment includes the specified point
	bool			include( const NLMISC::CVector& pos ) { return _BoundingShape->include( pos ); }
	/// Select the current environment
	void			selectEnv( const std::string& tag );
	/// Return the environment type
	TEnvEffectPreset getEnvNum() const		{ return _EnvNums[_Current].Preset; }
	/// Return the environment size
	float			getEnvSize() const;


	/** Set the environment type (EDIT). 
	 * The size of the environment is computed with the bounding shape, unless the argument
	 * customshape is positive.
	 */
	void			addEnvNum( TEnvEffectPreset num, const std::string& tag="", float customsize=-1.0f );
	/// Access the bounding shape (EDIT)
	IBoundingShape	*getBoundingShape()		{ return _BoundingShape; }
	/// Set the bounding shape (EDIT)
	void			setBoundingShape( IBoundingShape *bs ) { _BoundingShape = bs; }
	/// Save (output stream only) (EDIT)
	static void		save( const std::vector<CEnvEffect>& container, NLMISC::IStream& s );


private:

	// Index of the current environment type
	uint8							_Current;

	// Types of environment
	std::vector<TEnvEffectRoom>		_EnvNums;

	// Environment tags (indicate which env to select)
	std::vector<std::string>		_Tags;

	// Bounding shape
	IBoundingShape					*_BoundingShape;
};


} // NLSOUND


#endif // NL_ENV_EFFECT_H

/* End of env_effect.h */

	