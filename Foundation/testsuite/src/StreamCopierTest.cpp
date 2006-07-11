//
// StreamCopierTest.cpp
//
// $Id: //poco/1.1.0/Foundation/testsuite/src/StreamCopierTest.cpp#2 $
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


#include "StreamCopierTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Foundation/StreamCopier.h"
#include <sstream>


using Foundation::StreamCopier;


StreamCopierTest::StreamCopierTest(const std::string& name): CppUnit::TestCase(name)
{
}


StreamCopierTest::~StreamCopierTest()
{
}


void StreamCopierTest::testBufferedCopy()
{
	{
		std::string src;
		for (int i = 0; i < 255; ++i) src += char(i);
		std::istringstream istr(src);
		std::ostringstream ostr;
		StreamCopier::copyStream(istr, ostr);
		assert (ostr.str() == src);
	}
	{
		std::string src;
		for (int i = 0; i < 512; ++i) src += char(i % 256);
		std::istringstream istr(src);
		std::ostringstream ostr;
		StreamCopier::copyStream(istr, ostr, 100);
		assert (ostr.str() == src);
	}
	{
		std::string src;
		for (int i = 0; i < 512; ++i) src += char(i % 256);
		std::istringstream istr(src);
		std::ostringstream ostr;
		StreamCopier::copyStream(istr, ostr, 128);
		assert (ostr.str() == src);
	}
	{
		std::string src;
		for (int i = 0; i < 512; ++i) src += char(i % 256);
		std::istringstream istr(src);
		std::ostringstream ostr;
		StreamCopier::copyStream(istr, ostr, 512);
		assert (ostr.str() == src);
	}
}


void StreamCopierTest::testUnbufferedCopy()
{
	std::string src;
	for (int i = 0; i < 255; ++i) src += char(i);
	std::istringstream istr(src);
	std::ostringstream ostr;
	StreamCopier::copyStreamUnbuffered(istr, ostr);
	assert (ostr.str() == src);
}


void StreamCopierTest::testCopyToString()
{
	std::string src;
	for (int i = 0; i < 512; ++i) src += char(i % 256);
	std::istringstream istr(src);
	std::string dest;
	StreamCopier::copyToString(istr, dest, 100);
	assert (src == dest);
}


void StreamCopierTest::setUp()
{
}


void StreamCopierTest::tearDown()
{
}


CppUnit::Test* StreamCopierTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("StreamCopierTest");

	CppUnit_addTest(pSuite, StreamCopierTest, testBufferedCopy);
	CppUnit_addTest(pSuite, StreamCopierTest, testUnbufferedCopy);

	return pSuite;
}
