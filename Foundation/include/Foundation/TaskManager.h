//
// TaskManager.h
//
// $Id: //poco/1.1.0/Foundation/include/Foundation/TaskManager.h#2 $
//
// Library: Foundation
// Package: Tasks
// Module:  Tasks
//
// Definition of the TaskManager class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_TaskManager_INCLUDED
#define Foundation_TaskManager_INCLUDED


#ifndef Foundation_Foundation_INCLUDED
#include "Foundation/Foundation.h"
#endif
#ifndef Foundation_Mutex_INCLUDED
#include "Foundation/Mutex.h"
#endif
#ifndef Foundation_Task_INCLUDED
#include "Foundation/Task.h"
#endif
#ifndef Foundation_AutoPtr_INCLUDED
#include "Foundation/AutoPtr.h"
#endif
#ifndef Foundation_NotificationCenter_INCLUDED
#include "Foundation/NotificationCenter.h"
#endif
#ifndef Foundation_Timestamp_INCLUDED
#include "Foundation/Timestamp.h"
#endif
#ifndef STD_LIST_INCLUDED
#include <list>
#define STD_LIST_INCLUDED
#endif


Foundation_BEGIN


class Notification;
class ThreadPool;
class Exception;


class Foundation_API TaskManager
	/// The TaskManager manages a collection of tasks
	/// and monitors their lifetime.
	///
	/// A TaskManager has a built-in NotificationCenter that
	/// is used to send out notifications on task progress
	/// and task states. See the TaskNotification class and its
	/// subclasses for the various events that result in a notification.
	/// To keep the number of notifications small, a TaskProgressNotification
	/// will only be sent out once in 100 milliseconds.
{
public:
	typedef AutoPtr<Task>      TaskPtr;
	typedef std::list<TaskPtr> TaskList;

	TaskManager();
		/// Creates the TaskManager, using the
		/// default ThreadPool.

	TaskManager(ThreadPool& pool);
		/// Creates the TaskManager, using the
		/// given ThreadPool.

	~TaskManager();
		/// Destroys the TaskManager.

	void start(Task* pTask);
		/// Starts the given task in a thread obtained
		/// from the thread pool.
		///
		/// The TaskManager takes ownership of the Task object
		/// and deletes it when it it finished.

	void cancelAll();
		/// Requests cancellation of all tasks.
		
	void joinAll();
		/// Waits for the completion of all the threads
		/// in the TaskManager's thread pool.

	TaskList taskList() const;
		/// Returns a copy of the internal task list.

	int count() const;
		/// Returns the number of tasks in the internal task list.

	void addObserver(const AbstractObserver& observer);
		/// Registers an observer with the NotificationCenter.
		/// Usage:
		///     Observer<MyClass, MyNotification> obs(*this, &MyClass::handleNotification);
		///     notificationCenter.addObserver(obs);

	void removeObserver(const AbstractObserver& observer);
		/// Unregisters an observer with the NotificationCenter.

	static const int MIN_PROGRESS_NOTIFICATION_INTERVAL;

protected:
	void postNotification(Notification* pNf);
	  /// Posts a notification to the task manager's 
	  /// notification center.

	void taskStarted(Task* pTask);
	void taskProgress(Task* pTask, float progress);
	void taskCancelled(Task* pTask);
	void taskFinished(Task* pTask);
	void taskFailed(Task* pTask, const Exception& exc);

private:
	ThreadPool&        _threadPool;
	TaskList           _taskList;
	Timestamp          _lastProgressNotification;
	NotificationCenter _nc;
	mutable FastMutex  _mutex;

	friend class Task;
};


//
// inlines
//
inline int TaskManager::count() const
{
	FastMutex::ScopedLock lock(_mutex);

	return (int) _taskList.size();
}


Foundation_END


#endif // Foundation_TaskManager_INCLUDED
