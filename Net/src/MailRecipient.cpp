//
// MailRecipient.cpp
//
// $Id: //poco/svn/Net/src/MailRecipient.cpp#2 $
//
// Library: Net
// Package: Mail
// Module:  MailRecipient
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


#include "Poco/Net/MailRecipient.h"
#include <algorithm>


namespace Poco {
namespace Net {


MailRecipient::MailRecipient():
	_type(PRIMARY_RECIPIENT)
{
}

	
MailRecipient::MailRecipient(const MailRecipient& recipient):
	_address(recipient._address),
	_realName(recipient._realName),
	_type(recipient._type)
{
}

	
MailRecipient::MailRecipient(RecipientType type, const std::string& address):
	_address(address),
	_type(type)
{
}


MailRecipient::MailRecipient(RecipientType type, const std::string& address, const std::string& realName):
	_address(address),
	_realName(realName),
	_type(type)
{
}


MailRecipient::~MailRecipient()
{
}

	
MailRecipient& MailRecipient::operator = (const MailRecipient& recipient)
{
	if (this != &recipient)
	{
		MailRecipient tmp(recipient);
		swap(tmp);
	}
	return *this;
}


void MailRecipient::swap(MailRecipient& recipient)
{
	std::swap(_type, recipient._type);
	std::swap(_address, recipient._address);
	std::swap(_realName, recipient._realName);
}

	
void MailRecipient::setType(RecipientType type)
{
	_type = type;
}

	
void MailRecipient::setAddress(const std::string& address)
{
	_address = address;
}

	
void MailRecipient::setRealName(const std::string& realName)
{
	_realName = realName;
}


} } // namespace Poco::Net
