//
// NetTestSuite.cpp
//
// $Id: //poco/svn/Net/testsuite/src/NetTestSuite.cpp#2 $
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


#include "NetTestSuite.h"
#include "NetCoreTestSuite.h"
#include "SocketsTestSuite.h"
#include "MessagesTestSuite.h"
#include "HTTPTestSuite.h"
#include "HTTPClientTestSuite.h"
#include "TCPServerTestSuite.h"
#include "HTTPServerTestSuite.h"
#include "HTMLTestSuite.h"
#include "ReactorTestSuite.h"
#include "FTPClientTestSuite.h"
#include "MailTestSuite.h"
#include "ICMPClientTestSuite.h"
#include "SyslogTest.h"


CppUnit::Test* NetTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("NetTestSuite");

	pSuite->addTest(NetCoreTestSuite::suite());
	pSuite->addTest(SocketsTestSuite::suite());
	pSuite->addTest(MessagesTestSuite::suite());
	pSuite->addTest(HTTPTestSuite::suite());
	pSuite->addTest(HTTPClientTestSuite::suite());
	pSuite->addTest(TCPServerTestSuite::suite());
	pSuite->addTest(HTTPServerTestSuite::suite());
	pSuite->addTest(HTMLTestSuite::suite());
	pSuite->addTest(ReactorTestSuite::suite());
	pSuite->addTest(FTPClientTestSuite::suite());
	pSuite->addTest(MailTestSuite::suite());
	pSuite->addTest(ICMPClientTestSuite::suite());
	pSuite->addTest(SyslogTest::suite());

	return pSuite;
}
