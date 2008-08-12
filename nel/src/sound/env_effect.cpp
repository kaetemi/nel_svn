/** \file env_effect.cpp
 * CEnvEffect: environmental effects and where they are applied
 *
 * $Id: env_effect.cpp,v 1.8 2003/01/08 15:48:11 boucher Exp $
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

#include "stdsound.h"

#include "env_effect.h"

using namespace NLMISC;


namespace NLSOUND {


/*
 * Constructor
 */
CEnvEffect::CEnvEffect() : _Current(0), _BoundingShape(NULL)
{
}


/*
 * Serialize file header
 */
void			CEnvEffect::serialFileHeader( NLMISC::IStream& s, uint32& nb )
{
	s.serialCheck( (uint32)'FEN' ); // NeL Environment FX
	if ( s.serialVersion( 2 ) < 2 )
	{
		throw EOlderStream(s);
	}
	
	s.serial( nb );
}


/*
 * Load several EnvEffects
 */
uint32			CEnvEffect::load( std::vector<CEnvEffect*>& container, NLMISC::IStream& s )
{
	if ( s.isReading() )
	{
		uint32 i, nb;
		serialFileHeader( s, nb );
		for ( i=0; i!=nb; i++ )
		{
			CEnvEffect *enveffect = new CEnvEffect();
			s.serial( *enveffect );
			container.push_back( enveffect );
		}
		return nb;
	}
	else
	{
		nlstop;
		return 0;
	}
}

IKsPropertySet_QuerySupport
/*
 * Set the environment type (EDIT)
 */
void			CEnvEffect::addEnvNum( TEnvEffectPreset num, const std::string& tag, float customsize )
{
	_EnvNums.push_back( TEnvEffectRoom(num,customsize) );
	_Tags.push_back( tag );
}


/*
 * Return the environment size
 */
float			CEnvEffect::getEnvSize() const
{
	if ( _EnvNums[_Current].Size > 0 )
	{
		return _EnvNums[_Current].Size;
	}
	else
	{
		return _BoundingShape->getDiameter();
	}
}


/*
 * Select the current environment
 */
void			CEnvEffect::selectEnv( const std::string& tag )
{
	uint i;
	for ( i=0; i!= _Tags.size(); i++ )
	{
		if ( _Tags[i] == tag )
		{
			_Current = i;
			nldebug( "AM: EnvEffect: Environment changed to %s", tag.c_str() );
			return;
		}
	}
	nldebug( "AM: EnvEffect: Environment %s not found", tag.c_str() );
	// Don't change _Current if not found
}


/*
 * Save (output stream only) (EDIT)
 */
void			CEnvEffect::save( const std::vector<CEnvEffect>& container, NLMISC::IStream& s )
{
	nlassert( ! s.isReading() );

	uint32 nb=container.size(), i;
	serialFileHeader( s, nb );
	for ( i=0; i!=nb; i++ )
	{
		s.serial( const_cast<CEnvEffect&>(container[i]) );
	}
}


} // NLSOUND
