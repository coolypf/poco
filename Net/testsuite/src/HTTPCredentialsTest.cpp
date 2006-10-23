//
// HTTPCredentialsTest.cpp
//
// $Id: //poco/1.2/Net/testsuite/src/HTTPCredentialsTest.cpp#1 $
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


#include "HTTPCredentialsTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Net/NetException.h"


using Poco::Net::HTTPRequest;
using Poco::Net::HTTPBasicCredentials;
using Poco::Net::NotAuthenticatedException;


HTTPCredentialsTest::HTTPCredentialsTest(const std::string& name): CppUnit::TestCase(name)
{
}


HTTPCredentialsTest::~HTTPCredentialsTest()
{
}


void HTTPCredentialsTest::testCredentials()
{
	HTTPRequest request;
	assert (!request.hasCredentials());
	
	HTTPBasicCredentials cred("user", "secret");
	cred.authenticate(request);
	assert (request.hasCredentials());
	std::string scheme;
	std::string info;
	request.getCredentials(scheme, info);
	assert (scheme == "Basic");
	assert (info == "dXNlcjpzZWNyZXQ=");
	
	HTTPBasicCredentials cred2(request);
	assert (cred2.getUsername() == "user");
	assert (cred2.getPassword() == "secret");
}


void HTTPCredentialsTest::testBadCredentials()
{
	HTTPRequest request;
	
	std::string scheme;
	std::string info;
	try
	{
		request.getCredentials(scheme, info);
		fail("no credentials - must throw");
	}
	catch (NotAuthenticatedException&)
	{
	}
	
	request.setCredentials("Test", "SomeData");
	request.getCredentials(scheme, info);
	assert (scheme == "Test");
	assert (info == "SomeData");
	
	try
	{
		HTTPBasicCredentials cred(request);
		fail("bad scheme - must throw");
	}
	catch (NotAuthenticatedException&)
	{
	}
}


void HTTPCredentialsTest::setUp()
{
}


void HTTPCredentialsTest::tearDown()
{
}


CppUnit::Test* HTTPCredentialsTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("HTTPCredentialsTest");

	CppUnit_addTest(pSuite, HTTPCredentialsTest, testCredentials);
	CppUnit_addTest(pSuite, HTTPCredentialsTest, testBadCredentials);

	return pSuite;
}
