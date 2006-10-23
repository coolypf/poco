//
// SocketStream.h
//
// $Id: //poco/1.2/Net/include/Poco/Net/SocketStream.h#1 $
//
// Library: Net
// Package: Sockets
// Module:  SocketStream
//
// Definition of the SocketStream class.
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


#ifndef Net_SocketStream_INCLUDED
#define Net_SocketStream_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/BufferedBidirectionalStreamBuf.h"
#include <istream>
#include <ostream>


namespace Poco {
namespace Net {


class StreamSocketImpl;


class Net_API SocketStreamBuf: public Poco::BufferedBidirectionalStreamBuf
	/// This is the streambuf class used for reading from and writing to a socket.
{
public:
	SocketStreamBuf(const Socket& socket);
		/// Creates a SocketStreamBuf with the given socket.
		///
		/// The socket's SocketImpl must be a StreamSocketImpl,
		/// otherwise an InvalidArgumentException is thrown.

	~SocketStreamBuf();
		/// Destroys the SocketStreamBuf.
		
	StreamSocketImpl* socketImpl() const;
		/// Returns the internal SocketImpl.
	
protected:
	int readFromDevice(char* buffer, std::streamsize length);
	int writeToDevice(const char* buffer, std::streamsize length);

private:
	enum 
	{
		STREAM_BUFFER_SIZE = 1024
	};

	StreamSocketImpl* _pImpl;
};


class Net_API SocketIOS: public virtual std::ios
	/// The base class for SocketStream, SocketInputStream and
	/// SocketOutputStream.
	///
	/// This class is needed to ensure the correct initialization
	/// order of the stream buffer and base classes.
{
public:
	SocketIOS(const Socket& socket);
		/// Creates the SocketIOS with the given socket.
		///
		/// The socket's SocketImpl must be a StreamSocketImpl,
		/// otherwise an InvalidArgumentException is thrown.
		
	~SocketIOS();
		/// Destroys the SocketIOS.
		///
		/// Flushes the buffer, but does not close the socket.
		
	SocketStreamBuf* rdbuf();
		/// Returns a pointer to the internal SocketStreamBuf.
		
	void close();
		/// Flushes the stream and closes the socket.
		
	StreamSocket socket() const;
		/// Returns the underlying socket.

protected:
	SocketStreamBuf _buf;
};


class Net_API SocketOutputStream: public SocketIOS, public std::ostream
	/// An output stream for writing to a socket.
{
public:
	SocketOutputStream(const Socket& socket);
		/// Creates the SocketOutputStream with the given socket.
		///
		/// The socket's SocketImpl must be a StreamSocketImpl,
		/// otherwise an InvalidArgumentException is thrown.

	~SocketOutputStream();
		/// Destroys the SocketOutputStream.
		///
		/// Flushes the buffer, but does not close the socket.
};


class Net_API SocketInputStream: public SocketIOS, public std::istream
	/// An input stream for reading from a socket.
	///
	/// When using formatted input from a SocketInputStream,
	/// always ensure that a receive timeout is set for the
	/// socket. Otherwise your program might unexpectedly
	/// hang.
	///
	/// However, using formatted input from a SocketInputStream
	/// is not recommended, due to the read-ahead behavior of
	/// istream with formatted reads.
{
public:
	SocketInputStream(const Socket& socket);
		/// Creates the SocketInputStream with the given socket.
		///
		/// The socket's SocketImpl must be a StreamSocketImpl,
		/// otherwise an InvalidArgumentException is thrown.

	~SocketInputStream();
		/// Destroys the SocketInputStream.
};


class Net_API SocketStream: public SocketIOS, public std::iostream
	/// An bidirectional stream for reading from and writing to a socket.
	///
	/// When using formatted input from a SocketStream,
	/// always ensure that a receive timeout is set for the
	/// socket. Otherwise your program might unexpectedly
	/// hang.
	///
	/// However, using formatted input from a SocketStream
	/// is not recommended, due to the read-ahead behavior of
	/// istream with formatted reads.
{
public:
	SocketStream(const Socket& socket);
		/// Creates the SocketStream with the given socket.
		///
		/// The socket's SocketImpl must be a StreamSocketImpl,
		/// otherwise an InvalidArgumentException is thrown.

	~SocketStream();
		/// Destroys the SocketStream.
		///
		/// Flushes the buffer, but does not close the socket.
};


//
// inlines
//
inline StreamSocketImpl* SocketStreamBuf::socketImpl() const
{
	return _pImpl;
}


} } // namespace Poco::Net


#endif // Net_SocketStream_INCLUDED
