/** \file progress.h
 * TODO: File description
 *
 * $Id: progress.h,v 1.2 2004/11/15 10:25:09 lecroart Exp $
 */

/* Copyright, 2000 Nevrax Ltd.
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

#ifndef __PROGRESS__H
#define __PROGRESS__H

#include <string>
#include "../nel_mesh_lib/export_nel.h"


// ---------------------------------------------------------------------------

class CProgressBar : public IProgress
{
	
public:

	bool bCancelCalculation;
	float rRatioCalculated;
	double rTimeBegin;
	uint32 nNbTotalMeshes;
	std::string sInfoProgress[14];
	HWND hWndProgress;

public:

	CProgressBar();
	~CProgressBar();

	void initProgressBar (sint32 nNbMesh, Interface &ip);
	void uninitProgressBar();
	void updateProgressBar( sint32 NMeshNb );
	bool isCanceledProgressBar();

	// Interface implemenation
	virtual void setLine (uint32 LineNumber, std::string &LineText);
	virtual void update();
};

// ---------------------------------------------------------------------------



#endif