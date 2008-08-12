/** \file task_manager.h
 * Manage a list of task in a separate thread
 *
 * $Id: task_manager.h,v 1.16 2006/05/31 12:03:13 boucher Exp $
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

#ifndef NL_TASK_MANAGER_H
#define NL_TASK_MANAGER_H

#include "types_nl.h"
#include "vector.h"

#include <list>

#include "mutex.h"
#include "thread.h"

namespace NLMISC {


/**
 * A class derived from IRunnable to get a position
 */
class IRunnablePos : public NLMISC::IRunnable
{
public:
	NLMISC::CVector	Position;
};

/**
 * CTaskManager is a class that manage a list of Task with one Thread
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2000
 */
class CTaskManager : public IRunnable
{
public:

	/// Constructor
	CTaskManager();

	/// Destructeur
	~CTaskManager();

	/// Manage TaskQueue
	void run(void);

	/// Add a task to TaskManager and its priority
	void addTask(IRunnable *, float priority=0);

	/// Delete a task, only if task is not running, return true if found and deleted
	bool deleteTask(IRunnable *r);

	/// Sleep a Task
	void sleepTask(void) { nlSleep(10); }

	/// Task list size
	uint taskListSize(void); 

	/// return false if exit() is required. task added with addTask() should test this flag.
	bool	isThreadRunning() const {return _ThreadRunning;}

	/// Dump task list
	void	dump (std::vector<std::string> &result);
	
	/// Clear the dump of Done files
	void	clearDump();

	/// Get number of waiting task
	uint	getNumWaitingTasks();
	
	/// Is there a current task ?
	bool	isTaskRunning() const {return _IsTaskRunning;}
	
	/// A callback to modify the task priority
	class IChangeTaskPriority
	{
	public:
		virtual float getTaskPriority(const IRunnable &runable) = 0;
	};

	/// Register task priority callback
	void	registerTaskPriorityCallback (IChangeTaskPriority *callback);

private:

	/// Register task priority callback
	void	changeTaskPriority ();
	
	/// The callback
	IChangeTaskPriority		*_ChangePriorityCallback;

protected:
	
	/** If any, wait the current running task to complete
	 *	this function MUST be called in a 'accessor to the _TaskQueue' statement because a mutex is required
	 *	eg:
	 *	\code
	 *	{
	 *		CSynchronized<list<IRunnable *> >::CAccessor acces(&_TaskQueue);
	 *		waitCurrentTaskToComplete();
	 *	}
	 *	\endcode
	 */
	void	waitCurrentTaskToComplete ();

protected:

	// A task in the waiting queue with its parameters
	class CWaitingTask
	{
	public:
		CWaitingTask (IRunnable *task, float priority)
		{
			Task = task;
			Priority = priority;
		}
		IRunnable		*Task;
		float			Priority;

		// For the sort
		bool			operator< (const CWaitingTask &other) const
		{
			return Priority < other.Priority;
		}
	};

	/// queue of tasks, using list container instead of queue for DeleteTask methode
	CSynchronized<std::string>				_RunningTask;
	CSynchronized<std::list<CWaitingTask> >	_TaskQueue;
	CSynchronized<std::deque<std::string> >	_DoneTaskQueue;
	
	/// thread pointer
	IThread *_Thread;

	/// flag indicate thread loop, if false cause thread exit
	volatile	bool _ThreadRunning;

private:

	volatile	bool _IsTaskRunning;

};


} // NLMISC


#endif // NL_TASK_MANAGER_H

/* End of task_manager.h */
