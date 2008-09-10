/** \file tile_utility.h
 * TODO: File description
 *
 * $Id: tile_utility.h,v 1.3 2004/11/15 10:25:11 lecroart Exp $
 */

/* Copyright, 2000 Nevrax Ltd.
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

#ifndef __TILE_UTILITY__H
#define __TILE_UTILITY__H

#pragma conform(forScope, push)
#pragma conform(forScope, off)

#define _CRT_SECURE_NO_DEPRECATE

#include <Max.h>
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <utilapi.h>
#include <plugapi.h>
#include <stdmat.h>

#undef _CRT_SECURE_NO_DEPRECATE

#pragma conform(forScope, pop)

#undef min
#undef max

#include "resource.h"

extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;

#define RGBAddClassID (Class_ID(0x5621932, 0x565a6387))

#endif // __TILE_UTILITY__H
