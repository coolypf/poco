//
// FileChannelTest.h
//
// $Id: //poco/1.1.0/Foundation/testsuite/src/FileChannelTest.h#2 $
//
// Definition of the FileChannelTest class.
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


#ifndef FileChannelTest_INCLUDED
#define FileChannelTest_INCLUDED


#ifndef Foundation_Foundation_INCLUDED
#include "Foundation/Foundation.h"
#endif
#ifndef CppUnit_TestCase_INCLUDED
#include "CppUnit/TestCase.h"
#endif


class FileChannelTest: public CppUnit::TestCase
{
public:
	enum TimeRotation 
	{
		DAY_HOUR_MIN = 0,
		HOUR_MIN,
		MIN
	};

	FileChannelTest(const std::string& name);
	~FileChannelTest();

	void testRotateBySize();
	void testRotateByAge();
	void testRotateAtTimeDayUTC();
	void testRotateAtTimeDayLocal();
	void testRotateAtTimeHourUTC();
	void testRotateAtTimeHourLocal();
	void testRotateAtTimeMinUTC();
	void testRotateAtTimeMinLocal();
	void testArchive();
	void testCompress();
	void testPurgeAge();
	void testPurgeCount();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	template<class D> std::string rotation(TimeRotation rtype) const;
	void remove(const std::string& baseName);
	std::string filename() const;
};


#endif // FileChannelTest_INCLUDED
