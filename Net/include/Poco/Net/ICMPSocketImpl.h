//
// ICMPSocketImpl.h
//
// $Id: //poco/1.2/Net/include/Poco/Net/ICMPSocketImpl.h#1 $
//
// Library: Net
// Package: ICMP
// Module:  ICMPSocketImpl
//
// Definition of the ICMPSocketImpl class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#ifndef Net_ICMPSocketImpl_INCLUDED
#define Net_ICMPSocketImpl_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/RawSocketImpl.h"
#include "Poco/Net/ICMPPacket.h"
#include "Poco/Timestamp.h"


namespace Poco {
namespace Net {


class Net_API ICMPSocketImpl: public RawSocketImpl
	/// This class implements an ICMP socket.
{
public:
	ICMPSocketImpl(IPAddress::Family family, int dataSize, int ttl, int timeout);
		/// Creates an unconnected ICMP socket.
		///
		/// The socket will be created for the given address family.

	int sendTo(const void*, int, const SocketAddress& address, int flags = 0);
		/// Sends an ICMP request through the socket to the given address.
		///
		/// Returns the number of bytes sent.
	
	int receiveFrom(void*, int, SocketAddress& address, int flags = 0);
		/// Receives data from the socket.
		/// Stores the address of the sender in address.
		///
		/// Returns the time elapsed since the originating request was sent.

protected:
	~ICMPSocketImpl();

private:
	ICMPPacket _icmpPacket;
};


} } // namespace Poco::Net


#endif // Net_ICMPSocketImpl_INCLUDED
