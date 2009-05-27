/** \file graph.h
 * display graph
 *
 * $Id: graph.h,v 1.1 2003/01/24 13:54:06 lecroart Exp $
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

#ifndef GRAPH_H
#define GRAPH_H

// comment this define if you don't want 3d output
//#define USE_3D

#ifdef USE_3D

//
// Includes
//

#include <deque>
#include <string>


#include <nel/misc/rgba.h>
#include <nel/misc/time_nl.h>

#include <nel/3d/u_driver.h>
#include <nel/3d/u_text_context.h>

//
// External classes
//

class CGraph
{
public:
	std::string Name;
	float X, Y, Width, Height;
	NLMISC::CRGBA BackColor;
	float MaxValue;
	float Peak;

	std::deque<float> Values;

	NLMISC::TTime Quantum;

	NLMISC::TTime CurrentQuantumStart;

	CGraph (std::string name, float x, float y, float width, float height, NLMISC::CRGBA backColor, NLMISC::TTime quantum, float maxValue)
		: Name(name), X(x), Y(y), Width(width), Height(height), BackColor(backColor), Quantum(quantum),
		CurrentQuantumStart(NLMISC::CTime::getLocalTime()), MaxValue(maxValue), Peak(0.0f)
	{
		if (_Graphs == NULL)
		{
			_Graphs = new std::vector<CGraph*>;
		}

		_Graphs->push_back (this);
	}

	void addOneValue (float value = 0.0f);
	void addValue (float value);

	static void render (NL3D::UDriver &driver, NL3D::UTextContext &tc);

	static bool Display;
	static bool DisplayAverageValue;

private:

	static std::vector<CGraph*> *_Graphs;

	void render (NL3D::UDriver *Driver, NL3D::UTextContext *TextContext);
};

#endif

#endif // GRAPH_H

/* End of graph.h */
