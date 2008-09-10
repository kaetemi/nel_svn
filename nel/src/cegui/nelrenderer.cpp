/**
 * \file nelrenderer.cpp
 * \date November 2004
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
	purpose:	Implementation of Renderer class for Nevrax engine

	For use with GUI Library:
	Crazy Eddie's GUI System (http://crayzedsgui.sourceforge.net)
    Copyright (C)2004 Paul D Turner (crayzed@users.sourceforge.net)

	This file contains code that is specific to NeL (http://www.nevrax.org)
*************************************************************************/

#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUIImage.h"
#include "CEGUIExceptions.h"
#include "CEGUISystem.h"

#include "nel/cegui/nelrenderer.h"
#include "nel/cegui/neltexture.h"
#include "nel/cegui/nelresourceprovider.h"

#include <nel/3d/u_material.h>
#include <nel/3d/u_driver.h>

#include <algorithm>

#ifdef NL_OS_WINDOWS
#	define NOMINMAX
#	include <windows.h>
#endif

// Start of CEGUI namespace section
namespace CEGUI
{
	class NeLTexture;

	/*************************************************************************
		Constants definitions
	*************************************************************************/
	const int	NeLRenderer::VERTEX_PER_QUAD			= 4;
	const int	NeLRenderer::VERTEX_PER_TRIANGLE		= 3;
	const int	NeLRenderer::VERTEXBUFFER_CAPACITY		= 4096;

	NeLRenderer::NeLRenderer(NL3D::UDriver *driver, bool withRP)
	{
		m_Driver=driver;
		d_queueing=true;
		NL3D::UDriver::CMode mode;
		driver->getCurrentScreenMode(mode);
		d_display_area.d_left=0;
		d_display_area.d_top=0;
		d_display_area.d_right=(float)driver->getWindowWidth();
		d_display_area.d_bottom=(float)driver->getWindowHeight();
		m_InputDriver.addToServer(m_Driver->EventServer);
		m_InputDriver.setScreenMode(d_display_area.getWidth(),d_display_area.getHeight(),(float)mode.Depth);
		m_InputDriver.setDriver(m_Driver);
		NLMISC::CHTimer::startBench();
		m_NelProvider=withRP;
		m_FrameCount=0;
	}

	NeLRenderer::~NeLRenderer(void)
	{
		destroyAllTextures();
		m_InputDriver.removeFromServer(m_Driver->EventServer);
		NLMISC::CHTimer::clear();
	}

	void NeLRenderer::addSearchPath(const std::string &path, bool recurse, bool alternative, class NLMISC::IProgressCallback *progressCallBack) {
		NLMISC::CPath::addSearchPath(path.c_str(),recurse,alternative,progressCallBack);
	}

	void NeLRenderer::addQuad(const Rect& dest_rect, float z, const Texture* tex, const Rect& texture_rect, const ColourRect& colours, QuadSplitMode quad_split_mode)
	{
		using namespace NLMISC;
		H_AUTO(NeLRenderer_addQuad);

		/*
		 * Special note: quad splitting is not yet supported.
		 */

		NLMISC::CQuadColorUV nelquad;

		NeLTexture *text=(NeLTexture *)tex;
		// set quad position, flipping y co-ordinates, and applying appropriate texel origin offset
		Rect position=dest_rect;
		position.offset(Point(-0.5f, -0.5f));
		// upper left
		nelquad.V0.set(position.d_left, position.d_top, z);
		nelquad.Uv0.set(texture_rect.d_left, texture_rect.d_top);
		nelquad.Color0=colorToNeL(colours.d_bottom_left);

		// upper right
		nelquad.V1.set(position.d_right, position.d_top, z);
		nelquad.Uv1.set(texture_rect.d_right, texture_rect.d_top);
		nelquad.Color1=colorToNeL(colours.d_bottom_right);

		// lower right
		nelquad.V2.set(position.d_right, position.d_bottom, z);
		nelquad.Uv2.set(texture_rect.d_right, texture_rect.d_bottom);
		nelquad.Color2=colorToNeL(colours.d_top_right);

		// lower left
		nelquad.V3.set(position.d_left, position.d_bottom, z);
		nelquad.Uv3.set(texture_rect.d_left, texture_rect.d_bottom);
		nelquad.Color3=colorToNeL(colours.d_top_left);

		if(!d_queueing) {
			renderQuad(nelquad,text->getNeLTexture());
		} else {
			QuadVector::reverse_iterator itr = d_quadlist.rbegin();
			if((d_quadlist.size() > 0) && ((*itr).texture == text)) {
				(*itr).quads.push_back(nelquad);
			} else {
				QuadInfo qI;
				qI.texture = text;
				qI.quads.push_back(nelquad);
				d_quadlist.push_back(qI);
			}
		}
	}

