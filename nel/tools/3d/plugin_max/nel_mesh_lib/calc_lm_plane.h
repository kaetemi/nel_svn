/** \file calc_lm_plane.h
 * LightMap Calculation settings
 * Plane of faces in the same smooth group
 *
 * $Id: calc_lm_plane.h,v 1.5 2004/05/14 15:00:14 berenguier Exp $
 */

/* Copyright, 2001 Nevrax Ltd.
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

#ifndef NL_CALC_LM_PLANE_H
#define NL_CALC_LM_PLANE_H

// msk : this is the mask it has a size of w*h
// col : is all color planes continuous it has a size of w*h*nNbLayerUsed

// -------------------------------------------------------------------------------------------
struct SLMPlane
{

	sint32 x, y; // Pos in lightmap
	uint32 w, h; // Size
	vector<uint8> msk;	// 0 - No pixel
						// 1 - Pixel must be calculated
						// 2 - Pixel is interior and is calculated
						// 3 - Pixel is exterior in this plane but interior in another of the same smooth group
						// 4 - Pixel is exterior and is extrapolated
	vector<CRGBAF> col; // 32 bits value for each pixel of each layer.The layers are contiguous. (0.0f -> 1.0f)
	vector<uint8> ray;	// Raytrace composante
						// 0 - Ray passed
						// 1 - 254 - Ray blocked for one or more light
						// 255 - Ray passed through spot
	uint32 nNbLayerUsed;
	vector<CMesh::CFace*> faces;	

	// -----------------------------------------------------------------------
	// Interface
	// -----------------------------------------------------------------------

	SLMPlane ();

	void newLayer ();
	bool isAllBlack (uint8 nLayerNb);
	void copyColToBitmap8x2 (CBitmap* pImage, uint32 nLayerNb, CRGBAF refAmbient, CRGBAF refDiffuse);
	void copyColToBitmap32 (CBitmap* pImage, uint32 nLayerNb);
	void putIn (SLMPlane &Dst, bool bMaskOnly = false);
	bool testIn (SLMPlane &Dst);
	bool tryAllPosToPutIn (SLMPlane &Dst);
	void resize (uint32 nNewSizeX, uint32 nNewSizeY);
	void stretch (double osFactor);

	void createFromPlane (SLMPlane &Src);

	void copyFirstLayerTo (SLMPlane &Dst, uint8 nDstLayer);
	void contourDetect ();
	void andRayWidthMask ();

	void createFromFace (CMesh::CFace *pF);
	void createFromFaceGroup (vector<CMesh::CFace*>::iterator ItFace, uint32 nNbFace);

	CRGBAF getAverageColor (uint8 nLayerNb);
	bool isSameColorAs (uint8 nLayerNb, CRGBAF color, float precision);


	// -----------------------------------------------------------------------
	// Implementation
	// -----------------------------------------------------------------------

	bool isInTriangleOrEdge(double x, double y, double xt1, double yt1, 
							double xt2, double yt2, double xt3, double yt3);

	bool segmentIntersection(	double x1, double y1, double x2, double y2, 
								double x3, double y3, double x4, double y4);
};


#endif // NL_CALC_LM_PLANE_H

/* End of calc_lm_plane.h */

