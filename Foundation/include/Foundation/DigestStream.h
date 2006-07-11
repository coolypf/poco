//
// DigestStream.h
//
// $Id: //poco/1.1.0/Foundation/include/Foundation/DigestStream.h#2 $
//
// Library: Foundation
// Package: Crypt
// Module:  DigestStream
//
// Definition of classes DigestInputStream and DigestOutputStream.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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


#ifndef Foundation_DigestStream_INCLUDED
#define Foundation_DigestStream_INCLUDED


#ifndef Foundation_Foundation_INCLUDED
#include "Foundation/Foundation.h"
#endif
#ifndef Foundation_BufferedStreamBuf_INCLUDED
#include "Foundation/BufferedStreamBuf.h"
#endif
#ifndef Foundation_DigestEngine_INCLUDED
#include "Foundation/DigestEngine.h"
#endif
#ifndef STD_ISTREAM_INCLUDED
#include <istream>
#define STD_ISTREAM_INCLUDED
#endif
#ifndef STD_OSTREAM_INCLUDED
#include <ostream>
#define STD_OSTREAM_INCLUDED
#endif


Foundation_BEGIN


class Foundation_API DigestBuf: public BufferedStreamBuf
	/// This streambuf computes a digest of all data going
	/// through it.
{
public:
	DigestBuf(DigestEngine& eng);
	DigestBuf(DigestEngine& eng, std::istream& istr);
	DigestBuf(DigestEngine& eng, std::ostream& ostr);
	~DigestBuf();	
	int readFromDevice(char* buffer, std::streamsize length);
	int writeToDevice(const char* buffer, std::streamsize length);
	void close();

private:
	DigestEngine& _eng;
	std::istream* _pIstr;
	std::ostream* _pOstr;
	static const int BUFFER_SIZE;
};


class Foundation_API DigestIOS: public virtual std::ios
	/// The base class for DigestInputStream and DigestOutputStream.
	///
	/// This class is needed to ensure the correct initialization
	/// order of the stream buffer and base classes.
{
public:
	DigestIOS(DigestEngine& eng);
	DigestIOS(DigestEngine& eng, std::istream& istr);
	DigestIOS(DigestEngine& eng, std::ostream& ostr);
	~DigestIOS();
	DigestBuf* rdbuf();

protected:
	DigestBuf _buf;
};


class Foundation_API DigestInputStream: public DigestIOS, public std::istream
	/// This istream computes a digest of
	/// all the data passing through it,
	/// using a DigestEngine.
{
public:
	DigestInputStream(DigestEngine& eng, std::istream& istr);
	~DigestInputStream();
};


class Foundation_API DigestOutputStream: public DigestIOS, public std::ostream
	/// This ostream computes a digest of
	/// all the data passing through it,
	/// using a DigestEngine.
	/// To ensure that all data has been incorporated
	/// into the digest, call close() or flush() before 
	/// you obtain the digest from the digest engine.
{
public:
	DigestOutputStream(DigestEngine& eng);
	DigestOutputStream(DigestEngine& eng, std::ostream& ostr);
	~DigestOutputStream();
	void close();
};


Foundation_END


#endif // Foundation_DigestStream_INCLUDED
