//
// XMLString.cpp
//
// $Id: //poco/1.1.0/XML/src/XMLString.cpp#2 $
//
// Library: XML
// Package: XML
// Module:  XMLString
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


#include "XML/XMLString.h"


#if defined(XML_UNICODE_WCHAR_T)
#include <stdlib.h>
#endif


XML_BEGIN


#if defined(XML_UNICODE_WCHAR_T)


std::string fromXMLString(const XMLString& str)
{
	std::string result;
	result.reserve(str.size());
	
	for (XMLString::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		char c;
		wctomb(&c, *it);
		result += c;
	}
	return result;
}


XMLString toXMLString(const std::string& str)
{
	XMLString result;
	result.reserve(str.size());
	
	for (std::string::const_iterator it = str.begin(); it != str.end();)
	{
		wchar_t c;
		int n = mbtowc(&c, &*it, MB_CUR_MAX);
		result += c;
		it += (n > 0 ? n : 1);
	}
	return result;
}


#endif // XML_UNICODE_WCHAR_T


XML_END
