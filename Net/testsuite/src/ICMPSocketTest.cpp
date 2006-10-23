//
// ICMPSocketTest.cpp
//
// $Id: //poco/1.2/Net/testsuite/src/ICMPSocketTest.cpp#1 $
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


#include "ICMPSocketTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "UDPEchoServer.h"
#include "Poco/Net/ICMPSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetException.h"
#include "Poco/Timespan.h"
#include "Poco/Stopwatch.h"


using Poco::Net::Socket;
using Poco::Net::ICMPSocket;
using Poco::Net::SocketAddress;
using Poco::Net::IPAddress;
using Poco::Timespan;
using Poco::Stopwatch;
using Poco::TimeoutException;
using Poco::Net::ICMPException;


ICMPSocketTest::ICMPSocketTest(const std::string& name): CppUnit::TestCase(name)
{
}


ICMPSocketTest::~ICMPSocketTest()
{
}


void ICMPSocketTest::testAssign()
{
	ICMPSocket s1(IPAddress::IPv4);
	ICMPSocket s2(s1);
}

void ICMPSocketTest::testSendToReceiveFrom()
{
	ICMPSocket ss(IPAddress::IPv4);

	SocketAddress sa("www.appinf.com", 0);
	SocketAddress sr(sa);

	try
	{
		ss.receiveFrom(sa);
		fail("must throw");
	}
	catch(ICMPException&)
	{
	}
	catch(TimeoutException&)
	{
	}

	ss.sendTo(sa);
	ss.receiveFrom(sa);

	assert(sr.host().toString() == sa.host().toString());
	ss.close();
}


void ICMPSocketTest::setUp()
{
}


void ICMPSocketTest::tearDown()
{
}


CppUnit::Test* ICMPSocketTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ICMPSocketTest");

	CppUnit_addTest(pSuite, ICMPSocketTest, testSendToReceiveFrom);
	CppUnit_addTest(pSuite, ICMPSocketTest, testAssign);

	return pSuite;
}
