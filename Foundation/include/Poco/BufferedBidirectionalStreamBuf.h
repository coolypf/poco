//
// BufferedBidirectionalStreamBuf.h
//
// $Id: //poco/1.2/Foundation/include/Poco/BufferedBidirectionalStreamBuf.h#1 $
//
// Library: Foundation
// Package: Streams
// Module:  StreamBuf
//
// Definition of template BasicBufferedBidirectionalStreamBuf and class BufferedBidirectionalStreamBuf.
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


#ifndef Foundation_BufferedBidirectionalStreamBuf_INCLUDED
#define Foundation_BufferedBidirectionalStreamBuf_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/BufferAllocator.h"
#include "Poco/StreamUtil.h"
#include <streambuf>
#include <iosfwd>
#include <ios>


namespace Poco {


template<typename ch, typename tr, typename ba = BufferAllocator<ch> > 
class BasicBufferedBidirectionalStreamBuf: public std::basic_streambuf<ch, tr>
	/// This is an implementation of a buffered bidirectional 
	/// streambuf that greatly simplifies the implementation of
	/// custom streambufs of various kinds.
	/// Derived classes only have to override the methods
	/// readFromDevice() or writeToDevice().
	///
	/// In contrast to BasicBufferedStreambuf, this class supports
	/// simultaneous read and write access, so in addition to
	/// istream and ostream this streambuf can also be used
	/// for implementing an iostream.
{
protected:
	typedef std::basic_streambuf<ch, tr> Base;
	typedef std::basic_ios<ch, tr> IOS;
	typedef ch char_type;
	typedef tr char_traits;
	typedef ba Allocator;
	typedef typename Base::int_type int_type;
	typedef typename Base::pos_type pos_type;
	typedef typename Base::off_type off_type;
	typedef typename IOS::openmode openmode;

public:
	BasicBufferedBidirectionalStreamBuf(std::streamsize bufferSize, openmode mode):
		_bufsize(bufferSize),
		_pReadBuffer(Allocator::allocate(_bufsize)),
		_pWriteBuffer(Allocator::allocate(_bufsize)),
		_mode(mode)
	{
		this->setg(_pReadBuffer + 4, _pReadBuffer + 4, _pReadBuffer + 4);
		this->setp(_pWriteBuffer, _pWriteBuffer + (_bufsize - 1));
	}

	~BasicBufferedBidirectionalStreamBuf()
	{
		Allocator::deallocate(_pReadBuffer, _bufsize);
		Allocator::deallocate(_pWriteBuffer, _bufsize);
	}

	virtual int_type overflow(int_type c)
	{
		if (!(_mode & IOS::out)) return char_traits::eof();

		if (c != char_traits::eof()) 
		{
			*this->pptr() = char_traits::to_char_type(c);
			this->pbump(1);
		}
		if (flush_buffer() == std::streamsize(-1)) return char_traits::eof();

		return c;
	}

	virtual int_type underflow()
	{
		if (!(_mode & IOS::in)) return char_traits::eof();

		if (this->gptr() && (this->gptr() < this->egptr()))
			return char_traits::to_int_type(*this->gptr());

		int putback = int(this->gptr() - this->eback());
		if (putback > 4) putback = 4;

		char_traits::copy(_pReadBuffer + (4 - putback), this->gptr() - putback, putback);

		int n = readFromDevice(_pReadBuffer + 4, _bufsize - 4);
		if (n <= 0) return char_traits::eof();

		this->setg(_pReadBuffer + (4 - putback), _pReadBuffer + 4, _pReadBuffer + 4 + n);

		// return next character
		return char_traits::to_int_type(*this->gptr());    
	}

	virtual int sync()
	{
		if (this->pptr() && this->pptr() > this->pbase()) 
		{
			if (flush_buffer() == -1) return -1;
		}
		return 0;
	}

private:
	virtual int readFromDevice(char_type* buffer, std::streamsize length)
	{
		return 0;
	}

	virtual int writeToDevice(const char_type* buffer, std::streamsize length)
	{
		return 0;
	}

	int flush_buffer()
	{
		int n = int(this->pptr() - this->pbase());
		if (writeToDevice(this->pbase(), n) == n) 
		{
			this->pbump(-n);
			return n;
		}
		return -1;
	}

	std::streamsize _bufsize;
	char_type*      _pReadBuffer;
	char_type*      _pWriteBuffer;
	openmode        _mode;
};


//
// We provide an instantiation for char
//
typedef BasicBufferedBidirectionalStreamBuf<char, std::char_traits<char> > BufferedBidirectionalStreamBuf;


} // namespace Poco


#endif // Foundation_BufferedBidirectionalStreamBuf_INCLUDED
