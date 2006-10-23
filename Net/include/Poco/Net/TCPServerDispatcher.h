//
// TCPServerDispatcher.h
//
// $Id: //poco/1.2/Net/include/Poco/Net/TCPServerDispatcher.h#1 $
//
// Library: Net
// Package: TCPServer
// Module:  TCPServerDispatcher
//
// Definition of the TCPServerDispatcher class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
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


#ifndef Net_TCPServerDispatcher_INCLUDED
#define Net_TCPServerDispatcher_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Runnable.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Mutex.h"


namespace Poco {
namespace Net {


class TCPServerParams;
class TCPServerConnectionFactory;


class Net_API TCPServerDispatcher: public Poco::Runnable
	/// A helper class for TCPServer that dispatches
	/// connections to server connection threads.
{
public:
	TCPServerDispatcher(TCPServerConnectionFactory* pFactory, Poco::ThreadPool& threadPool, TCPServerParams* pParams);
		/// Creates the TCPServerDispatcher.
		///
		/// The dispatcher takes ownership of the TCPServerParams object.
		/// If no TCPServerParams object is supplied, the TCPServerDispatcher
		/// creates one.

	void duplicate();
		/// Increments the object's reference count.
		
	void release();
		/// Decrements the object's reference count
		/// and deletes the object if the count
		/// reaches zero.	

	void run();
		/// Runs the dispatcher.
		
	void enqueue(const StreamSocket& socket);
		/// Queues the given socket connection.

	void stop();
		/// Stops the dispatcher.
			
	int currentThreads() const;
		/// Returns the number of currently used threads.
		
	int totalConnections() const;
		/// Returns the total number of handled connections.
		
	int currentConnections() const;
		/// Returns the number of currently handled connections.	

	int maxConcurrentConnections() const;
		/// Returns the maximum number of concurrently handled connections.	
		
	int queuedConnections() const;
		/// Returns the number of queued connections.	
	
	int refusedConnections() const;
		/// Returns the number of refused connections.

	const TCPServerParams& params() const;
		/// Returns a const reference to the TCPServerParam object.

protected:
	~TCPServerDispatcher();
		/// Destroys the TCPServerDispatcher.

	void beginConnection();
		/// Updates the performance counters.
		
	void endConnection();
		/// Updates the performance counters.

private:
	TCPServerDispatcher();
	TCPServerDispatcher(const TCPServerDispatcher&);
	TCPServerDispatcher& operator = (const TCPServerDispatcher&);

	int _rc;
	TCPServerParams* _pParams;
	int  _currentThreads;
	int  _totalConnections;
	int  _currentConnections;
	int  _maxConcurrentConnections;
	int  _refusedConnections;
	bool _stopped;
	Poco::NotificationQueue     _queue;
	TCPServerConnectionFactory* _pConnectionFactory;
	Poco::ThreadPool&           _threadPool;
	mutable Poco::FastMutex     _mutex;
};


//
// inlines
//
inline const TCPServerParams& TCPServerDispatcher::params() const
{
	return *_pParams;
}


} } // namespace Poco::Net


#endif // Net_TCPServerDispatcher_INCLUDED
