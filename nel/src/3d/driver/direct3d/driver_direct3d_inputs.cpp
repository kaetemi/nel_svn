/** \file driver_direct3d_inputs.cpp
 * Direct 3d driver implementation
 *
 * $Id: driver_direct3d_inputs.cpp,v 1.3 2004/08/09 14:35:08 vizerie Exp $
 *
 * \todo manage better the init/release system (if a throw occurs in the init, we must release correctly the driver)
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

#include "stddirect3d.h"

#include "nel/misc/di_event_emitter.h"
#include "nel/misc/mouse_device.h"

#include "driver_direct3d.h"

using namespace std;
using namespace NLMISC;

namespace NL3D
{

// ***************************************************************************

void CDriverD3D::showCursor (bool b)
{
	H_AUTO_D3D(CDriverD3D_showCursor);
	if (b)
	{
		while (ShowCursor(b) < 0) {};
	}
	else
	{
		while (ShowCursor(b) >= 0) {};
	}
};

// ***************************************************************************

void CDriverD3D::setMousePos(float x, float y)
{
	H_AUTO_D3D(CDriver3D_setMousePos);
	if (_HWnd)
	{
		// NeL window coordinate to MSWindows coordinates
		POINT pt;
		pt.x = (int)((float)(_CurrentMode.Width)*x);
		pt.y = (int)((float)(_CurrentMode.Height)*(1.0f-y));
		ClientToScreen (_HWnd, &pt);
		SetCursorPos(pt.x, pt.y);
	}
}

// ***************************************************************************

void CDriverD3D::setCapture (bool b)
{
	if (b)
	{
		RECT client;
		GetClientRect (_HWnd, &client);
		POINT pt1,pt2;
		pt1.x = client.left;
		pt1.y = client.top;
		ClientToScreen (_HWnd, &pt1);
		pt2.x = client.right;
		pt2.y = client.bottom;
		ClientToScreen (_HWnd, &pt2);
		client.bottom = pt2.y;
		client.top = pt1.y;
		client.left = pt1.x;
		client.right = pt2.x;
		ClipCursor (&client);
	}
	else
		ClipCursor (NULL);
}

// ***************************************************************************

NLMISC::IMouseDevice	*CDriverD3D::enableLowLevelMouse(bool enable, bool exclusive)
{
	H_AUTO_D3D(CDriverD3D_enableLowLevelMouse);
	if (_EventEmitter.getNumEmitters() < 2) 
		return NULL;
	NLMISC::CDIEventEmitter *diee = NLMISC::safe_cast<CDIEventEmitter *>(_EventEmitter.getEmitter(1));
	if (enable)
	{
		try
		{
			NLMISC::IMouseDevice *md = diee->getMouseDevice(exclusive);
			return md;
		}
		catch (EDirectInput &)
		{
			return NULL;
		}
	}
	else
	{
		diee->releaseMouse();
		return NULL;
	}
}

// ***************************************************************************

NLMISC::IKeyboardDevice		*CDriverD3D::enableLowLevelKeyboard(bool enable)
{
	H_AUTO_D3D(CDriverD3D_enableLowLevelKeyboard);
	if (_EventEmitter.getNumEmitters() < 2) return NULL;
	NLMISC::CDIEventEmitter *diee = NLMISC::safe_cast<NLMISC::CDIEventEmitter *>(_EventEmitter.getEmitter(1));
	if (enable)
	{
		try
		{
			NLMISC::IKeyboardDevice *md = diee->getKeyboardDevice();
			return md;
		}
		catch (EDirectInput &)
		{
			return NULL;
		}
	}
	else
	{
		diee->releaseKeyboard();
		return NULL;
	}
}

// ***************************************************************************

NLMISC::IInputDeviceManager		*CDriverD3D::getLowLevelInputDeviceManager()
{
	H_AUTO_D3D(CDriverD3D_getLowLevelInputDeviceManager);
	if (_EventEmitter.getNumEmitters() < 2) return NULL;
	NLMISC::CDIEventEmitter *diee = NLMISC::safe_cast<NLMISC::CDIEventEmitter *>(_EventEmitter.getEmitter(1));
	return diee;
}

// ***************************************************************************

uint CDriverD3D::getDoubleClickDelay(bool hardwareMouse)
{
	H_AUTO_D3D(CDriverD3D_getDoubleClickDelay);
	NLMISC::IMouseDevice *md = NULL;
	if (_EventEmitter.getNumEmitters() >= 2)
	{		
		NLMISC::CDIEventEmitter *diee = NLMISC::safe_cast<CDIEventEmitter *>(_EventEmitter.getEmitter(1));					
		if (diee->isMouseCreated())
		{			
			try
			{
				md = diee->getMouseDevice(hardwareMouse);					
			}
			catch (EDirectInput &)
			{
				// could not get device ..					
			}			
		}
	}
	if (md)
	{
		return md->getDoubleClickDelay();
	}
	// try to read the good value from windows
	return ::GetDoubleClickTime();
}

// ***************************************************************************

} // NL3D
