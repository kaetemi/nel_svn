/** \file std_afx.h
 * TODO: File description
 *
 * $Id: std_afx.h,v 1.6 2007/03/19 09:55:26 boucher Exp $
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

#include <windows.h>
#include <locale.h>
#include <windowsx.h>
#include <commctrl.h>
#include <max.h>
#include <iparamb2.h>
#include <istdplug.h>
#include <iparamm2.h>
#include <utilapi.h>
#include <shlobj.h>
#undef STRICT
#include <MaxScrpt/maxscrpt.h>
#include <MaxScrpt/3dmath.h>
#include <MaxScrpt/numbers.h>
#include <MaxScrpt/maxclses.h>
#include <MaxScrpt/streams.h>
#include <MaxScrpt/mstime.h>
#include <MaxScrpt/maxobj.h>
#include <MaxScrpt/parser.h>
#include <stdmat.h>
#include <MaxScrpt/definsfn.h>
#include <animtbl.h>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#include "nel/misc/bsphere.h"
