/**
 * \file NeLDriver.cpp
 * \date November 2004
 * \author Matt Raykowski
 * \author Henri Kuuste
 */

/* Copyright, 2004 Werewolf
 *
 * This file is part of Werewolf.
 * Werewolf is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * Werewolf is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Werewolf; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#ifndef __NELDRIVER_H__
#define __NELDRIVER_H__

//
// NeL Includes
//
#include <nel/misc/value_smoother.h>

extern uint16 gScreenWidth;
extern uint16 gScreenHeight;

class NeLDriver {
public:
	NeLDriver(NL3D::UDriver *driver) { m_Driver=driver; }
	virtual ~NeLDriver() { ; }

	void init();
	void update();
	void render();

	double getFps();

	NL3D::UDriver		&getDriver() const;
	NL3D::UScene		&getScene() const; 
	NL3D::UTextContext	&getTextContext() const;

private:
	// 3D
	NL3D::UDriver				*m_Driver;
	NL3D::UTextContext			*m_TextContext;
	NL3D::UScene				*m_Scene;

	// TIME
	NLMISC::CValueSmootherTemplate<double> m_DeltaTimeSmooth;
	double m_DeltaTime;
	double m_FirstTime;
	double m_OldTime;
	double m_Time;
};


#endif // __NELDRIVER_H__

