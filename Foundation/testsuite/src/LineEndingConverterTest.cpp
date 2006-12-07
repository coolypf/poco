//
// LineEndingConverterTest.cpp
//
// $Id: //poco/1.2/Foundation/testsuite/src/LineEndingConverterTest.cpp#1 $
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


#include "LineEndingConverterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/LineEndingConverter.h"
#include "Poco/StreamCopier.h"
#include <sstream>


using Poco::LineEnding;
using Poco::InputLineEndingConverter;
using Poco::OutputLineEndingConverter;
using Poco::StreamCopier;


LineEndingConverterTest::LineEndingConverterTest(const std::string& name): CppUnit::TestCase(name)
{
}


LineEndingConverterTest::~LineEndingConverterTest()
{
}


void LineEndingConverterTest::testInputDosToUnix()
{
	std::istringstream input("line1\r\nline2\r\nline3\r\n");
	std::ostringstream output;
	InputLineEndingConverter conv(input, LineEnding::NEWLINE_LF);
	StreamCopier::copyStream(conv, output);
	std::string result = output.str();
	assert (result == "line1\nline2\nline3\n");
}


void LineEndingConverterTest::testInputUnixToDos()
{
	std::istringstream input("line1\nline2\nline3\n");
	std::ostringstream output;
	InputLineEndingConverter conv(input, LineEnding::NEWLINE_CRLF);
	StreamCopier::copyStream(conv, output);
	std::string result = output.str();
	assert (result == "line1\r\nline2\r\nline3\r\n");
}


void LineEndingConverterTest::testInputMacToUnix()
{
	std::istringstream input("line1\rline2\rline3\r");
	std::ostringstream output;
	InputLineEndingConverter conv(input, LineEnding::NEWLINE_LF);
	StreamCopier::copyStream(conv, output);
	std::string result = output.str();
	assert (result == "line1\nline2\nline3\n");
}


void LineEndingConverterTest::testInputRemove()
{
	std::istringstream input("line1\r\nline2\rline3\n");
	std::ostringstream output;
	InputLineEndingConverter conv(input, "");
	StreamCopier::copyStream(conv, output);
	std::string result = output.str();
	assert (result == "line1line2line3");
}


void LineEndingConverterTest::testOutputDosToUnix()
{
	std::ostringstream output;
	OutputLineEndingConverter conv(output, LineEnding::NEWLINE_LF);
	conv << "line1\r\nline2\r\nline3\r\n" << std::flush;
	std::string result = output.str();
	assert (result == "line1\nline2\nline3\n");
}


void LineEndingConverterTest::testOutputUnixToDos()
{
	std::ostringstream output;
	OutputLineEndingConverter conv(output, LineEnding::NEWLINE_CRLF);
	conv << "line1\nline2\nline3\n" << std::flush;
	std::string result = output.str();
	assert (result == "line1\r\nline2\r\nline3\r\n");
}


void LineEndingConverterTest::testOutputMacToUnix()
{
	std::ostringstream output;
	OutputLineEndingConverter conv(output, LineEnding::NEWLINE_LF);
	conv << "line1\rline2\rline3\r" << std::flush;
	std::string result = output.str();
	assert (result == "line1\nline2\nline3\n");
}


void LineEndingConverterTest::testOutputRemove()
{
	std::ostringstream output;
	OutputLineEndingConverter conv(output, "");
	conv << "line1\r\nline2\rline3\n" << std::flush;
	std::string result = output.str();
	assert (result == "line1line2line3");
}


void LineEndingConverterTest::setUp()
{
}


void LineEndingConverterTest::tearDown()
{
}


CppUnit::Test* LineEndingConverterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("LineEndingConverterTest");

	CppUnit_addTest(pSuite, LineEndingConverterTest, testInputDosToUnix);
	CppUnit_addTest(pSuite, LineEndingConverterTest, testInputUnixToDos);
	CppUnit_addTest(pSuite, LineEndingConverterTest, testInputMacToUnix);
	CppUnit_addTest(pSuite, LineEndingConverterTest, testInputRemove);
	CppUnit_addTest(pSuite, LineEndingConverterTest, testOutputDosToUnix);
	CppUnit_addTest(pSuite, LineEndingConverterTest, testOutputUnixToDos);
	CppUnit_addTest(pSuite, LineEndingConverterTest, testOutputMacToUnix);
	CppUnit_addTest(pSuite, LineEndingConverterTest, testOutputRemove);

	return pSuite;
}
