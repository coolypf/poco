//
// String.h
//
// $Id: //poco/1.1.0/Foundation/src/String.cpp#2 $
//
// Library: Foundation
// Package: Core
// Module:  String
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


#include "Foundation/String.h"


Foundation_BEGIN


#if defined(POCO_NO_TEMPLATE_ICOMPARE)


int icompare(const std::string& str, std::string::size_type pos, std::string::size_type n, std::string::const_iterator it2, std::string::const_iterator end2)
{
	std::string::size_type sz = str.size();
	if (pos > sz) pos = sz;
	if (pos + n > sz) n = sz - pos;
	std::string::const_iterator it1  = str.begin() + pos; 
	std::string::const_iterator end1 = str.begin() + pos + n;
	std::locale loc;
	while (it1 != end1 && it2 != end2)
	{
        std::string::value_type c1 = tolower(*it1, loc);
        std::string::value_type c2 = tolower(*it2, loc);
        if (c1 < c2)
            return -1;
        else if (c1 > c2)
            return 1;
        ++it1; ++it2;
	}
    
    if (it1 == end1)
		return it2 == end2 ? 0 : -1;
    else
        return 1;
}


int icompare(const std::string& str1, const std::string& str2)
{
	return icompare(str1, 0, str1.size(), str2.begin(), str2.end());
}


int icompare(const std::string& str1, std::string::size_type n1, const std::string& str2, std::string::size_type n2)
{
	if (n2 > str2.size()) n2 = str2.size();
	return icompare(str1, 0, n1, str2.begin(), str2.begin() + n2);
}


int icompare(const std::string& str1, std::string::size_type n, const std::string& str2)
{
	if (n > str2.size()) n = str2.size();
	return icompare(str1, 0, n, str2.begin(), str2.begin() + n);
}


int icompare(const std::string& str1, std::string::size_type pos, std::string::size_type n, const std::string& str2)
{
	return icompare(str1, pos, n, str2.begin(), str2.end());
}


int icompare(const std::string& str1, std::string::size_type pos1, std::string::size_type n1, const std::string& str2, std::string::size_type pos2, std::string::size_type n2)
{
	std::string::size_type sz2 = str2.size();
	if (pos2 > sz2) pos2 = sz2;
	if (pos2 + n2 > sz2) n2 = sz2 - pos2;
	return icompare(str1, pos1, n1, str2.begin() + pos2, str2.begin() + pos2 + n2);
}


int icompare(const std::string& str1, std::string::size_type pos1, std::string::size_type n, const std::string& str2, std::string::size_type pos2)
{
	std::string::size_type sz2 = str2.size();
	if (pos2 > sz2) pos2 = sz2;
	if (pos2 + n > sz2) n = sz2 - pos2;
	return icompare(str1, pos1, n, str2.begin() + pos2, str2.begin() + pos2 + n);
}


int icompare(const std::string& str, std::string::size_type pos, std::string::size_type n, const std::string::value_type* ptr)
{
	poco_check_ptr (ptr);
	std::string::size_type sz = str.size();
	if (pos > sz) pos = sz;
	if (pos + n > sz) n = sz - pos;
	std::string::const_iterator it  = str.begin() + pos; 
	std::string::const_iterator end = str.begin() + pos + n;
	std::locale loc;
	while (it != end && *ptr)
	{
        std::string::value_type c1 = tolower(*it, loc);
        std::string::value_type c2 = tolower(*ptr, loc);
        if (c1 < c2)
            return -1;
        else if (c1 > c2)
            return 1;
        ++it; ++ptr;
	}
    
    if (it == end)
		return *ptr == 0 ? 0 : -1;
    else
        return 1;
}


int icompare(const std::string& str, std::string::size_type pos, const std::string::value_type* ptr)
{
	return icompare(str, pos, str.size() - pos, ptr);
}


int icompare(const std::string& str, const std::string::value_type* ptr)
{
	return icompare(str, 0, str.size(), ptr);
}


#endif


Foundation_END
