/**
 * \file NeLResourceProvider.h
 * \date January 2005
 * \author Matt Raykowski
 * \author Henri Kuuste
 */

/* Copyright, 2004 Werewolf
 *
 * This file is part of Werewolf.
 * Werewolf is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * Werewolf is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Werewolf; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */
/************************************************************************
	purpose:	Interface for main Nevrax Engine GUI renderer class

	For use with GUI Library:
	Crazy Eddie's GUI System (http://crayzedsgui.sourceforge.net)
    Copyright (C)2004 Paul D Turner (crayzed@users.sourceforge.net)

	This file contains code that is specific to NeL (http://www.nevrax.org)
*************************************************************************/

#ifndef __NELRESOURCEPROVIDER_H__
#define __NELRESOURCEPROVIDER_H__

#if defined( __WIN32__ ) || defined( _WIN32 )
#   ifdef NEL_GUIRENDERER_EXPORTS
#       define NEL_GUIRENDERER_API __declspec(dllexport)
#   else
#       define NEL_GUIRENDERER_API __declspec(dllimport)
#   endif
#else
#   define NEL_GUIRENDERER_API
#endif

// standard includes
#include <set>
#include <list>

// CEGUI includes
#include "CEGUIBase.h"
#include "CEGUIRenderer.h"
#include "CEGUITexture.h"
#include "CEGUISystem.h"

// NeL includes
#include <nel/misc/file.h>
#include <nel/misc/path.h>
#include <nel/misc/debug.h>
#include <nel/misc/vector.h>
#include <nel/misc/matrix.h>
#include <nel/misc/common.h>
#include <nel/misc/events.h>
#include <nel/misc/fast_mem.h>
#include <nel/misc/config_file.h>
#include <nel/misc/system_info.h>
#include <nel/misc/mem_displayer.h>

#include <nel/3d/u_scene.h>
#include <nel/3d/u_camera.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_texture.h>
#include <nel/3d/u_material.h>
#include <nel/3d/u_instance.h>
#include <nel/3d/u_text_context.h>
#include <nel/3d/u_particle_system_instance.h>

// Start of CEGUI namespace section
namespace CEGUI
{
	class NEL_GUIRENDERER_API NeLResourceProvider : public ResourceProvider
	{
	public:
		NeLResourceProvider();
		~NeLResourceProvider();

		void loadRawDataContainer(const String& filename, RawDataContainer& output, const String& resourceGroup);
	};
}; // end namespacec CEGUI

#endif // end __NELRESOURCEPROVIDER_H__
