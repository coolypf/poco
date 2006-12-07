//
// HTTPHeaderStream.cpp
//
// $Id: //poco/1.2/Net/src/HTTPHeaderStream.cpp#1 $
//
// Library: Net
// Package: HTTP
// Module:  HTTPHeaderStream
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


#include "Poco/Net/HTTPHeaderStream.h"
#include "Poco/Net/HTTPSession.h"


namespace Poco {
namespace Net {


//
// HTTPHeaderStreamBuf
//


HTTPHeaderStreamBuf::HTTPHeaderStreamBuf(HTTPSession& session, openmode mode):
	HTTPBasicStreamBuf(HTTPBufferAllocator::BUFFER_SIZE, mode),
	_session(session),
	_end(false)
{
}


HTTPHeaderStreamBuf::~HTTPHeaderStreamBuf()
{
}


int HTTPHeaderStreamBuf::readFromDevice(char* buffer, std::streamsize length)
{
	// read line-by-line; an empty line denotes the end of the headers.
	static const int eof = std::char_traits<char>::eof();

	if (_end) return 0;

	int n = 0;
	int ch = _session.get();
	while (ch != eof && ch != '\n' && n < length - 1)
	{
		*buffer++ = (char) ch; ++n;
		ch = _session.get();
	}
	if (ch != eof)
	{
		*buffer++ = (char) ch; ++n;
		if (n == 2) _end = true;
	}
	return n;
}


int HTTPHeaderStreamBuf::writeToDevice(const char* buffer, std::streamsize length)
{
	return _session.write(buffer, length);
}


//
// HTTPHeaderIOS
//


HTTPHeaderIOS::HTTPHeaderIOS(HTTPSession& session, HTTPHeaderStreamBuf::openmode mode):
	_buf(session, mode)
{
	poco_ios_init(&_buf);
}


HTTPHeaderIOS::~HTTPHeaderIOS()
{
	try
	{
		_buf.sync();
	}
	catch (...)
	{
	}
}


HTTPHeaderStreamBuf* HTTPHeaderIOS::rdbuf()
{
	return &_buf;
}


//
// HTTPHeaderInputStream
//


Poco::MemoryPool HTTPHeaderInputStream::_pool(sizeof(HTTPHeaderInputStream));


HTTPHeaderInputStream::HTTPHeaderInputStream(HTTPSession& session):
	HTTPHeaderIOS(session, std::ios::in),
	std::istream(&_buf)
{
}


HTTPHeaderInputStream::~HTTPHeaderInputStream()
{
}


void* HTTPHeaderInputStream::operator new(size_t size)
{
	return _pool.get();
}


void HTTPHeaderInputStream::operator delete(void* ptr)
{
	_pool.release(ptr);
}


//
// HTTPHeaderOutputStream
//


Poco::MemoryPool HTTPHeaderOutputStream::_pool(sizeof(HTTPHeaderOutputStream));


HTTPHeaderOutputStream::HTTPHeaderOutputStream(HTTPSession& session):
	HTTPHeaderIOS(session, std::ios::out),
	std::ostream(&_buf)
{
}


HTTPHeaderOutputStream::~HTTPHeaderOutputStream()
{
}


void* HTTPHeaderOutputStream::operator new(size_t size)
{
	return _pool.get();
}


void HTTPHeaderOutputStream::operator delete(void* ptr)
{
	_pool.release(ptr);
}


} } // namespace Poco::Net
