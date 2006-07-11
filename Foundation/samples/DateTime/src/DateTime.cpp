//
// DateTime.cpp
//
// $Id: //poco/1.1.0/Foundation/samples/DateTime/src/DateTime.cpp#2 $
//
// This sample demonstrates the DateTime class.
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


#include "Foundation/DateTime.h"
#include "Foundation/DateTimeFormat.h"
#include <iostream>


using Foundation::DateTime;
using Foundation::DateTimeFormat;


int main(int argc, char** argv)
{
	DateTime now;
	
	std::cout << "Today is "
	          << DateTimeFormat::WEEKDAY_NAMES[now.dayOfWeek()] << ", "
	          << DateTimeFormat::MONTH_NAMES[now.month() - 1] << " "
	          << now.day() << " - "
	          << "day number "
	          << now.dayOfYear()
	          << " in "
	          << now.year()
	          << " and day number "
	          << (long) now.julianDay()
	          << " in the Julian calendar." << std::endl;
	
	return 0;
}
