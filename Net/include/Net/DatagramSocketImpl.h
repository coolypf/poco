//
// DatagramSocketImpl.h
//
// $Id: //poco/1.1.0/Net/include/Net/DatagramSocketImpl.h#2 $
//
// Library: Net
// Package: Sockets
// Module:  DatagramSocketImpl
//
// Definition of the DatagramSocketImpl class.
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


#ifndef Net_DatagramSocketImpl_INCLUDED
#define Net_DatagramSocketImpl_INCLUDED


#ifndef Net_Net_INCLUDED
#include "Net/Net.h"
#endif
#ifndef Net_SocketImpl_INCLUDED
#include "Net/SocketImpl.h"
#endif


Net_BEGIN


class Net_API DatagramSocketImpl: public SocketImpl
	/// This class implements an UDP socket.
{
public:
	DatagramSocketImpl();
		/// Creates a StreamSocketImpl.
		///
		/// If the system supports IPv6, the socket will
		/// be an IPv6 socket. Otherwise, it will be
		/// an IPv4 socket.

	DatagramSocketImpl(IPAddress::Family family);
		/// Creates an unconnected datagram socket.
		///
		/// The socket will be created for the
		/// given address family.

	DatagramSocketImpl(poco_socket_t sockfd);
		/// Creates a StreamSocketImpl using the given native socket.
		
protected:
	void init(int af);
	
	~DatagramSocketImpl();
};


Net_END


#endif // Net_DatagramSocketImpl_INCLUDED
