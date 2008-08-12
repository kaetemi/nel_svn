/** \file pacs.cpp
 * pacs management
 *
 * $Id: pacs.cpp,v 1.8 2001/08/14 13:45:34 lecroart Exp $
 */

/* Copyright, 2001 Nevrax Ltd.
 *
 * This file is part of NEVRAX SNOWBALLS.
 * NEVRAX SNOWBALLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX SNOWBALLS is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX SNOWBALLS; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

//
// Includes
//

#include <vector>

#include <nel/pacs/u_retriever_bank.h>
#include <nel/pacs/u_global_retriever.h>
#include <nel/pacs/u_move_container.h>
#include <nel/pacs/u_move_primitive.h>

#include <nel/3d/u_scene.h>
#include <nel/3d/u_instance_group.h>
#include <nel/3d/u_visual_collision_manager.h>

#include <nel/3d/u_instance.h>

#include <nel/misc/vectord.h>

#include "client.h"
#include "landscape.h"
#include "pacs.h"
#include "entities.h"

//
// Namespaces
//

using namespace std;
using namespace NLMISC;
using namespace NL3D;
using namespace NLPACS;

//
// Variables
//

// The retriever bank used in the world
URetrieverBank				*RetrieverBank;
// The global retriever used for pacs
UGlobalRetriever			*GlobalRetriever;
// The move container used for dynamic collisions
UMoveContainer				*MoveContainer;

// The collision manager for ground snappping
UVisualCollisionManager		*VisualCollisionManager;

// The collision primitive for the instances in the landscape
vector<UMovePrimitive *>	InstancesMovePrimitives;

//
// Functions
//

void	initPACS()
{
	// init the global retriever and the retriever bank
	RetrieverBank = URetrieverBank::createRetrieverBank(ConfigFile.getVar("RetrieverBankName").asString().c_str());
	GlobalRetriever = UGlobalRetriever::createGlobalRetriever(ConfigFile.getVar("GlobalRetrieverName").asString().c_str(), RetrieverBank);

	// create the move primitive
	MoveContainer = UMoveContainer::createMoveContainer(GlobalRetriever, 100, 100, 6.0);

	// create a visual collision manager
	// this should not be in pacs, but this is too close to pacs to be put elsewhere
	VisualCollisionManager = Scene->createVisualCollisionManager();
	VisualCollisionManager->setLandscape(Landscape);

	// create a move primite for each instance in the instance group
	uint	i, j;
	for (j=0; j<InstanceGroups.size(); ++j)
	{
		for (i=0; i<InstanceGroups[j]->getNumInstance(); ++i)
		{
			UMovePrimitive	*primitive = MoveContainer->addCollisionablePrimitive(0, 1);
			primitive->setPrimitiveType(UMovePrimitive::_2DOrientedCylinder);
			primitive->setReactionType(UMovePrimitive::DoNothing);
			primitive->setTriggerType(UMovePrimitive::NotATrigger);
			primitive->setCollisionMask(OtherCollisionBit+SelfCollisionBit+SnowballCollisionBit);
			primitive->setOcclusionMask(StaticCollisionBit);
			primitive->setObstacle(true);

			// setup the radius of each mesh in the instance group
			string	name = InstanceGroups[j]->getShapeName(i);
			float rad;

			     if (strlwr(name) == "pi_po_igloo_a")		rad = 4.5f;
			else if (strlwr(name) == "pi_po_snowman_a")		rad = 1.0f;
			else if (strlwr(name) == "pi_po_pinetree_a")	rad = 2.0f;
			else if (strlwr(name) == "pi_po_tree_a")		rad = 2.0f;
			else if (strlwr(name) == "pi_po_pingoo_stat_a")	rad = 1.0f;
			else if (strlwr(name) == "pi_po_gnu_stat_a")	rad = 1.0f;
			else
			{
				rad = 2.0f;
				nlwarning ("Instance name '%s' doesn't have a good radius for collision", name.c_str());
			}

			primitive->setRadius(rad);
			primitive->setHeight(6.0f);

			primitive->insertInWorldImage(0);
			CVector	pos = InstanceGroups[j]->getInstancePos(i);
			primitive->setGlobalPosition(CVectorD(pos.x, pos.y, pos.z-1.5f), 0);
			InstancesMovePrimitives.push_back(primitive);
		}
	}
}

void	releasePACS()
{
	// create a move primite for each instance in the instance group
	uint	i;
	for (i=0; i<InstancesMovePrimitives.size(); ++i)
		MoveContainer->removePrimitive(InstancesMovePrimitives[i]);

	InstancesMovePrimitives.clear();

	// delete all allocated objects
	UGlobalRetriever::deleteGlobalRetriever(GlobalRetriever);
	URetrieverBank::deleteRetrieverBank(RetrieverBank);
	UMoveContainer::deleteMoveContainer(MoveContainer);

	// delete the visual collision manager
	Scene->deleteVisualCollisionManager(VisualCollisionManager);

}


