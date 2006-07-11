//
// CoreTest.cpp
//
// $Id: //poco/1.1.0/Foundation/testsuite/src/CoreTest.cpp#2 $
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


#include "CoreTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Foundation/Bugcheck.h"
#include "Foundation/Exception.h"
#include "Foundation/Environment.h"
#include "Foundation/Thread.h"
#include <iostream>


using Foundation::Bugcheck;
using Foundation::Exception;
using Foundation::Environment;
using Foundation::Thread;


//
// The bugcheck test is normally disabled, as it
// causes a break into the debugger.
//
#define ENABLE_BUGCHECK_TEST 0


CoreTest::CoreTest(const std::string& name): CppUnit::TestCase(name)
{
}


CoreTest::~CoreTest()
{
}


void CoreTest::testPlatform()
{
	std::cout << "POCO_OS:   " << POCO_OS << std::endl;
	std::cout << "POCO_ARCH: " << POCO_ARCH << std::endl;
}


void CoreTest::testFixedLength()
{
	assert (sizeof(Foundation::Int8) == 1);
	assert (sizeof(Foundation::UInt8) == 1);
	assert (sizeof(Foundation::Int16) == 2);
	assert (sizeof(Foundation::UInt16) == 2);
	assert (sizeof(Foundation::Int32) == 4);
	assert (sizeof(Foundation::UInt32) == 4);
	#if defined(POCO_HAVE_INT64)
	assert (sizeof(Foundation::Int64) == 8);
	assert (sizeof(Foundation::UInt64) == 8);
	#endif
	assert (sizeof(Foundation::IntPtr) == sizeof(void*));
	assert (sizeof(Foundation::UIntPtr) == sizeof(void*));	
}


void CoreTest::testBugcheck()
{
#if ENABLE_BUGCHECK_TEST
	try
	{
		Bugcheck::assertion("test", __FILE__, __LINE__);	
		failmsg("must throw exception");
	}
	catch (Exception&)
	{
	}

	try
	{
		Bugcheck::nullPointer("test", __FILE__, __LINE__);	
		failmsg("must throw exception");
	}
	catch (Exception&)
	{
	}

	try
	{
		Bugcheck::bugcheck("test", __FILE__, __LINE__);	
		failmsg("must throw exception");
	}
	catch (Exception&)
	{
	}
#endif
}


void CoreTest::testEnvironment()
{
	Environment::set("FOO", "BAR");
	assert (Environment::has("FOO"));
	assert (Environment::get("FOO") == "BAR");
	assert (!Environment::has("THISONEDOESNOTEXIST123"));
	try
	{
		std::string v = Environment::get("THISONEDOESNOTEXIST123");
		failmsg("Environment variable does not exist - must throw exception");
	}
	catch (Exception&)
	{
	}
	
	std::cout << "OS Name:         " << Environment::osName() << std::endl;
	std::cout << "OS Version:      " << Environment::osVersion() << std::endl;
	std::cout << "OS Architecture: " << Environment::osArchitecture() << std::endl;
	std::cout << "Node Name:       " << Environment::nodeName() << std::endl;
}


void CoreTest::setUp()
{
}


void CoreTest::tearDown()
{
}


CppUnit::Test* CoreTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("CoreTest");

	CppUnit_addTest(pSuite, CoreTest, testPlatform);
	CppUnit_addTest(pSuite, CoreTest, testFixedLength);
	CppUnit_addTest(pSuite, CoreTest, testBugcheck);
	CppUnit_addTest(pSuite, CoreTest, testEnvironment);

	return pSuite;
}
