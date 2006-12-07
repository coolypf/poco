//
// ServerSocket.h
//
// $Id: //poco/1.2/Net/include/Poco/Net/ServerSocket.h#1 $
//
// Library: Net
// Package: Sockets
// Module:  ServerSocket
//
// Definition of the ServerSocket class.
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


#ifndef Net_ServerSocket_INCLUDED
#define Net_ServerSocket_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/Socket.h"
#include "Poco/Net/StreamSocket.h"


namespace Poco {
namespace Net {


class Net_API ServerSocket: public Socket
	/// This class provides an interface to a
	/// TCP server socket.
{
public:
	ServerSocket();
		/// Creates a server socket.
		///
		/// The server socket must be bound to
		/// and address and put into listening state.

	ServerSocket(const Socket& socket);
		/// Creates the ServerSocket with the SocketImpl
		/// from another socket. The SocketImpl must be
		/// a ServerSocketImpl, otherwise an InvalidArgumentException
		/// will be thrown.

	ServerSocket(const SocketAddress& address, int backlog = 64);
		/// Creates a server socket, binds it
		/// to the given address and puts it in listening
		/// state.
		///
		/// After successful construction, the server socket
		/// is ready to accept connections.

	ServerSocket(Poco::UInt16 port, int backlog = 64);
		/// Creates a server socket, binds it
		/// to the given port and puts it in listening
		/// state.
		///
		/// After successful construction, the server socket
		/// is ready to accept connections.

	virtual ~ServerSocket();
		/// Destroys the StreamSocket.

	ServerSocket& operator = (const Socket& socket);
		/// Assignment operator.
		///
		/// Releases the socket's SocketImpl and
		/// attaches the SocketImpl from the other socket and
		/// increments the reference count of the SocketImpl.	

	virtual void bind(const SocketAddress& address, bool reuseAddress = false);
		/// Bind a local address to the socket.
		///
		/// This is usually only done when establishing a server
		/// socket. TCP clients should not bind a socket to a
		/// specific address.
		///
		/// If reuseAddress is true, sets the SO_REUSEADDR
		/// socket option.

	virtual void bind(Poco::UInt16 port, bool reuseAddress = false);
		/// Bind a local port to the socket.
		///
		/// This is usually only done when establishing a server
		/// socket. 
		///
		/// If reuseAddress is true, sets the SO_REUSEADDR
		/// socket option.
		
	virtual void listen(int backlog = 64);
		/// Puts the socket into listening state.
		///
		/// The socket becomes a passive socket that
		/// can accept incoming connection requests.
		///
		/// The backlog argument specifies the maximum
		/// number of connections that can be queued
		/// for this socket.

	virtual StreamSocket acceptConnection(SocketAddress& clientAddr);
		/// Get the next completed connection from the
		/// socket's completed connection queue.
		///
		/// If the queue is empty, waits until a connection
		/// request completes.
		///
		/// Returns a new TCP socket for the connection
		/// with the client.
		///
		/// The client socket's address is returned in clientAddr.

	virtual StreamSocket acceptConnection();
		/// Get the next completed connection from the
		/// socket's completed connection queue.
		///
		/// If the queue is empty, waits until a connection
		/// request completes.
		///
		/// Returns a new TCP socket for the connection
		/// with the client.

protected:
	ServerSocket(SocketImpl* pImpl, bool);
		/// The bool argument is to resolve an ambiguity with
		/// another constructor (Microsoft Visual C++ 2005)
};


} } // namespace Poco::Net


#endif // Net_ServerSocket_INCLUDED
