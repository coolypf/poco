//
// NetworkInterfaceTest.cpp
//
// $Id: //poco/1.2/Net/testsuite/src/NetworkInterfaceTest.cpp#1 $
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


#include "NetworkInterfaceTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Net/NetworkInterface.h"
#include <iostream>


using Poco::Net::NetworkInterface;


NetworkInterfaceTest::NetworkInterfaceTest(const std::string& name): CppUnit::TestCase(name)
{
}


NetworkInterfaceTest::~NetworkInterfaceTest()
{
}


void NetworkInterfaceTest::testList()
{
	NetworkInterface::NetworkInterfaceList list = NetworkInterface::list();
	assert (!list.empty());
	for (NetworkInterface::NetworkInterfaceList::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		std::cout << "Name:    " << it->name() << std::endl;
		std::cout << "Address: " << it->address().toString() << std::endl;
		std::cout << "Index:   " << it->index() << std::endl;		
	}
}


void NetworkInterfaceTest::testForName()
{
	NetworkInterface::NetworkInterfaceList list = NetworkInterface::list();
	for (NetworkInterface::NetworkInterfaceList::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		NetworkInterface ifc = NetworkInterface::forName(it->name());
		assert (ifc.name() == it->name());
	}
}


void NetworkInterfaceTest::testForAddress()
{
	NetworkInterface::NetworkInterfaceList list = NetworkInterface::list();
	for (NetworkInterface::NetworkInterfaceList::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		NetworkInterface ifc = NetworkInterface::forAddress(it->address());
		assert (ifc.address() == it->address());
	}
}


void NetworkInterfaceTest::testForIndex()
{
#if defined(POCO_HAVE_IPv6)
	NetworkInterface::NetworkInterfaceList list = NetworkInterface::list();
	for (NetworkInterface::NetworkInterfaceList::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		NetworkInterface ifc = NetworkInterface::forIndex(it->index());
		assert (ifc.index() == it->index());
	}
#endif
}


void NetworkInterfaceTest::setUp()
{
}


void NetworkInterfaceTest::tearDown()
{
}


CppUnit::Test* NetworkInterfaceTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("NetworkInterfaceTest");

	CppUnit_addTest(pSuite, NetworkInterfaceTest, testList);
	CppUnit_addTest(pSuite, NetworkInterfaceTest, testForName);
	CppUnit_addTest(pSuite, NetworkInterfaceTest, testForAddress);
	CppUnit_addTest(pSuite, NetworkInterfaceTest, testForIndex);

	return pSuite;
}