	void NeLRenderer::renderQuad(NLMISC::CQuadColorUV quad, NL3D::UMaterial mat) {
		using namespace NLMISC;
		H_AUTO(NeLRenderer_renderQuad);
		m_Driver->setFrustum(NL3D::CFrustum(0, d_display_area.getWidth(), d_display_area.getHeight(), 0, -1, 1, false));
		m_Driver->drawQuad(quad,mat);
	}

	void NeLRenderer::doRender(void)
	{
		using namespace NLMISC;
		H_AUTO(NeLRenderer_doRender);

		// set the culling frustrum
		m_Driver->setFrustum(NL3D::CFrustum(0, d_display_area.getWidth(), d_display_area.getHeight(), 0, -1, 1, false));

		// and go through the list.
		for(QuadVector::iterator itr=d_quadlist.begin();itr!=d_quadlist.end();itr++) {
			NL3D::UMaterial mat = (*itr).texture->getNeLTexture();
			m_Driver->drawQuads((*itr).quads,mat);
		}

		m_FrameCount++;
		if(m_FrameCount==200) {
#ifdef _DEBUG
			NLMISC::CHTimer::displaySummary();
			nlinfo("Quad list size: %d", d_quadlist.size());
#endif
			m_FrameCount=0;
		}
	}

	void NeLRenderer::clearRenderList(void)
	{
		d_quadlist.clear();
	}

	Texture *NeLRenderer::createTexture(void)
	{
		
		NeLTexture *tex=new NeLTexture(this);
		d_texturelist.push_back((NeLTexture *const)tex);
		return tex;
	}

	Texture *NeLRenderer::createTexture(const String &filename, const String &resourceGroup)
	{
		NeLTexture *tex=(NeLTexture*)createTexture();
		tex->loadFromFile(filename, resourceGroup);
		return tex;
	}

	Texture *NeLRenderer::createTexture(float size)
	{
		NeLTexture* tex = (NeLTexture*)createTexture();
		return tex;
	}


	void NeLRenderer::destroyTexture(Texture* texture)
	{
		if (texture != NULL)
		{
			NeLTexture *tex=(NeLTexture *)texture;
			d_texturelist.remove((NeLTexture *const)tex);
			delete tex;
		}
	}

	void NeLRenderer::destroyAllTextures(void)
	{
		while(!d_texturelist.empty())
		{
			destroyTexture((Texture *)*(d_texturelist.begin()));
		}
	}

	void NeLRenderer::sortQuads(void)
	{
		nlinfo("Received a request to sort quads.");
	}

	NLMISC::CRGBA NeLRenderer::colorToNeL(CEGUI::colour color) {
		NLMISC::CRGBA ctmp;
		ctmp.set((uint8)(color.getRed()*255),(uint8)(color.getGreen()*255),(uint8)(color.getBlue()*255),(uint8)(color.getAlpha()*255));
		return ctmp;
	}

	ResourceProvider* NeLRenderer::createResourceProvider(void)
	{
		if(d_resourceProvider==0) {
			//if(m_NelProvider) {
				d_resourceProvider = new NeLResourceProvider();
			//} else {
			//	d_resourceProvider = new DefaultResourceProvider();
			//}
		}
		return d_resourceProvider;
	}
} // end namespace CEGUI
