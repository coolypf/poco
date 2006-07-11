//
// HTTPFixedLengthStream.cpp
//
// $Id: //poco/1.1.0/Net/src/HTTPFixedLengthStream.cpp#2 $
//
// Library: Net
// Package: HTTP
// Module:  HTTPFixedLengthStream
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


#include "Net/HTTPFixedLengthStream.h"
#include "Net/HTTPSession.h"


using Foundation::BufferedStreamBuf;


Net_BEGIN


//
// HTTPFixedLengthStreamBuf
//


HTTPFixedLengthStreamBuf::HTTPFixedLengthStreamBuf(HTTPSession& session, std::streamsize length, openmode mode):
	HTTPBasicStreamBuf(HTTPBufferAllocator::BUFFER_SIZE, mode),
	_session(session),
	_length(length),
	_count(0)
{
}


HTTPFixedLengthStreamBuf::~HTTPFixedLengthStreamBuf()
{
}


int HTTPFixedLengthStreamBuf::readFromDevice(char* buffer, std::streamsize length)
{
	int n = 0;
	if (_count < _length)
	{
		if (_count + length > _length)
			length = _length - _count;
		n = _session.read(buffer, length);
		if (n > 0) _count += n;
	}
	return n;
}


int HTTPFixedLengthStreamBuf::writeToDevice(const char* buffer, std::streamsize length)
{
	int n = 0;
	if (_count < _length)
	{
		if (_count + length > _length)
			length = _length - _count;
		n = _session.write(buffer, length);
		if (n > 0) _count += n;
	}
	return n;
}


//
// HTTPFixedLengthIOS
//


HTTPFixedLengthIOS::HTTPFixedLengthIOS(HTTPSession& session, std::streamsize length, HTTPFixedLengthStreamBuf::openmode mode):
	_buf(session, length, mode)
{
	poco_ios_init(&_buf);
}


HTTPFixedLengthIOS::~HTTPFixedLengthIOS()
{
	try
	{
		_buf.sync();
	}
	catch (...)
	{
	}
}


HTTPFixedLengthStreamBuf* HTTPFixedLengthIOS::rdbuf()
{
	return &_buf;
}


//
// HTTPFixedLengthInputStream
//


Foundation::MemoryPool HTTPFixedLengthInputStream::_pool(sizeof(HTTPFixedLengthInputStream));


HTTPFixedLengthInputStream::HTTPFixedLengthInputStream(HTTPSession& session, std::streamsize length):
	HTTPFixedLengthIOS(session, length, std::ios::in),
	std::istream(&_buf)
{
}


HTTPFixedLengthInputStream::~HTTPFixedLengthInputStream()
{
}


void* HTTPFixedLengthInputStream::operator new(size_t size)
{
	return _pool.get();
}


void HTTPFixedLengthInputStream::operator delete(void* ptr)
{
	_pool.release(ptr);
}


//
// HTTPFixedLengthOutputStream
//


Foundation::MemoryPool HTTPFixedLengthOutputStream::_pool(sizeof(HTTPFixedLengthOutputStream));


HTTPFixedLengthOutputStream::HTTPFixedLengthOutputStream(HTTPSession& session, std::streamsize length):
	HTTPFixedLengthIOS(session, length, std::ios::out),
	std::ostream(&_buf)
{
}


HTTPFixedLengthOutputStream::~HTTPFixedLengthOutputStream()
{
}


void* HTTPFixedLengthOutputStream::operator new(size_t size)
{
	return _pool.get();
}


void HTTPFixedLengthOutputStream::operator delete(void* ptr)
{
	_pool.release(ptr);
}


Net_END
