//
// HTTPHeaderStream.h
//
// $Id: //poco/1.2/Net/include/Poco/Net/HTTPHeaderStream.h#1 $
//
// Library: Net
// Package: HTTP
// Module:  HTTPHeaderStream
//
// Definition of the HTTPHeaderStream class.
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


#ifndef Net_HTTPHeaderStream_INCLUDED
#define Net_HTTPHeaderStream_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/HTTPBasicStreamBuf.h"
#include "Poco/MemoryPool.h"
#include <istream>
#include <ostream>


namespace Poco {
namespace Net {


class HTTPSession;


class Net_API HTTPHeaderStreamBuf: public HTTPBasicStreamBuf
	/// This is the streambuf class used for reading from a HTTP header
	/// in a HTTPSession.
{
public:
	typedef HTTPBasicStreamBuf::openmode openmode;

	HTTPHeaderStreamBuf(HTTPSession& session, openmode mode);
	~HTTPHeaderStreamBuf();
	
protected:
	int readFromDevice(char* buffer, std::streamsize length);
	int writeToDevice(const char* buffer, std::streamsize length);

private:
	HTTPSession& _session;
	bool         _end;
};


class Net_API HTTPHeaderIOS: public virtual std::ios
	/// The base class for HTTPHeaderInputStream.
{
public:
	HTTPHeaderIOS(HTTPSession& session, HTTPHeaderStreamBuf::openmode mode);
	~HTTPHeaderIOS();
	HTTPHeaderStreamBuf* rdbuf();

protected:
	HTTPHeaderStreamBuf _buf;
};


class Net_API HTTPHeaderInputStream: public HTTPHeaderIOS, public std::istream
	/// This class is for internal use by HTTPSession only.
{
public:
	HTTPHeaderInputStream(HTTPSession& session);
	~HTTPHeaderInputStream();

	void* operator new(size_t size);
	void operator delete(void* ptr);
	
private:
	static Poco::MemoryPool _pool;
};


class Net_API HTTPHeaderOutputStream: public HTTPHeaderIOS, public std::ostream
	/// This class is for internal use by HTTPSession only.
{
public:
	HTTPHeaderOutputStream(HTTPSession& session);
	~HTTPHeaderOutputStream();

	void* operator new(size_t size);
	void operator delete(void* ptr);
	
private:
	static Poco::MemoryPool _pool;
};


} } // namespace Poco::Net


#endif // Net_HTTPHeaderStream_INCLUDED
