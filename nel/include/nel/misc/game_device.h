/** \file game_device.h
 * TODO: File description
 *
 * $Id: game_device.h,v 1.3 2005/02/22 10:14:12 besson Exp $
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#ifndef NL_GAME_DEVICE_H
#define NL_GAME_DEVICE_H

#include "types_nl.h"
#include "input_device.h"
#include <string>
#include <vector>


namespace NLMISC 
{

/// Describe a game device
struct CGameDeviceDesc
{
	// type of the device
	enum TDevType { GamePad, Joystick, DontKnow, DevTypeLast }		DevType;
	// Friendly name for the instance. For example, "Joystick 1." 
	std::string	InstanceName;
	// Friendly name for the product
	std::string	ProductName;
	// Tells wether this device is connected
	bool		Connected;
};

// a list of game device description
typedef std::vector<CGameDeviceDesc> TDeviceDescVect;

/// for devices comparison. The 'Connected' field is ignored.
inline bool operator == (const CGameDeviceDesc &lhs, const CGameDeviceDesc &rhs)
{
	return lhs.InstanceName == rhs.InstanceName && lhs.ProductName == rhs.ProductName;
}
//
inline bool operator != (const CGameDeviceDesc &lhs, const CGameDeviceDesc &rhs)
{
	return !(lhs == rhs);
}


/**
 * This abstract a joystick or gamepad
 * \author Nicolas Vizerie
 * \author Nevrax France
 * \date 2002
 */
struct IGameDevice : public IInputDevice
{
	enum TAxis { XAxis = 0, YAxis, ZAxis, /* translation */
				 RXAxis, RYAxis, RZAxis,   /* rotations */
				 MaxNumAxis
				}; 						  

	/// Get a general description of this device
	virtual const CGameDeviceDesc &getDescription()  const = 0;
	
	///\name Controls presence
	//@{
		// returns the number of buttons available on this game device
		virtual	uint  getNumButtons()  const = 0;
		/** Check if the given axe is present on this game device
		  * NB : only absolute axis are managed
		  */
		virtual bool		hasAxis(TAxis axis)  const = 0;
		// Check the number of sliders presents on this game device
		virtual uint		getNumSliders()  const = 0;
		// Check the number of point of views controls present on this game device
		virtual	uint		getNumPOV()  const = 0;
	//@}

	///\name Controls names. Must ensure that controls are present before calling these methods.
	//@{
		virtual const char *getButtonName(uint index)  const = 0;
		virtual const char *getAxisName(TAxis axis)  const = 0;
		virtual const char *getSliderName(uint index)  const = 0;
		virtual const char *getPOVName(uint index)  const = 0;
	//@}

	///\name Controls state. Must ensure that controls are present before calling these methods.
	//@{
		// Return true if the given button is pushed.
		virtual bool		getButtonState(uint index) const = 0;
		// Return a value in [-1, 1] for a translation axis, or an orientation.
		virtual float		getAxisValue(TAxis axis) const = 0;
		// Return a value in [0, 1]
		virtual float		getSliderPos(uint index) const = 0;
		// Return a CCW angle in degrees
		virtual float		getPOVAngle(uint index) const = 0;
	//@}
};


} // NLMISC


#endif // NL_GAME_DEVICE_H

/* End of GAME_device.h */
