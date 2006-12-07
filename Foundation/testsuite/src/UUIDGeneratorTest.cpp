//
// UUIDGeneratorTest.cpp
//
// $Id: //poco/1.2/Foundation/testsuite/src/UUIDGeneratorTest.cpp#1 $
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


#include "UUIDGeneratorTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/UUID.h"
#include <set>


using Poco::UUIDGenerator;
using Poco::UUID;


UUIDGeneratorTest::UUIDGeneratorTest(const std::string& name): CppUnit::TestCase(name)
{
}


UUIDGeneratorTest::~UUIDGeneratorTest()
{
}


void UUIDGeneratorTest::testTimeBased()
{
	UUIDGenerator& gen = UUIDGenerator::defaultGenerator();
	
	std::set<UUID> uuids;
	for (int i = 0; i < 1000; ++i)
	{
		UUID uuid = gen.create();
		assert (uuid.version() == UUID::UUID_TIME_BASED);
		assert (uuids.find(uuid) == uuids.end());
		uuids.insert(uuid);
	}
}


void UUIDGeneratorTest::testRandom()
{
	UUIDGenerator& gen = UUIDGenerator::defaultGenerator();

	std::set<UUID> uuids;
	for (int i = 0; i < 1000; ++i)
	{
		UUID uuid = gen.createRandom();
		assert (uuid.version() == UUID::UUID_RANDOM);
		assert (uuids.find(uuid) == uuids.end());
		uuids.insert(uuid);
	}
}


void UUIDGeneratorTest::testNameBased()
{
	UUIDGenerator& gen = UUIDGenerator::defaultGenerator();

	UUID uuid1 = gen.createFromName(UUID::uri(), "http://www.appinf.com/uuid");
	assert (uuid1.version() == UUID::UUID_NAME_BASED);
	assert (uuid1.variant() == 2);

	UUID uuid2 = gen.createFromName(UUID::uri(), "http://www.appinf.com/uuid2");
	assert (uuid2 != uuid1);

	UUID uuid3 = gen.createFromName(UUID::dns(), "www.appinf.com");
	assert (uuid3 != uuid1);

	UUID uuid4 = gen.createFromName(UUID::oid(), "1.3.6.1.4.1");
	assert (uuid4 != uuid1);

	UUID uuid5 = gen.createFromName(UUID::x500(), "cn=Guenter Obiltschnig, ou=People, o=Applied Informatics, c=at");
	assert (uuid5 != uuid1);

	UUID uuid6 = gen.createFromName(UUID::uri(), "http://www.appinf.com/uuid");
	assert (uuid6 == uuid1);
}


void UUIDGeneratorTest::setUp()
{
}


void UUIDGeneratorTest::tearDown()
{
}


CppUnit::Test* UUIDGeneratorTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("UUIDGeneratorTest");

	CppUnit_addTest(pSuite, UUIDGeneratorTest, testTimeBased);
	CppUnit_addTest(pSuite, UUIDGeneratorTest, testRandom);
	CppUnit_addTest(pSuite, UUIDGeneratorTest, testNameBased);

	return pSuite;
}
