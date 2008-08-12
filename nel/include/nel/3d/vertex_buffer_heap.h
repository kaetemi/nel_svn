/** \file vertex_buffer_heap.h
 * TODO: File description
 *
 * $Id: vertex_buffer_heap.h,v 1.6 2005/02/22 10:19:13 besson Exp $
 */

/* Copyright, 2000-2002 Nevrax Ltd.
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

#ifndef NL_VERTEX_BUFFER_HEAP_H
#define NL_VERTEX_BUFFER_HEAP_H

#include "nel/misc/types_nl.h"
#include "nel/misc/heap_memory.h"
#include "driver.h"


namespace NL3D 
{


// ***************************************************************************
/**
 * A vertex buffer used to group lot of static VB in it.
 *	Work with VBHard where available. 
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2002
 */
class CVertexBufferHeap
{
public:
	/// Constructor
	CVertexBufferHeap();
	~CVertexBufferHeap();

	/// \name Init/Setup
	// @{

	/// Create the vertex buffer heap. It use a VBHard if possible. else a std CVertexBuffer is used.
	void			init(IDriver *driver, uint vertexFormat, uint maxVertices);
	/// release the VB. init() can be called after this.
	void			release();

	/// false if any error at init, or if init() not called
	bool			enabled() const {return _Enabled;}
	/// return the driver used.
	IDriver			*getDriver() const {return _Driver;}
	/// get the vertexFormat
	uint			getVertexFormat() const {return _VertexFormat;}
	/// get the vertexSize
	uint			getVertexSize() const {return _VertexSize;}
	/// get max vertices the Buffer allows.
	uint			getMaxVertices() const {return _MaxVertices;}

	// @}

	/// \name Allocation.
	// @{

	/// allocate a subset of the VB. false if cannot (not enough space/too big).
	bool			allocate(uint numVertices, uint &indexStart);

	/// free a subset of the VB. nlstop if subset not found...
	void			free(uint indexStart);

	// @}

	/// \name Rendering. Those methods must be called only if enabled(), else crash
	// @{

	/// lock the VB, for future filling
	uint8			*lock(uint indexStart);
	/// unlock the VB. Mirror the CVertexBuffer::unlock(start, end) scheme.
	void			unlock(uint startVert, uint endVert);

	/// activate the VB/VBHard as the current VB in the driver, for future rendering
	void			activate();

	// @}

// ********************
private:
	NLMISC::CRefPtr<IDriver>			_Driver;
	CVertexBuffer						_VBSoft;
	NLMISC::CHeapMemory					_HeapManager;
	uint8								*_HeapStart;
	bool								_Enabled;
	bool								_HardMode;

	uint			_VertexFormat;
	uint			_VertexSize;
	uint			_MaxVertices;

};


} // NL3D


#endif // NL_VERTEX_BUFFER_HEAP_H

/* End of vertex_buffer_heap.h */
