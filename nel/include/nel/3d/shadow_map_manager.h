/** \file shadow_map_manager.h
 * TODO: File description
 *
 * $Id: shadow_map_manager.h,v 1.12 2005/02/22 10:19:12 besson Exp $
 */

/* Copyright, 2000-2003 Nevrax Ltd.
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

#ifndef NL_SHADOW_MAP_MANAGER_H
#define NL_SHADOW_MAP_MANAGER_H

#include "nel/misc/types_nl.h"
#include "shadow_map.h"
#include "nel/misc/types_nl.h"
#include "quad_grid.h"
#include "vertex_buffer.h"
#include "material.h"
#include "texture.h"


namespace NL3D {


class	CTransform;


// ***************************************************************************
#define	NL3D_SMM_QUADGRID_SIZE		16
#define	NL3D_SMM_QUADCELL_SIZE		8.0f
#define	NL3D_SMM_MAX_TEXTDEST_SIZE	256
#define	NL3D_SMM_MAX_FREETEXT		20
#define	NL3D_SMM_FADE_SPEED			0.5f

// ***************************************************************************
/**
 * A class to manage the render of shadow map.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2003
 */
class CShadowMapManager
{
public:

	/// Constructor
	CShadowMapManager();
	~CShadowMapManager();

	/// change the QuadGrid size. it reset all the receivers!
	void			setQuadGridSize(uint size, float cellSize);

	/** clear both _ShadowCasters and _GenerateShadowCasters lists
	 *	WARNING: the _GenerateShadowCasters list of shadow caster (added with addShadowCaster() / 
	 *	selectShadowMapsToGenerate()) must have valid Ptrs. => Cannot leave this list 
	 *	non empty at end of CScene::render() because some CTransform may be deleted between render()
	 */
	void			clearAllShadowCasters();

	/// Add a ShadowCaster that influence the scene this pass.
	void			addShadowCaster(CTransform *model);
	/** From List of ShadowCaster, select a sub - part (so called Loding ShadowMap Casters)
	 *	NB: Beware that this clear the currentlist of shadowMap to generate
	 *	NB: model->setGeneratingShadowMap(true); are called for each model selected
	 */
	void			selectShadowMapsToGenerate(CScene *scene);
	/// Add a ShadowRecevier visible in this scene for this pass
	void			addShadowReceiver(CTransform *model);

	/** render ShadowMap with ShadowCasters. Generate ShadowMap only (with the AuxDriver).
	 *	NB: current driver Frustum, ViewMatrix kept their initial state but ModelMatrix not.
	 */
	void			renderGenerate(CScene *scene);

	/** project ShadowMaps onto receivers. NB: renderGenerate() must have been called before.
	 *	NB: current driver Frustum, ViewMatrix kept their initial state but ModelMatrix not.
	 *	call clearShadowCaster
	 */
	void			renderProject(CScene *scene);

	/// Enable Polygon Smoothing
	void			enableShadowPolySmooth(bool enable) {_PolySmooth= enable;}
	/// get Enable Polygon Smoothing flag
	bool			getEnableShadowPolySmooth() const {return _PolySmooth;}

	/// Get the typical Material for Caster
	CMaterial		&getCasterShadowMaterial() {return _CasterShadowMaterial;}


	/// \name Texture Allocation
	// @{
	/// Allocate a texture for a shadowMap. NB: owned by a smartPtr. nlassert powerof2
	ITexture		*allocateTexture(uint textSize);
	/** Release this one.
	 *	NB: the texture is not deleted, but still will be used for later use
	 */
	void			releaseTexture(ITexture *text);
	// @}

// ******************
private:

	// The Casters added to this pass. cleared at render
	std::vector<CTransform*>	_ShadowCasters;
	// The Casters added to this pass that will compute their shadowMap this frame. cleared at render
	std::vector<CTransform*>	_GenerateShadowCasters;
	// This is a quadGrid of ShadowReceiver.
	typedef CQuadGrid<CTransform*>	TShadowReceiverGrid;
	TShadowReceiverGrid			_ShadowReceiverGrid;

	void			computeShadowDirection(CScene *scene, CTransform *sc, CVector &lightDir);
	void			computeShadowColors(CScene *scene, CTransform *sc, CRGBA &ambient, CRGBA &diffuse);

	void			fillBlackBorder(IDriver *drv, uint numPassText, uint numTextW, uint numTextH, uint baseTextureSize);

	void			setBlackQuad(uint index, sint x, sint y, sint w, sint h);

	void			updateBlurTexture(IDriver &drv, uint w, uint h);
	void			copyScreenToBlurTexture(IDriver *drv, uint numPassText, uint numTextW, uint numTextH, uint baseTextureSize);
	void			applyFakeGaussianBlur(IDriver *drv, uint numPassText, uint numTextW, uint numTextH, uint baseTextureSize, uint blurSource);
	void			setBlurQuadFakeGaussian(uint index, sint x, sint y, sint w, sint h);

	bool						_PolySmooth;

	// For clearing
	CVertexBuffer				_FillQuads;
	CMaterial					_FillMaterial;

	// For Blurring
	CSmartPtr<ITexture>			_BlurTexture[2];
	uint32						_BlurTextureW;
	uint32						_BlurTextureH;
	float						_BlurTextureOOW;
	float						_BlurTextureOOH;
	float						_BlurTextureD05W;
	float						_BlurTextureD05H;
	CMaterial					_BlurMaterial[2];
	CVertexBuffer				_BlurQuads;

	// For copy
	CVertexBuffer				_CopyQuads;
	CMaterial					_CopyMaterial;

	// For Receiving
	CMaterial					_ReceiveShadowMaterial;
	NLMISC::CSmartPtr<ITexture>	_ClampTexture;
	CShadowMapProjector			_ShadowMapProjector;

	// For Receiving
	CMaterial					_CasterShadowMaterial;

	void			clearGenerateShadowCasters();
		
	// Texture allocation
	typedef	std::map<ITexture *, CSmartPtr<ITexture> >	TTextureMap;
	typedef	TTextureMap::iterator						ItTextureMap;
	TTextureMap					_ShadowTextureMap;
	// List of free shadow textures
	std::vector<ItTextureMap>	_FreeShadowTextures;
	// Called at each renderGenerate().
	void						garbageShadowTextures(CScene *scene);

	// For Texture profiling
	NLMISC::CSmartPtr<ITexture::CTextureCategory>	_TextureCategory;
};


} // NL3D


#endif // NL_SHADOW_MAP_MANAGER_H

/* End of shadow_map_manager.h */
