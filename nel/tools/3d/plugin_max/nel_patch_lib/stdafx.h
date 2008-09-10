/** \file stdafx.h
 * TODO: File description
 *
 * $Id: stdafx.h,v 1.4 2004/11/15 10:25:11 lecroart Exp $
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

#pragma conform(forScope, push)
#pragma conform(forScope, off)

#define _CRT_SECURE_NO_DEPRECATE

#pragma warning (disable : 4786)
#include <Max.h>
#include <istdplug.h>
#include <meshadj.h>
#include <iparamb2.h>
#include <iparamm2.h>

#undef _CRT_SECURE_NO_DEPRECATE

#pragma conform(forScope, pop)

#undef min
#undef max
