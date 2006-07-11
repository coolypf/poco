//
// SharedLibraryTest.cpp
//
// $Id: //poco/1.1.0/Foundation/testsuite/src/SharedLibraryTest.cpp#2 $
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


#include "SharedLibraryTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Foundation/SharedLibrary.h"
#include "Foundation/Exception.h"


using Foundation::SharedLibrary;
using Foundation::NotFoundException;
using Foundation::LibraryLoadException;
using Foundation::LibraryAlreadyLoadedException;


typedef int (*GimmeFiveFunc)();


SharedLibraryTest::SharedLibraryTest(const std::string& name): CppUnit::TestCase(name)
{
}


SharedLibraryTest::~SharedLibraryTest()
{
}


void SharedLibraryTest::testSharedLibrary1()
{
	std::string path = "TestLibrary";
	path.append(SharedLibrary::suffix());
	SharedLibrary sl;
	assert (!sl.isLoaded());
	sl.load(path);
	assert (sl.getPath() == path);
	assert (sl.isLoaded());
	assert (sl.hasSymbol("pocoBuildManifest"));
	assert (sl.hasSymbol("pocoInitializeLibrary"));
	assert (sl.hasSymbol("pocoUninitializeLibrary"));
	assert (sl.hasSymbol("gimmeFive"));
	assert (!sl.hasSymbol("fooBar123"));
	
	void* p1 = sl.getSymbol("pocoBuildManifest");
	assertNotNullPtr(p1);
	try
	{
		p1 = sl.getSymbol("fooBar123");
		failmsg("no such symbol - must throw exception");
	}
	catch (NotFoundException&)
	{
	}
	catch (...)
	{
		failmsg("wrong exception");
	}
	sl.unload();
	assert (!sl.isLoaded());
}


void SharedLibraryTest::testSharedLibrary2()
{
	std::string path = "TestLibrary";
	path.append(SharedLibrary::suffix());
	SharedLibrary sl(path);
	assert (sl.getPath() == path);
	assert (sl.isLoaded());

	GimmeFiveFunc gimmeFive = (GimmeFiveFunc) sl.getSymbol("gimmeFive");
	assert (gimmeFive() == 5);
	
	sl.unload();
	assert (!sl.isLoaded());
}


void SharedLibraryTest::testSharedLibrary3()
{
	std::string path = "NonexistentLibrary";
	path.append(SharedLibrary::suffix());
	SharedLibrary sl;
	try
	{
		sl.load(path);
		failmsg("no such library - must throw exception");
	}
	catch (LibraryLoadException&)
	{
	}
	catch (...)
	{
		failmsg("wrong exception");
	}
	assert (!sl.isLoaded());

	path = "TestLibrary";
	path.append(SharedLibrary::suffix());
	sl.load(path);
	assert (sl.isLoaded());
	
	try
	{
		sl.load(path);
		failmsg("library already loaded - must throw exception");
	}
	catch (LibraryAlreadyLoadedException&)
	{
	}
	catch (...)
	{
		failmsg("wrong exception");
	}
	assert (sl.isLoaded());

	sl.unload();
	assert (!sl.isLoaded());
}


void SharedLibraryTest::setUp()
{
}


void SharedLibraryTest::tearDown()
{
}


CppUnit::Test* SharedLibraryTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SharedLibraryTest");

	CppUnit_addTest(pSuite, SharedLibraryTest, testSharedLibrary1);
	CppUnit_addTest(pSuite, SharedLibraryTest, testSharedLibrary2);
	CppUnit_addTest(pSuite, SharedLibraryTest, testSharedLibrary3);

	return pSuite;
}
