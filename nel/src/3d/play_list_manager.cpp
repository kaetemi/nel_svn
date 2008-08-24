/** \file play_list_manager.cpp
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

#include "std3d.h"

#include "nel/3d/play_list_manager.h"


namespace NL3D
{


// ***************************************************************************
void	CPlayListManager::addPlaylist(CAnimationPlaylist* plist, CChannelMixer *chanMixer)
{
	nlassert(plist);
	if(!chanMixer)
		return;
	// this do all the good things.
	_List[plist]= CNode(plist, chanMixer);
}


// ***************************************************************************
void	CPlayListManager::removePlaylist(CAnimationPlaylist* plist)
{
	nlassert(plist);
	// this do all the good things.
	_List.erase(plist);
}


// ***************************************************************************
void	CPlayListManager::animate(TGlobalAnimationTime time)
{
	TPlayListList::iterator		it;

	for(it=_List.begin();it!=_List.end();)
	{
		CNode	*node= &(it->second);
		// Test refPtrs.
		if( node->PlayList==NULL || node->ChannelMixer==NULL)
		{
			// erase it from map.
			TPlayListList::iterator		itDel= it++;
			_List.erase(itDel);
		}
		else
		{
			// animate!!
			node->PlayList->setupMixer(*node->ChannelMixer, time);
			node->ChannelMixer->eval(false);
			it++;
		}
	}
}


// ***************************************************************************
void	CPlayListManager::setup(TGlobalAnimationTime time)
{
	TPlayListList::iterator		it;

	for(it=_List.begin();it!=_List.end();)
	{
		CNode	*node= &(it->second);
		// Test refPtrs.
		if( node->PlayList==NULL || node->ChannelMixer==NULL)
		{
			// erase it from map.
			TPlayListList::iterator		itDel= it++;
			_List.erase(itDel);
		}
		else
		{
			// animate!!
			node->PlayList->setupMixer(*node->ChannelMixer, time);
			it++;
		}
	}
}

// ***************************************************************************

void CPlayListManager::deleteAll()
{
	TPlayListList::iterator	it = _List.begin();
	while (it != _List.end())
	{
		TPlayListList::iterator itDel = it;
		++it;
		CNode *node= &(itDel->second);
		delete node->ChannelMixer;
		delete node->PlayList;
		_List.erase(itDel);
	}
	_List.clear();
}


} // NL3D
