/** \file play_list_manager_user.cpp
 * TODO: File description
 *
 * $Id: play_list_manager_user.cpp,v 1.9 2005/02/22 10:19:11 besson Exp $
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

#include "nel/3d/play_list_manager_user.h"
#include "nel/misc/hierarchical_timer.h"

using namespace NLMISC;

namespace NL3D 
{


// ***************************************************************************
UPlayList	*CPlayListManagerUser::createPlayList(UAnimationSet	*animSet)
{
	if(!animSet)
		nlerror("createPlayList(): animSet==NULL");
	
	CPlayListUser	*pl= new CPlayListUser( safe_cast<CAnimationSetUser*>(animSet)->_AnimationSet );
	_PlayLists.insert(pl);

	_PlayListManager.addPlaylist(&pl->_PlayList, &pl->_ChannelMixer);

	return pl;
}


// ***************************************************************************
void		CPlayListManagerUser::deletePlayList(UPlayList *playList)
{
	CPlayListUser	*pl= safe_cast<CPlayListUser*>(playList);

	_PlayListManager.removePlaylist(&pl->_PlayList);
	_PlayLists.erase(pl, "deletePlayList(): bad playList");
}


// ***************************************************************************
void		CPlayListManagerUser::animate(TGlobalAnimationTime	time)
{
		H_AUTO( NL3D_Render_PlayListMgr_Animate );
	
	_PlayListManager.animate(time);
}


// ***************************************************************************
void		CPlayListManagerUser::setup(TGlobalAnimationTime	time)
{
	H_AUTO( NL3D_Render_PlayListMgr_Setup );
	
	_PlayListManager.setup(time);
}



} // NL3D
