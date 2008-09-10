/** \file stdafx.h
 * TODO: File description
 *
 * $Id: StdAfx.h,v 1.7 2007/03/19 16:54:47 boucher Exp $
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

#if !defined(AFX_STDAFX_H__7B19FB21_D10C_11D4_9CD4_0050DAC3A412__INCLUDED_)
#define AFX_STDAFX_H__7B19FB21_D10C_11D4_9CD4_0050DAC3A412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

//#include "nel/misc/types_nl.h"
// Max SDK includes
#include <max.h>
#include <stdmat.h>
#include <shaders.h>
#include <iparamb2.h>
#include <Maxscrpt/maxscrpt.h>
//#include <parser.h>

// Character Studio SDK include
#include <bipexp.h>
#include <phyexp.h>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#include <string>
#include <vector>

#include "../nel_patch_lib/rpo.h"
#include "nel/misc/time_nl.h"
#include "nel/misc/file.h"
#include "nel/misc/triangle.h"
#include "nel/misc/bsphere.h"
#include "nel/3d/quad_tree.h"
#include "nel/3d/scene_group.h"
#include "nel/3d/skeleton_shape.h"
#include "nel/3d/texture_file.h"
#include "nel/3d/light.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7B19FB21_D10C_11D4_9CD4_0050DAC3A412__INCLUDED_)
