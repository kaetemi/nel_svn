/** \file std_afx.h
 * TODO: File description
 *
 * $Id: std_afx.h,v 1.17 2007/03/19 09:55:26 boucher Exp $
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


#if !defined(AFX_STDAFX_H__9B22CB86_1929_11D5_9CD4_0050DAC3A412__INCLUDED_)
#define AFX_STDAFX_H__9B22CB86_1929_11D5_9CD4_0050DAC3A412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include "nel/misc/common.h"
#include "nel/misc/stream.h"
#include "nel/misc/vector.h"
#include "nel/misc/matrix.h"
#include "nel/misc/file.h"
#include "nel/misc/path.h"
#include "nel/misc/time_nl.h"
#include "nel/misc/config_file.h"
#include "nel/misc/event_listener.h"
#include "nel/misc/stream.h"

#include "nel/3d/logic_info.h"

#include "nel/pacs/u_global_position.h"


#include <vector>
#include <map>
#include <algorithm>


#include "nel/3d/nelu.h"
#include "nel/3d/mesh.h"
#include "nel/3d/transform_shape.h"
#include "nel/3d/mesh_instance.h"
#include "nel/3d/text_context.h"
#include "nel/3d/skeleton_model.h"
#include "nel/3d/animation_set.h"
#include "nel/3d/channel_mixer.h"
#include "nel/3d/shape.h"
#include "nel/3d/event_mouse_listener.h"
#include "nel/3d/light.h"
#include "nel/3d/font_manager.h"



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9B22CB86_1929_11D5_9CD4_0050DAC3A412__INCLUDED_)
