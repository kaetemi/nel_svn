/** \file blend_wnd.h
 * Window class for the dlg slot blend window
 *
 * $Id: blend_wnd.h,v 1.2 2001/10/29 16:07:33 lecroart Exp $
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX D.T.C. SYSTEM.
 * NEVRAX D.T.C. SYSTEM is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX D.T.C. SYSTEM is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX D.T.C. SYSTEM; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef NL_BLEND_WND_H
#define NL_BLEND_WND_H

#include "nel/misc/types_nl.h"


/**
 * Window class for the dlg slot blend window
 *
 * \author Cyril 'Hulud' Corvazier
 * \author Nevrax France
 * \date 2001
 */
class CBlendWnd
{
public:

	/// Constructor
	CBlendWnd();

	// *** From CWnd

	void OnPaint (const RECT& client, CDC* pDc, float StartBlend, float EndBlend, float StartBlendTime, float EndBlendTime, 
		float Smoothness, float StartTime, float EndTime, bool enabled);

private:
	// Build a rect
	void MakeRect (const RECT& src, RECT& dst, float x, float y, float width, float height);

	// Build a point
	void MakePoint (const RECT& src, POINT& dst, float x, float y);
};


#endif // NL_BLEND_WND_H

/* End of blend_wnd.h */
