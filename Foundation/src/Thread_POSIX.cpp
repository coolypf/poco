//
// Thread_POSIX.cpp
//
// $Id: //poco/1.1.0/Foundation/src/Thread_POSIX.cpp#2 $
//
// Library: Foundation
// Package: Threading
// Module:  Thread
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


#include "Foundation/Thread_POSIX.h"
#include "Foundation/Exception.h"
#include "Foundation/ErrorHandler.h"
#include <signal.h>


//
// Block SIGPIPE in main thread.
//
#if defined(POCO_OS_FAMILY_UNIX)
namespace
{
	class SignalBlocker
	{
	public:
		SignalBlocker()
		{
			sigset_t sset;
			sigemptyset(&sset);
			sigaddset(&sset, SIGPIPE); 
			pthread_sigmask(SIG_BLOCK, &sset, 0);
		}
		~SignalBlocker()
		{
		}
	};
	
	static SignalBlocker signalBlocker;
}
#endif


Foundation_BEGIN


pthread_key_t ThreadImpl::_currentKey;
bool ThreadImpl::_haveCurrentKey = false;


ThreadImpl::ThreadImpl(): 
	_pTarget(0), 
	_thread(0), 
	_prio(PRIO_NORMAL_IMPL)
{
	if (!_haveCurrentKey)
	{
		if (pthread_key_create(&_currentKey, NULL))
			throw SystemException("cannot allocate thread context key");
		_haveCurrentKey = true;
	}
}

			
ThreadImpl::~ThreadImpl()
{
	if (_pTarget)
		pthread_detach(_thread);
}


void ThreadImpl::setPriorityImpl(int prio)
{
	if (prio != _prio)
	{
		_prio = prio;
		if (_pTarget)
		{
			struct sched_param par;
			par.sched_priority = mapPrio(_prio);
			if (pthread_setschedparam(_thread, SCHED_OTHER, &par))
				throw SystemException("cannot set thread priority");
		}
	}
}


void ThreadImpl::startImpl(Runnable& target)
{
	if (_pTarget) throw SystemException("thread already running");

	_pTarget = &target;
	if (pthread_create(&_thread, NULL, entry, this))
	{
		_pTarget = 0;
		throw SystemException("cannot start thread");
	}

	if (_prio != PRIO_NORMAL_IMPL)
	{
		struct sched_param par;
		par.sched_priority = mapPrio(_prio);
		if (pthread_setschedparam(_thread, SCHED_OTHER, &par))
			throw SystemException("cannot set thread priority");
	}
}


void ThreadImpl::joinImpl()
{
	if (!_pTarget) return;
	void* result;
	if (pthread_join(_thread, &result))
		throw SystemException("cannot join thread"); 
	_pTarget = 0;
}


bool ThreadImpl::isRunningImpl() const
{
	return _pTarget != 0;
}


ThreadImpl* ThreadImpl::currentImpl()
{
	if (_haveCurrentKey)
		return (ThreadImpl*) pthread_getspecific(_currentKey);
	else
		return 0;
}


void* ThreadImpl::entry(void* pThread)
{
	pthread_setspecific(_currentKey, pThread);

#if defined(POCO_OS_FAMILY_UNIX)
	sigset_t sset;
	sigemptyset(&sset);
	sigaddset(&sset, SIGQUIT);
	sigaddset(&sset, SIGTERM);
	sigaddset(&sset, SIGPIPE); 
	pthread_sigmask(SIG_BLOCK, &sset, 0);
#endif

	try
	{
		reinterpret_cast<ThreadImpl*>(pThread)->_pTarget->run();
	}
	catch (Exception& exc)
	{
		ErrorHandler::handle(exc);
	}
	catch (std::exception& exc)
	{
		ErrorHandler::handle(exc);
	}
	catch (...)
	{
		ErrorHandler::handle();
	}
	return 0;
}


int ThreadImpl::mapPrio(int prio)
{
#if defined(__VMS) || defined(__digital__)
	static const int pmin = PRI_OTHER_MIN;
	static const int pmax = PRI_OTHER_MAX;
#else
	static const int pmin = sched_get_priority_min(SCHED_OTHER);
	static const int pmax = sched_get_priority_max(SCHED_OTHER);
#endif

	switch (prio)
	{
	case PRIO_LOWEST_IMPL:
		return pmin;
	case PRIO_LOW_IMPL:
		return pmin + (pmax - pmin)/4;
	case PRIO_NORMAL_IMPL:
		return pmin + (pmax - pmin)/2;
	case PRIO_HIGH_IMPL:
		return pmin + 3*(pmax - pmin)/4;
	case PRIO_HIGHEST_IMPL:
		return pmax;
	default:
		poco_bugcheck_msg("invalid thread priority");
	}
	return -1; // just to satisfy compiler - we'll never get here anyway
}


Foundation_END
