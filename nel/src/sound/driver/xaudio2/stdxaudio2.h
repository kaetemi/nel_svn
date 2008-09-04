/**
 * \file stdxaudio2.h
 * \brief STDXAudio2
 * \date 2008-08-20 12:32GMT
 * \author Jan Boon (Kaetemi)
 * STDXAudio2
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

#include <nel/misc/types_nl.h>

// STL includes
#include <iostream>

// 3rd Party Includes
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <x3daudio.h>

// NeL includes
#include <nel/misc/common.h>
#include <nel/misc/time_nl.h>
#include <nel/misc/fast_mem.h>
#include <nel/misc/debug.h>
#include <nel/misc/log.h>
#include <nel/misc/vector.h>
#include <nel/misc/singleton.h>
#include "../sound_driver.h"

/* end of file */
