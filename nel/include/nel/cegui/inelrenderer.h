/**
 * \file nelrenderer.h
 * \date November 2004
 * \author Matt Raykowski
 * \author Henri Kuuste
 * \date 2008-11-08 16:16GMT
 * NeLRenderer
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

#ifndef __INELRENDERER_H__
#define __INELRENDERER_H__

// standard includes
#include <set>
#include <list>

// CEGUI includes
#include <CEGUIBase.h>
#include "CEGUIRenderer.h"
#include "CEGUITexture.h"
#include "CEGUISystem.h"
#include "CEGUIExceptions.h"

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
#include <nel/misc/dynloadlib.h>
#include <nel/misc/class_registry.h>

#include <nel/3d/u_scene.h>
#include <nel/3d/u_camera.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_texture.h>
#include <nel/3d/u_material.h>
#include <nel/3d/u_instance.h>
#include <nel/3d/u_text_context.h>
#include <nel/3d/u_particle_system_instance.h>

//#ifdef NL_OS_WINDOWS
//#ifdef NEL_CEGUIRENDERER_EXPORTS
//#define DLLSPEC __declspec(dllexport)
//#else //NEL_CEGUI_RENDERER_EXPORTS
//#define DLLSPEC __declspec(dllimport)
//#endif // NEL_CEGUI_RENDERER_EXPORTS
//#else // NL_OS_WINDOWS
//#define DLLSPEC 
//#endif // NL_OS_WINDOWS

// Start of CEGUI namespace section
namespace CEGUI
{
	// forward class definitions
	//class NeLTexture;
	class NeLResourceProvider;

	/**
	 * \brief Class to interface with the NeL rendering engine.
	 */
	class INeLRenderer : public Renderer
	{
	public:
		virtual	void	addQuad(const Rect& dest_rect, float z, const Texture* tex, const Rect& texture_rect, const ColourRect& colours, QuadSplitMode quad_split_mode)=0;
		virtual	void	doRender(void)=0;
		virtual	void	clearRenderList(void)=0;
		virtual	Texture *createTexture(void)=0;
		virtual Texture *createTexture(const String &filename, const String &resourceGroup)=0;
		virtual	Texture	*createTexture(float size)=0;
		virtual	void	destroyTexture(Texture* texture)=0;
		virtual void	destroyAllTextures(void)=0;
		virtual void	setQueueingEnabled(bool setting)=0;
		virtual bool	isQueueingEnabled(void) const=0;
		virtual void	sortQuads(void)=0;
		virtual float	getWidth(void) const=0;
		virtual float	getHeight(void) const=0;
		virtual Size	getSize(void) const=0;
		virtual Rect	getRect(void) const=0;
		virtual	uint	getMaxTextureSize(void) const=0;
		virtual	uint	getHorzScreenDPI(void) const=0;
		virtual	uint	getVertScreenDPI(void) const=0;
		virtual ResourceProvider *createResourceProvider(void)=0;

		// Some NeL stuff.
		virtual NL3D::UDriver &getNeLDriver()=0;
		//virtual Texture*	createTexture(NL3D::UMaterial *texture)=0;

		virtual NLMISC::CRGBA colorToNeL(CEGUI::colour color)=0;
		virtual void renderQuad(NLMISC::CQuadColorUV quad, NL3D::UMaterial mat)=0;

		

		virtual void captureCursor(bool capture)=0;
		virtual void activateInput()=0;
		virtual void deactivateInput()=0;
		virtual bool isInputActive()=0;
	}; // END CLASS INELRENDERER

}; // END NAMESPACE CEGUI

//class CEGUI::NeLRenderer;

//class CCeguiRendererNelLibrary : public NLMISC::INelLibrary {
//public:
//	void onLibraryLoaded(bool firstTime) { }
//	void onLibraryUnloaded(bool lastTime) { }

	// Provide a handle for users to generate a NeLRenderer object.
	//CEGUI::INeLRenderer *createNelRenderer(NL3D::UDriver *driver, bool withRP=true) {
	//	return new CEGUI::NeLRenderer(driver,withRP);
	//}
//};

	//CEGUI::INeLLogger *createNelLogger() {
	//	return new CEGUI::NeLLogger();
	//}

#endif // __INELRENDERER_H__