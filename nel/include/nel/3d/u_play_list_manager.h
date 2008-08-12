/** \file u_play_list_manager.h
 * TODO: File description
 *
 * $Id: u_play_list_manager.h,v 1.6 2005/02/22 10:14:13 besson Exp $
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

#ifndef NL_U_PLAY_LIST_MANAGER_H
#define NL_U_PLAY_LIST_MANAGER_H

#include "nel/misc/types_nl.h"
#include "animation_time.h"


namespace NL3D
{


class	UAnimationSet;
class	UPlayList;


// ***************************************************************************
/**
 * A manager of playlist.
 * \author Lionel Berenguier
 * \author Nevrax France
 * \date 2001
 */
class UPlayListManager
{
protected:

	/// Constructor
	UPlayListManager() {}
	/// dtor
	virtual	~UPlayListManager() {}

public:

	/** Create a playlist, instance of an animation set. nlerror if(animSet==NULL).
	 * \param animSet the UAnimationSet you want to instanciate into a UPlayList.
	 * \return the new created playlist.
	 */
	virtual	UPlayList	*createPlayList(UAnimationSet	*animSet) =0;
	/** Delete a playlist. nlerror if not found. no-op if playList==NULL.
	 * \param playList the playList you want to delete.
	 */
	virtual	void		deletePlayList(UPlayList *playList) =0;


	/** Animate all the playlist. Only the globals channels are animated.
	 * NB: all objects registered to the playLists (see registerTransform) are updated, BUT the detail channels 
	 * (like materials channels) which may be updated during UScene::render(), only if they are visibles...
	 *
	 * \param time the effective currentTime in second.
	 */
	virtual	void		animate (TGlobalAnimationTime time) =0;


	/** Setup all the playlist. Channels are not animated.
	 * NB: all objects registered to the playLists (see registerTransform) are updated.
	 *
	 * \param time the effective currentTime in second.
	 */
	virtual	void		setup (TGlobalAnimationTime time) =0;

};


} // NL3D


#endif // NL_U_PLAY_LIST_MANAGER_H

/* End of u_play_list_manager.h */
