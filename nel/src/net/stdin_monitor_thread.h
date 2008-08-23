/** \file stdin_monitor_thread.h
 *
 * interface for a class used by IService to create a monitor thread for stdin,
 * allowing ICommand commands to be executed in response to console input
 */

/* Copyright, 2000 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */


#ifndef NL_STDIN_MONITOR_THREAD_H
#define NL_STDIN_MONITOR_THREAD_H

namespace NLNET
{
	//-----------------------------------------------------------------------------
	// class IStdinMonitorSingleton
	//-----------------------------------------------------------------------------

	class IStdinMonitorSingleton
	{
	public:
		// static for getting hold of the singleton instance
		static IStdinMonitorSingleton* getInstance();

		// methods required by IStdinMonitorSingleton
		virtual void init()=0;
		virtual void update()=0;
		virtual void release()=0;

		// virtual destructor
		virtual ~IStdinMonitorSingleton() { }
	};

} // NLMISC

#endif
