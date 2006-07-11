//
// HTTPTestServer.h
//
// $Id: //poco/1.1.0/Net/testsuite/src/HTTPTestServer.h#2 $
//
// Definition of the HTTPTestServer class.
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


#ifndef HTTPTestServer_INCLUDED
#define HTTPTestServer_INCLUDED


#ifndef Net_Net_INCLUDED
#include "Net/Net.h"
#endif
#ifndef Net_ServerSocket_INCLUDED
#include "Net/ServerSocket.h"
#endif
#ifndef Net_Foundation_Thread_INCLUDED
#include "Foundation/Thread.h"
#endif
#ifndef Net_Foundation_Event_INCLUDED
#include "Foundation/Event.h"
#endif


class HTTPTestServer: public Foundation::Runnable
	/// A simple sequential echo server.
{
public:
	HTTPTestServer();
		/// Creates the HTTPTestServer.

	~HTTPTestServer();
		/// Destroys the HTTPTestServer.

	Foundation::UInt16 port() const;
		/// Returns the port the echo server is
		/// listening on.
		
	void run();
		/// Does the work.
		
	const std::string& lastRequest() const;
		/// Returns the last request.

	static const std::string SMALL_BODY;
	static const std::string LARGE_BODY;	

protected:
	bool requestComplete() const;
	std::string handleRequest() const;

private:
	Net::ServerSocket  _socket;
	Foundation::Thread _thread;
	Foundation::Event  _ready;
	bool               _stop;
	std::string        _lastRequest;
};


#endif // HTTPTestServer_INCLUDED
