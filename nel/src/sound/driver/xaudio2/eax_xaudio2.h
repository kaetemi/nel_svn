/**
 * \file eax_xaudio2.h
 * \brief CEaxXAudio2
 * \date 2008-09-04 00:47GMT
 * \author Jan Boon (Kaetemi)
 * CEaxXAudio2
 * 
 * $Id$
 */

/* 
 * Copyright (C) 2008  Jan Boon (Kaetemi)
 * 
 * This file is part of NLSOUND XAudio2 Driver.
 * NLSOUND XAudio2 Driver is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of
 * the License, or (at your option) any later version.
 * 
 * NLSOUND XAudio2 Driver is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NLSOUND XAudio2 Driver; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 */

#ifndef NLSOUND_EAX_XAUDIO2_H
#define NLSOUND_EAX_XAUDIO2_H
#include "stdxaudio2.h"

// STL includes

// NeL includes

// Project includes

namespace NLSOUND {

/**
 * \brief CEaxXAudio2
 * \date 2008-09-04 00:47GMT
 * \author Jan Boon (Kaetemi)
 * CEaxXAudio2 is a set of utility functions to get the right parameters for the EAX effects under XAudio2.
 */
class CEaxXAudio2
{
protected:
	static bool _Init;
	static const uint _DefaultEnv = 0;
	static const uint _MaxEnvironments = 26;
	static XAUDIO2FX_REVERB_PARAMETERS _Environments[_MaxEnvironments];

public:
	static void init();
	static void getEnvironment(uint envNum, XAUDIO2FX_REVERB_PARAMETERS* paramsOut);
	static inline uint getInvalidEnvironmentId() { return _MaxEnvironments; }

}; /* class CEaxXAudio2 */

} /* namespace NLSOUND */

#endif /* #ifndef NLSOUND_EAX_XAUDIO2_H */

/* end of file */
