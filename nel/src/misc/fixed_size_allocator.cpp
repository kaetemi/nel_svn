/** \file fixed_size_allocator.cpp
 */

/* Copyright, 2000, 2001, 2002, 2003 Nevrax Ltd.
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

#include "stdmisc.h"
#include "nel/misc/fixed_size_allocator.h"


namespace NLMISC
{

//*****************************************************************************************************************
CFixedSizeAllocator::CFixedSizeAllocator(uint numBytesPerBlock, uint numBlockPerChunk)
{
	_FreeSpace = NULL;
	_NumChunks = 0;
	nlassert(numBytesPerBlock > 1);
	_NumBytesPerBlock = numBytesPerBlock;
	_NumBlockPerChunk = std::max(numBlockPerChunk, (uint) 3);
	_NumAlloc = 0;
}

//*****************************************************************************************************************
CFixedSizeAllocator::~CFixedSizeAllocator()
{
	if (_NumAlloc != 0)
	{
		#ifdef NL_DEBUG
			nlwarning("%d blocks were not freed", (int) _NumAlloc);
		#endif
		return;
	}
	if (_NumChunks > 0)
	{
		nlassert(_NumChunks == 1);
		// delete the left chunk. This should force all the left nodes to be removed from the empty list
		delete _FreeSpace->Chunk;
	}
}

//*****************************************************************************************************************
void *CFixedSizeAllocator::alloc()
{
	if (!_FreeSpace)
	{
		CChunk *chunk = new CChunk; // link a new chunk to that object
		chunk->init(this);
	}
	++ _NumAlloc;
	return _FreeSpace->unlink();
}

//*****************************************************************************************************************
void CFixedSizeAllocator::free(void *block)
{
	if (!block) return;
	/// get the node from the object
	CNode *node = (CNode *) ((uint8 *) block - offsetof(CNode, Next));
	//
	nlassert(node->Chunk != NULL);
	nlassert(node->Chunk->Allocator == this);
	//
	--_NumAlloc;
	node->link();
}

//*****************************************************************************************************************
uint CFixedSizeAllocator::CChunk::getBlockSizeWithOverhead() const
{
	return std::max((uint)(sizeof(CNode) - offsetof(CNode, Next)),(uint)(Allocator->getNumBytesPerBlock())) + offsetof(CNode, Next);
}

//*****************************************************************************************************************
CFixedSizeAllocator::CChunk::CChunk()
{
	NumFreeObjs = 0;
	Allocator = NULL;
}

//*****************************************************************************************************************
CFixedSizeAllocator::CChunk::~CChunk()
{
	nlassert(Allocator != NULL);
	for (uint k = 0; k < Allocator->getNumBlockPerChunk(); ++k)
	{
		getNode(k).unlink();
	}
	nlassert(NumFreeObjs == 0);
	nlassert(Allocator->_NumChunks > 0);
	-- (Allocator->_NumChunks);
	delete Mem;
}

//*****************************************************************************************************************
void CFixedSizeAllocator::CChunk::init(CFixedSizeAllocator *alloc)
{
	nlassert(!Allocator);
	nlassert(alloc != NULL);
	Allocator = alloc;
	//
	Mem = new uint8[getBlockSizeWithOverhead() * alloc->getNumBlockPerChunk()];
	//
	getNode(0).Chunk = this;
	getNode(0).Next = &getNode(1);
	getNode(0).Prev = &alloc->_FreeSpace;
	//
	NumFreeObjs = alloc->getNumBlockPerChunk();
	/// init all the element as a linked list
	for (uint k = 1; k < (NumFreeObjs - 1); ++k)
	{
		getNode(k).Chunk = this;
		getNode(k).Next = &getNode(k + 1);
		getNode(k).Prev = &getNode(k - 1).Next;
	}

	getNode(NumFreeObjs - 1).Chunk = this;
	getNode(NumFreeObjs - 1).Next  = alloc->_FreeSpace;
	getNode(NumFreeObjs - 1).Prev = &(getNode(NumFreeObjs - 2).Next);

	if (alloc->_FreeSpace) { alloc->_FreeSpace->Prev = &getNode(NumFreeObjs - 1).Next; }
	alloc->_FreeSpace = &getNode(0);
	++(alloc->_NumChunks);
}

//*****************************************************************************************************************
CFixedSizeAllocator::CNode &CFixedSizeAllocator::CChunk::getNode(uint index)
{
	nlassert(Allocator != NULL);
	nlassert(index < Allocator->getNumBlockPerChunk());
	return *(CNode *) ((uint8 *) Mem + index * getBlockSizeWithOverhead());
}

//*****************************************************************************************************************
void CFixedSizeAllocator::CChunk::add()
{
	nlassert(Allocator);
	// a node of this chunk has been given back
	nlassert(NumFreeObjs < Allocator->getNumBlockPerChunk());
	++ NumFreeObjs;
	if (NumFreeObjs == Allocator->getNumBlockPerChunk()) // all objects back ?
	{
		if (Allocator->_NumChunks > 1) // we want to have at least one chunk left
		{
			delete this; // kill that object
		}
	}
}

//*****************************************************************************************************************
void CFixedSizeAllocator::CChunk::grab()
{
	// a node of this chunk has been given back
	nlassert(NumFreeObjs > 0);
	-- NumFreeObjs;
}

//*****************************************************************************************************************
void *CFixedSizeAllocator::CNode::unlink()
{
	nlassert(Prev != NULL);
	if (Next) { Next->Prev = Prev;}
	*Prev = Next;
	nlassert(Chunk->NumFreeObjs > 0);
	Chunk->grab(); // tells the containing chunk that a node has been allocated
	return (void *) &Next;
}

//*****************************************************************************************************************
void CFixedSizeAllocator::CNode::link()
{
	// destroy the obj to get back uninitialized memory
	nlassert(Chunk);
	nlassert(Chunk->Allocator);

	CNode *&head = Chunk->Allocator->_FreeSpace;
	Next = head;
	Prev = &head;
	if (Next)
	{
		nlassert(Next->Prev = &head);
		Next->Prev = &Next;
	}
	Chunk->Allocator->_FreeSpace = this;
	Chunk->add();
}

} // NLMISC
