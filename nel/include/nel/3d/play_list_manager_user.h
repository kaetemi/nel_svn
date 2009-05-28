/** \file play_list_manager_user.h
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

#ifndef NL_PLAY_LIST_MANAGER_USER_H
#define NL_PLAY_LIST_MANAGER_USER_H

#include "nel/misc/types_nl.h"
#include "nel/3d/u_play_list_manager.h"
#include "nel/3d/play_list_manager.h"
#include "nel/3d/play_list_user.h"
#include "nel/3d/animation_set_user.h"
#include "nel/3d/ptr_set.h"


namespace NL3D
{


// ***************************************************************************
/**
 * UPlayListManager implementation
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class CPlayListManagerUser : public UPlayListManager
{
private:
	CPlayListManager		_PlayListManager;
	CPtrSet<CPlayListUser>	_PlayLists;


public:

	/// Constructor
	CPlayListManagerUser()
	{
	}


	/** Create a playlist, instance of an animation set. nlerror if(animSet==NULL).
	 */
	virtual	UPlayList	*createPlayList(UAnimationSet	*animSet);
	/** Delete a playlist. nlerror if not found. no-op if playList==NULL.
	 */
	virtual	void		deletePlayList(UPlayList *playList);


	/** Animate all the playlist. Only the globals channels are animated.
	 * NB: all AnimationTime are in second.
	 */
	virtual	void		animate(TGlobalAnimationTime	time);


	/** Setup all the playlist.
	 * NB: all AnimationTime are in second.
	 */
	virtual	void		setup(TGlobalAnimationTime	time);

};


} // NL3D


#endif // NL_PLAY_LIST_MANAGER_USER_H

/* End of play_list_manager_user.h */
