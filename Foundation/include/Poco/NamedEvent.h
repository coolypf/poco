//
// NamedEvent.h
//
// $Id: //poco/1.2/Foundation/include/Poco/NamedEvent.h#1 $
//
// Library: Foundation
// Package: Processes
// Module:  NamedEvent
//
// Definition of the NamedEvent class.
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


#ifndef Foundation_NamedEvent_INCLUDED
#define Foundation_NamedEvent_INCLUDED


#include "Poco/Foundation.h"


#if defined(POCO_OS_FAMILY_WINDOWS) && defined(POCO_WIN32_UTF8)
#include "Poco/NamedEvent_WIN32U.h"
#elif defined(POCO_OS_FAMILY_WINDOWS)
#include "Poco/NamedEvent_WIN32.h"
#elif defined(POCO_OS_FAMILY_UNIX)
#include "Poco/NamedEvent_UNIX.h"
#else
#include "Poco/NamedEvent_VMS.h"
#endif


namespace Poco {


class Foundation_API NamedEvent: public NamedEventImpl
	/// An NamedEvent is a global synchronization object 
	/// that allows one process or thread to signal an
	/// other process or thread that a certain event
	/// has happened.
	///
	/// Unlike an Event, which itself is the unit of synchronization,
	/// a NamedEvent refers to a named operating system resource being the
	/// unit of synchronization.
	/// In other words, there can be multiple instances of NamedEvent referring
	/// to the same actual synchronization object.
	///
	/// NamedEvents are always autoresetting.
	///
	/// There should not be more than one instance of NamedEvent for
	/// a given name in a process. Otherwise, the instances may
	/// interfere with each other.
{
public:
	NamedEvent(const std::string& name);
		/// Creates the event.
		
	~NamedEvent();
		/// Destroys the event.

	void set();
		/// Signals the event. 
		/// The one thread or process waiting for the event 
		/// can resume execution.

	void wait();
		/// Waits for the event to become signalled.

private:
	NamedEvent();
	NamedEvent(const NamedEvent&);
	NamedEvent& operator = (const NamedEvent&);
};


//
// inlines
//
inline void NamedEvent::set()
{
	setImpl();
}


inline void NamedEvent::wait()
{
	waitImpl();
}


} // namespace Poco


#endif // Foundation_NamedEvent_INCLUDED
