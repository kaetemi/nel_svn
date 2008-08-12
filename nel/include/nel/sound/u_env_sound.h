/** \file u_env_sound.h
 * UEnvSound: Game interface for localized environment sounds
 *
 * $Id: u_env_sound.h,v 1.9 2002/11/04 15:40:43 boucher Exp $
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

#ifndef NL_U_ENV_SOUND_H
#define NL_U_ENV_SOUND_H

#include "nel/misc/types_nl.h"
#include "nel/misc/vector.h"

namespace NLSOUND {


class USource;

/** Output a warning message in deprecated function call.
 *	Put this macro on the first line of each deprecated method to
 *	output a warning message.
 */
#define DEPRECATED_CALL static bool _deprecatedWarningDone##__LINE__ = false;\
						if (!_deprecatedWarningDone##__LINE__) \
						{	\
							_deprecatedWarningDone##__LINE__ = true;	\
							nlwarning("This method is deprecated, you should update your code.");	\
						}




/**
 * Game interface for localized environment sounds
 * \deprecated
 *
 * An envsound object is a node of an envsound tree, the root of which
 * is returned by UAudioMixer::loadEnvSounds(). The root is the world
 * envsound: it has no bounds. The areas of children envsounds have
 * bounds and they must be totally included in the area of their
 * parent envsound.
 *
 * For arguments as 3D vectors, use the NeL vector coordinate system:
 * \verbatim
 *     (top)
 *       z    
 *       |  y (front)
 *       | /
 *       -----x (right)
 * \endverbatim
 *
 * An envsound source plays with the priority HighPri, and has the
 * priority LowPri when not playing.
 *
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2001
 */
class UEnvSound
{
public:

	/// Return the position
	virtual void					getPos( NLMISC::CVector& pos ) const = 0;
	/// Moves the envsound (and its transition envsound if it has one)
	virtual void					setPos( const NLMISC::CVector& pos ) = 0;
	/// Select the current env for this node, and for all descendants if children_too is true
	virtual void					selectEnv( const char *tag, bool children_too=false ) = 0;
	/// Return the children envsounds
	virtual std::vector<UEnvSound*>& getChildren() = 0;


	/// Play this node, and all descendants if children_too is true
	virtual void					play( bool children_too=false ) = 0;
	/// Stop playing this node, and all descendants if children_too is true
	virtual void					stop( bool children_too=false ) = 0;


	/// Destructor
	virtual							~UEnvSound() {}

protected:

	/// Constructor
	UEnvSound() {}

};


} // NLSOUND


#endif // NL_U_ENV_SOUND_H

/* End of u_env_sound.h */
