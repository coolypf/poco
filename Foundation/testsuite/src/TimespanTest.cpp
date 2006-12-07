//
// TimespanTest.cpp
//
// $Id: //poco/1.2/Foundation/testsuite/src/TimespanTest.cpp#1 $
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


#include "TimespanTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Timespan.h"


using Poco::Timespan;


TimespanTest::TimespanTest(const std::string& name): CppUnit::TestCase(name)
{
}


TimespanTest::~TimespanTest()
{
}


void TimespanTest::testConversions()
{
	Timespan ts;
	assert (ts.totalMicroseconds() == 0);
	ts = Timespan::DAYS;
	assert (ts.totalMicroseconds() == Timespan::DAYS);
	assert (ts.totalMilliseconds() == 86400000);
	assert (ts.totalSeconds() == 86400);
	assert (ts.totalMinutes() == 60*24);
	assert (ts.totalHours() == 24);
	assert (ts.days() == 1);
	
	assert (ts.microseconds() == 0);
	assert (ts.milliseconds() == 0);
	assert (ts.seconds() == 0);
	assert (ts.minutes() == 0);
	assert (ts.hours() == 0);
	
	ts.assign(2, 12, 30, 10, 123456);
	assert (ts.microseconds() == 456);
	assert (ts.milliseconds() == 123);
	assert (ts.seconds() == 10);
	assert (ts.minutes() == 30);
	assert (ts.hours() == 12);
	assert (ts.days() == 2);

	ts.assign(0, 36, 30, 10, 123456);
	assert (ts.microseconds() == 456);
	assert (ts.milliseconds() == 123);
	assert (ts.useconds() == 123456);
	assert (ts.seconds() == 10);
	assert (ts.minutes() == 30);
	assert (ts.hours() == 12);
	assert (ts.days() == 1);

	ts.assign(0, 0, 2190, 10, 123456);
	assert (ts.microseconds() == 456);
	assert (ts.milliseconds() == 123);
	assert (ts.useconds() == 123456);
	assert (ts.seconds() == 10);
	assert (ts.minutes() == 30);
	assert (ts.hours() == 12);
	assert (ts.days() == 1);
}


void TimespanTest::testComparisons()
{
	Timespan ts1(10000000);
	Timespan ts2(20000000);
	Timespan ts3(20000000);
	
	assert (ts1 != ts2);
	assert (!(ts1 == ts2));
	assert (ts1 <= ts2);
	assert (ts1 < ts2);
	assert (ts2 > ts1);
	assert (ts2 >= ts1);
	
	assert (ts2 == ts3);
	assert (!(ts2 != ts3));
	assert (ts2 >= ts3);
	assert (ts2 <= ts3);
	assert (!(ts2 > ts3));
	assert (!(ts2 < ts3));
	
	assert (ts1 == 10000000);
	assert (ts1 != 20000000);
	assert (ts1 <= 10000000);
	assert (ts1 <= 20000000);
	assert (ts1 >= 10000000);
	assert (ts1 >= 5000000);
	assert (ts1 < 20000000);
	assert (ts1 > 5000000);
}


void TimespanTest::testArithmetics()
{
	Timespan ts1(100000000);
	Timespan ts2(50000000);
	Timespan ts3;
	ts3 = ts1 + ts2;
	assert (ts3 == 150000000);
	ts3 = ts1 + 30000000;
	assert (ts3 == 130000000);
	ts3 = ts1 - ts2;
	assert (ts3 == 50000000);
	ts3 = ts1 - 20000000;
	assert (ts3 == 80000000);
	ts3 += 20000000;
	assert (ts3 == ts1);
	ts3 -= ts2;
	assert (ts3 == ts2);
}


void TimespanTest::testSwap()
{
	Timespan ts1(10000000);
	Timespan ts2(50000000);
	
	assert (ts1 < ts2);
	ts1.swap(ts2);
	assert (ts2 < ts1);
}


void TimespanTest::setUp()
{
}


void TimespanTest::tearDown()
{
}


CppUnit::Test* TimespanTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TimespanTest");

	CppUnit_addTest(pSuite, TimespanTest, testConversions);
	CppUnit_addTest(pSuite, TimespanTest, testComparisons);
	CppUnit_addTest(pSuite, TimespanTest, testArithmetics);
	CppUnit_addTest(pSuite, TimespanTest, testSwap);

	return pSuite;
}
