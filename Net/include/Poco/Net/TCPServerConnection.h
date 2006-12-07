//
// TCPServerConnection.h
//
// $Id: //poco/1.2/Net/include/Poco/Net/TCPServerConnection.h#1 $
//
// Library: Net
// Package: TCPServer
// Module:  TCPServerConnection
//
// Definition of the TCPServerConnection class.
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


#ifndef Net_TCPServerConnection_INCLUDED
#define Net_TCPServerConnection_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Runnable.h"


namespace Poco {
namespace Net {


class Net_API TCPServerConnection: public Poco::Runnable
	/// The abstract base class for TCP server connections
	/// created by TCPServer.
	///
	/// Derived classes must override the run() method
	/// (inherited from Runnable). Furthermore, a
	/// TCPServerConnectionFactory must be provided for the subclass.
	///
	/// The run() method must perform the complete handling
	/// of the client connection. As soon as the run() method
	/// returns, the server connection object is destroyed and
	/// the connection is automatically closed.
	///
	/// A new TCPServerConnection object will be created for
	/// each new client connection that is accepted by
	/// TCPServer.
{
public:
	TCPServerConnection(const StreamSocket& socket);
		/// Creates the TCPServerConnection using the given
		/// stream socket.

	virtual ~TCPServerConnection();
		/// Destroys the TCPServerConnection.

protected:
	StreamSocket& socket();
		/// Returns a reference to the underlying socket.

	void start();
		/// Calls run() and catches any exceptions that
		/// might be thrown by run().

private:
	TCPServerConnection();
	TCPServerConnection(const TCPServerConnection&);
	TCPServerConnection& operator = (const TCPServerConnection&);
	
	StreamSocket _socket;
	
	friend class TCPServerDispatcher;
};


//
// inlines
//
inline StreamSocket& TCPServerConnection::socket()
{
	return _socket;
}


} } // namespace Poco::Net


#endif // Net_TCPServerConnection_INCLUDED
