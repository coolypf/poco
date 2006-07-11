//
// HTTPFixedLengthStream.h
//
// $Id: //poco/1.1.0/Net/include/Net/HTTPFixedLengthStream.h#2 $
//
// Library: Net
// Package: HTTP
// Module:  HTTPFixedLengthStream
//
// Definition of the HTTPFixedLengthStream class.
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


#ifndef Net_HTTPFixedLengthStream_INCLUDED
#define Net_HTTPFixedLengthStream_INCLUDED


#ifndef Net_Net_INCLUDED
#include "Net/Net.h"
#endif
#ifndef Net_HTTPBasicStreamBuf_INCLUDED
#include "Net/HTTPBasicStreamBuf.h"
#endif
#ifndef STD_ISTREAM_INCLUDED
#include <istream>
#define STD_ISTREAM_INCLUDED
#endif
#ifndef STD_OSTREAM_INCLUDED
#include <ostream>
#define STD_OSTREAM_INCLUDED
#endif


Net_BEGIN


class HTTPSession;


class Net_API HTTPFixedLengthStreamBuf: public HTTPBasicStreamBuf
	/// This is the streambuf class used for reading and writing fixed-size
	/// HTTP message bodies.
	///
	/// At most a given number of bytes are read or written.
{
public:
	typedef HTTPBasicStreamBuf::openmode openmode;

	HTTPFixedLengthStreamBuf(HTTPSession& session, std::streamsize length, openmode mode);
	~HTTPFixedLengthStreamBuf();
	
protected:
	int readFromDevice(char* buffer, std::streamsize length);
	int writeToDevice(const char* buffer, std::streamsize length);

private:
	HTTPSession&    _session;
	std::streamsize _length;
	std::streamsize _count;
};


class Net_API HTTPFixedLengthIOS: public virtual std::ios
	/// The base class for HTTPFixedLengthInputStream.
{
public:
	HTTPFixedLengthIOS(HTTPSession& session, std::streamsize length, HTTPFixedLengthStreamBuf::openmode mode);
	~HTTPFixedLengthIOS();
	HTTPFixedLengthStreamBuf* rdbuf();

protected:
	HTTPFixedLengthStreamBuf _buf;
};


class Net_API HTTPFixedLengthInputStream: public HTTPFixedLengthIOS, public std::istream
	/// This class is for internal use by HTTPSession only.
{
public:
	HTTPFixedLengthInputStream(HTTPSession& session, std::streamsize length);
	~HTTPFixedLengthInputStream();
	
	void* operator new(size_t size);
	void operator delete(void* ptr);
	
private:
	static Foundation::MemoryPool _pool;
};


class Net_API HTTPFixedLengthOutputStream: public HTTPFixedLengthIOS, public std::ostream
	/// This class is for internal use by HTTPSession only.
{
public:
	HTTPFixedLengthOutputStream(HTTPSession& session, std::streamsize length);
	~HTTPFixedLengthOutputStream();

	void* operator new(size_t size);
	void operator delete(void* ptr);
	
private:
	static Foundation::MemoryPool _pool;
};


Net_END


#endif // Net_HTTPFixedLengthStream_INCLUDED
