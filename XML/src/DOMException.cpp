//
// DOMException.cpp
//
// $Id: //poco/1.1.0/XML/src/DOMException.cpp#2 $
//
// Library: XML
// Package: DOM
// Module:  DOM
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


#include "DOM/DOMException.h"
#include <typeinfo>


XML_BEGIN


const std::string DOMException::MESSAGES[_NUMBER_OF_MESSAGES] =
{
	"Invalid DOM exception code",
	"Index or size is negative or greater than allowed value",
	"The specified range of text does not fit into a DOMString",
	"A node is inserted somewhere it doesn't belong",
	"A node is used in a different document than the one that created it",
	"An invalid character is specified",
	"Data is specified for a node which does not support data",
	"An attempt is made to modify an object where modifications are not allowed",
	"An attempt was made to reference a node in a context where it does not exist",
	"The implementation does not support the type of object requested",
	"An attempt is made to add an attribute that is already in use elsewhere",
	"A parameter or an operation is not supported by the underlying object",
	"An invalid or illegal string is specified",
	"An attempt is made to modify the type of the underlying object",
	"An attempt is made to create or change an object in a way which is incorrect with regard to namespaces",
	"An attempt is made to use an object that is not, or is no longer, usable"
};


DOMException::DOMException(unsigned short code):
	XMLException(message(code)),
	_code(code)
{
}

	
DOMException::DOMException(const DOMException& exc):
	XMLException(exc),
	_code(exc._code)
{
}

	
DOMException::~DOMException() throw()
{
}

	
DOMException& DOMException::operator = (const DOMException& exc)
{
	if (&exc != this)
	{
		XMLException::operator = (exc);
		_code = exc._code;
	}
	return *this;
}


const char* DOMException::name() const throw()
{
	return "DOMException";
}


const char* DOMException::className() const throw()
{
	return typeid(*this).name();
}


Foundation::Exception* DOMException::clone() const
{
	return new DOMException(*this);
}


const std::string& DOMException::message(unsigned short code)
{
	if (code >= 1 && code < _NUMBER_OF_MESSAGES)
		return MESSAGES[code];
	else
		return MESSAGES[0];
}


XML_END
