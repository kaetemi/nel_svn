
/** \file debug_vb.h
 */

/* Copyright, 2000-2004 Nevrax Ltd.
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

#ifndef NL_DEBUG_VB_H
#define NL_DEBUG_VB_H

// helper macro for debug
/// this macro is used to see whether a write in a vertex buffer is correct

#ifdef NL_DEBUG
	//#define NL_DEBUG_VB
#endif

#ifdef NL_DEBUG_VB

#define CHECK_VERTEX_BUFFER(vb, pt) nlCheckVertexBuffer((vb), (const uint8 *) (pt));
#define CHECK_VBA(vba, pt) nlCheckVBA((vba), (const uint8 *) (pt));
#define CHECK_VBA_RANGE(vba, ptStart, length) nlCheckVBARange((vba), (const uint8 *) (ptStart), (uint) (length));
#define CHECK_IBA_RANGE(iba, ptStart, length) nlCheckIBARange((iba), (const uint8 *) (ptStart), (uint) (length));
#define CHECK_IBA(iba, ptStart) nlCheckIBA((iba), (const uint8 *) (ptStart));

#else
	#define CHECK_VERTEX_BUFFER(a,b)
	#define CHECK_VBA(vbA, pt)
	#define CHECK_VBA_RANGE(vba, ptStart, length)
	#define CHECK_IBA_RANGE(iba, ptStart, length)
	#define CHECK_IBA(iba, ptStart)
#endif

namespace NL3D
{

class CVertexBuffer;
class CVertexBufferRead;
class CVertexBufferReadWrite;
class CIndexBufferRead;
class CIndexBufferReadWrite;

void nlCheckVertexBuffer(const CVertexBuffer &vb, const uint8 *ptr);
void nlCheckVBA(CVertexBufferRead &vbr, const uint8 *ptr);
void nlCheckVBA(CVertexBufferReadWrite &vbrw, const uint8 *ptr);
void nlCheckVBARange(CVertexBufferRead &vbr, const uint8 *ptStart, uint length);
void nlCheckVBARange(CVertexBufferReadWrite &vbrw, const uint8 *ptStart, uint length);
void nlCheckIBARange(CIndexBufferReadWrite &ibrw, const uint8 *ptStart, uint length);
void nlCheckIBARange(CIndexBufferRead &ibr, const uint8 *ptStart, uint length);
void nlCheckIBA(CIndexBufferReadWrite &ibrw, const uint8 *ptStart);
void nlCheckIBA(CIndexBufferRead &ibrw, const uint8 *ptStart);


} // NL3D

#endif
