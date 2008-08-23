/** \file landscapevb_info.h
 * TODO: File description
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

#ifndef NL_LANDSCAPEVB_INFO_H
#define NL_LANDSCAPEVB_INFO_H

#include "nel/misc/types_nl.h"
#include "nel/3d/vertex_buffer.h"


namespace NL3D 
{


class	CVertexBuffer;


// ***************************************************************************
/// Info for the current Far VertexBuffer setuped (iether normal or hard).
class	CFarVertexBufferInfo
{
public:
	CVertexBufferReadWrite	Accessor;
	uint32		VertexFormat;
	uint32		VertexSize;
	uint32		NumVertices;
	void		*VertexCoordPointer;
	void		*TexCoordPointer0;
	void		*TexCoordPointer1;
	void		*ColorPointer;
	uint32		TexCoordOff0;
	uint32		TexCoordOff1;
	uint32		ColorOff;

	// VertexProgram Only.
	void		*GeomInfoPointer;
	void		*DeltaPosPointer;
	void		*AlphaInfoPointer;
	uint32		GeomInfoOff;
	uint32		DeltaPosOff;
	uint32		AlphaInfoOff;


	void		setupVertexBuffer(CVertexBuffer &vb, bool forVertexProgram);
	void		setupNullPointers();

private:
	void		setupPointersForVertexProgram();
};


// ***************************************************************************
/// Info for the current Far VertexBuffer setuped (iether normal or hard).
class	CNearVertexBufferInfo
{
public:
	CVertexBufferReadWrite	Accessor;
	uint32		VertexFormat;
	uint32		VertexSize;
	uint32		NumVertices;
	void		*VertexCoordPointer;
	void		*TexCoordPointer0;
	void		*TexCoordPointer1;
	void		*TexCoordPointer2;
	uint32		TexCoordOff0;
	uint32		TexCoordOff1;
	uint32		TexCoordOff2;


	// VertexProgram Only.
	void		*GeomInfoPointer;
	void		*DeltaPosPointer;
	uint32		GeomInfoOff;
	uint32		DeltaPosOff;


	void		setupVertexBuffer(CVertexBuffer &vb, bool forVertexProgram);
	void		setupNullPointers();

private:
	void		setupPointersForVertexProgram();
};



} // NL3D


#endif // NL_LANDSCAPEVB_INFO_H

/* End of landscapevb_info.h */
