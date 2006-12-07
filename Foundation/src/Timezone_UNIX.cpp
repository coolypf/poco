//
// Timezone_UNIX.cpp
//
// $Id: //poco/1.2/Foundation/src/Timezone_UNIX.cpp#1 $
//
// Library: Foundation
// Package: DateTime
// Module:  Timezone
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


#include "Poco/Timezone.h"
#include <time.h>


namespace Poco {


class TZInfo
{
public:
	TZInfo()
	{
		tzset();
	}
	
	int timeZone()
	{
	#if defined(__APPLE__)  || defined(__FreeBSD__) // no timezone global var
		time_t now = time(NULL);
		struct tm t;
		gmtime_r(&now, &t);
		time_t utc = mktime(&t);
		return now - utc;
	#elif defined(__CYGWIN__)
		return -_timezone;
	#else
		return -timezone;
	#endif
	}
	
	const char* name(bool dst)
	{
		return tzname[dst ? 1 : 0];
	}
};


static TZInfo tzInfo;


int Timezone::utcOffset()
{
	return tzInfo.timeZone();
}

	
int Timezone::dst()
{
	time_t now = time(NULL);
	struct tm t;
	localtime_r(&now, &t);
	return t.tm_isdst == 1 ? 3600 : 0;
}


bool Timezone::isDst(const Timestamp& timestamp)
{
	time_t time = timestamp.epochTime();
	struct tm* tms = localtime(&time);
	return tms->tm_isdst > 0;
}

	
std::string Timezone::name()
{
	return std::string(tzInfo.name(dst() != 0));
}

	
std::string Timezone::standardName()
{
	return std::string(tzInfo.name(false));
}

	
std::string Timezone::dstName()
{
	return std::string(tzInfo.name(true));
}


} // namespace Poco
