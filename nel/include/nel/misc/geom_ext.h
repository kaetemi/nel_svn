/** \file geom_ext.h
 * Set of extension of triangles (triangle with uv, color, uvcolor etc...)
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

#ifndef NL_TRIANGLE_EXT_H
#define NL_TRIANGLE_EXT_H

#include "types_nl.h"
#include "line.h"
#include "triangle.h"
#include "quad.h"
#include "uv.h"
#include "rgba.h"


namespace NLMISC
{

// ***************************************************************************
// ***************************************************************************
// Lines.
// ***************************************************************************
// ***************************************************************************


// ***************************************************************************
/**
 * A line with 2 color.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CLineColor : public CLine
{
public:
	CRGBA	Color0, Color1;

public:

	/// Constructor
	CLineColor() {}

	CLineColor		&operator=(const CLine &line)
	{
		*((CLine*)this)= line;
		return *this;
	}

};


// ***************************************************************************
/**
 * A line with 2 uvs.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CLineUV : public CLine
{
public:
	CUV		Uv0, Uv1;

public:

	/// Constructor
	CLineUV() {}

	CLineUV		&operator=(const CLine &line)
	{
		*((CLine*)this)= line;
		return *this;
	}

};


// ***************************************************************************
/**
 * A line with 2 color and 2 uvs.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CLineColorUV : public CLine
{
public:
	CRGBA	Color0, Color1;
	CUV		Uv0, Uv1;

public:

	/// Constructor
	CLineColorUV() {}

	CLineColorUV		&operator=(const CLine &line)
	{
		*((CLine*)this)= line;
		return *this;
	}

};


// ***************************************************************************
// ***************************************************************************
// Triangles.
// ***************************************************************************
// ***************************************************************************



// ***************************************************************************
/**
 * A triangle with 3 color.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CTriangleColor : public CTriangle
{
public:
	CRGBA	Color0, Color1, Color2;

public:

	/// Constructor
	CTriangleColor() {}

	CTriangleColor		&operator=(const CTriangle &tri)
	{
		*((CTriangle*)this)= tri;
		return *this;
	}

};


// ***************************************************************************
/**
 * A triangle with 3 uvs.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CTriangleUV : public CTriangle
{
public:
	CUV		Uv0, Uv1, Uv2;

public:

	/// Constructor
	CTriangleUV() {}

	CTriangleUV		&operator=(const CTriangle &tri)
	{
		*((CTriangle*)this)= tri;
		return *this;
	}

};


// ***************************************************************************
/**
 * A triangle with 3 color and 3 uvs.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CTriangleColorUV : public CTriangle
{
public:
	CRGBA	Color0, Color1, Color2;
	CUV		Uv0, Uv1, Uv2;

public:

	/// Constructor
	CTriangleColorUV() {}

	CTriangleColorUV		&operator=(const CTriangle &tri)
	{
		*((CTriangle*)this)= tri;
		return *this;
	}

};


// ***************************************************************************
// ***************************************************************************
// Quads.
// ***************************************************************************
// ***************************************************************************


// ***************************************************************************
/**
 * A quad with 4 color.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CQuadColor : public CQuad
{
public:
	CRGBA	Color0, Color1, Color2, Color3;

public:

	/// Constructor
	CQuadColor() {}

	CQuadColor		&operator=(const CQuad &quad)
	{
		*((CQuad*)this)= quad;
		return *this;
	}

};


// ***************************************************************************
/**
 * A quad with 4 uvs.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CQuadUV : public CQuad
{
public:
	CUV		Uv0, Uv1, Uv2, Uv3;

public:

	/// Constructor
	CQuadUV() {}

	CQuadUV		&operator=(const CQuad &quad)
	{
		*((CQuad*)this)= quad;
		return *this;
	}

};


// ***************************************************************************
/**
 * A quad with 4 color and 4 uvs.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CQuadColorUV : public CQuad
{
public:
	CRGBA	Color0, Color1, Color2, Color3;
	CUV		Uv0, Uv1, Uv2, Uv3;

public:

	/// Constructor
	CQuadColorUV() {}

	CQuadColorUV		&operator=(const CQuad &quad)
	{
		*((CQuad*)this)= quad;
		return *this;
	}

};


// ***************************************************************************
/**
 * A quad with 4 color and 8 uvs.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2000
 */
class CQuadColorUV2 : public CQuadColorUV
{
public:
	CUV		Uv02, Uv12, Uv22, Uv32;
};


} // NLMISC


#endif // NL_TRIANGLE_EXT_H

/* End of triangle_ext.h */
