//
// BinaryReaderWriterTest.cpp
//
// $Id: //poco/1.2/Foundation/testsuite/src/BinaryReaderWriterTest.cpp#1 $
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


#include "BinaryReaderWriterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/BinaryWriter.h"
#include "Poco/BinaryReader.h"
#include <sstream>


using Poco::BinaryWriter;
using Poco::BinaryReader;
using Poco::Int32;
using Poco::UInt32;
using Poco::Int64;
using Poco::UInt64;


BinaryReaderWriterTest::BinaryReaderWriterTest(const std::string& name): CppUnit::TestCase(name)
{
}


BinaryReaderWriterTest::~BinaryReaderWriterTest()
{
}


void BinaryReaderWriterTest::testNative()
{
	std::stringstream sstream;
	BinaryWriter writer(sstream);
	BinaryReader reader(sstream);
	write(writer);
	read(reader);
}


void BinaryReaderWriterTest::testBigEndian()
{
	std::stringstream sstream;
	BinaryWriter writer(sstream, BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	BinaryReader reader(sstream, BinaryReader::UNSPECIFIED_BYTE_ORDER);
	assert (writer.byteOrder() == BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	writer.writeBOM();
	write(writer);
	reader.readBOM();
	assert (reader.byteOrder() == BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	read(reader);
}


void BinaryReaderWriterTest::testLittleEndian()
{
	std::stringstream sstream;
	BinaryWriter writer(sstream, BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	BinaryReader reader(sstream, BinaryReader::UNSPECIFIED_BYTE_ORDER);
	assert (writer.byteOrder() == BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);
	writer.writeBOM();
	write(writer);
	reader.readBOM();
	assert (reader.byteOrder() == BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	read(reader);
}


void BinaryReaderWriterTest::write(BinaryWriter& writer)
{
	writer << true;
	writer << false;
	writer << 'a';
	writer << (short) -100;
	writer << (unsigned short) 50000;
	writer << -123456;
	writer << (unsigned) 123456;
	writer << (long) -1234567890;
	writer << (unsigned long) 1234567890;
	
#if defined(POCO_HAVE_INT64)
	writer << (Int64) -1234567890;
	writer << (UInt64) 1234567890;
#endif

	writer << (float) 1.5;
	writer << (double) -1.5;
	
	writer << "foo";
	writer << "";
	
	writer << std::string("bar");
	writer << std::string();
	
	writer.write7BitEncoded((UInt32) 100);
	writer.write7BitEncoded((UInt32) 1000);
	writer.write7BitEncoded((UInt32) 10000);
	writer.write7BitEncoded((UInt32) 100000);
	writer.write7BitEncoded((UInt32) 1000000);

#if defined(POCO_HAVE_INT64)
	writer.write7BitEncoded((UInt64) 100);
	writer.write7BitEncoded((UInt64) 1000);
	writer.write7BitEncoded((UInt64) 10000);
	writer.write7BitEncoded((UInt64) 100000);
	writer.write7BitEncoded((UInt64) 1000000);
#endif

	writer.writeRaw("RAW");
}


void BinaryReaderWriterTest::read(BinaryReader& reader)
{
	bool b;
	reader >> b;
	assert (b);
	reader >> b;
	assert (!b);
	
	char c;
	reader >> c;
	assert (c == 'a');

	short shortv;
	reader >> shortv;
	assert (shortv == -100);

	unsigned short ushortv;
	reader >> ushortv;
	assert (ushortv == 50000);

	int intv;
	reader >> intv;
	assert (intv == -123456);

	unsigned uintv;
	reader >> uintv;
	assert (uintv == 123456);

	long longv;
	reader >> longv;
	assert (longv == -1234567890);

	unsigned long ulongv;
	reader >> ulongv;
	assert (ulongv == 1234567890);

#if defined(POCO_HAVE_INT64)
	Int64 int64v;
	reader >> int64v;
	assert (int64v == -1234567890);
	
	UInt64 uint64v;
	reader >> uint64v;
	assert (uint64v == 1234567890);
#endif

	float floatv;
	reader >> floatv;
	assert (floatv == 1.5);
	
	double doublev;
	reader >> doublev;
	assert (doublev == -1.5);
	
	std::string str;
	reader >> str;
	assert (str == "foo");
	reader >> str;
	assert (str == "");
	reader >> str;
	assert (str == "bar");
	reader >> str;
	assert (str == "");
	
	UInt32 uint32v;
	reader.read7BitEncoded(uint32v);
	assert (uint32v == 100);
	reader.read7BitEncoded(uint32v);
	assert (uint32v == 1000);
	reader.read7BitEncoded(uint32v);
	assert (uint32v == 10000);
	reader.read7BitEncoded(uint32v);
	assert (uint32v == 100000);
	reader.read7BitEncoded(uint32v);
	assert (uint32v == 1000000);

#if defined(POCO_HAVE_INT64)
	reader.read7BitEncoded(uint64v);
	assert (uint64v == 100);
	reader.read7BitEncoded(uint64v);
	assert (uint64v == 1000);
	reader.read7BitEncoded(uint64v);
	assert (uint64v == 10000);
	reader.read7BitEncoded(uint64v);
	assert (uint64v == 100000);
	reader.read7BitEncoded(uint64v);
	assert (uint64v == 1000000);
#endif

	reader.readRaw(3, str);
	assert (str == "RAW");
}


void BinaryReaderWriterTest::setUp()
{
}


void BinaryReaderWriterTest::tearDown()
{
}


CppUnit::Test* BinaryReaderWriterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("BinaryReaderWriterTest");

	CppUnit_addTest(pSuite, BinaryReaderWriterTest, testNative);
	CppUnit_addTest(pSuite, BinaryReaderWriterTest, testBigEndian);
	CppUnit_addTest(pSuite, BinaryReaderWriterTest, testLittleEndian);

	return pSuite;
}
