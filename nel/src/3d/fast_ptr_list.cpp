/** \file fast_ptr_list.cpp
 * TODO: File description
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


#include "std3d.h"
#include "nel/3d/fast_ptr_list.h"

using namespace std;

namespace NL3D
{


// ***************************************************************************
void	CFastPtrListNode::unlink()
{
	// If linked to a list, remove me.
	if(_Owner)
	{
		_Owner->erase(this);
		nlassert(_Owner==NULL);
	}
}


// ***************************************************************************
CFastPtrListBase::~CFastPtrListBase()
{
	clear();
}


// ***************************************************************************
void			CFastPtrListBase::clear()
{
	while(size())
	{
		CFastPtrListNode *node= _Nodes[0];
		erase(node);
	}
}


// ***************************************************************************
void			CFastPtrListBase::insert(void *element, CFastPtrListNode *node)
{
	nlassert(element);
	nlassert(node);

	// if this node is already linked to me, no-op!
	if(node->_Owner==this)
		return;

	// first unlink the node from its older list if any.
	node->unlink();

	// then add the elements to the list, and update node info
	_Elements.push_back(element);
	_Nodes.push_back(node);
	node->_Owner= this;
	node->_IndexInOwner= _Nodes.size()-1;
}

// ***************************************************************************
void			CFastPtrListBase::erase(CFastPtrListNode *node)
{
	// not mine?
	if(node->_Owner!=this)
		return;

	// Take the indexes,
	uint	nodeIndex= node->_IndexInOwner;
	uint	lastIndex= _Nodes.size()-1;

	// swap the last element and the erased one.
	swap(_Elements[nodeIndex], _Elements[lastIndex]);
	swap(_Nodes[nodeIndex], _Nodes[lastIndex]);
	// change the swapped node index. NB: work also in the particular case nodeIndex==lastIndex
	_Nodes[nodeIndex]->_IndexInOwner= nodeIndex;
	// erase the last elements
	_Elements.pop_back();
	_Nodes.pop_back();

	// reset erased node.
	node->_Owner= NULL;
}


} // NL3D
