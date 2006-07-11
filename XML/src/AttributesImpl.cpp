//
// AttributesImpl.cpp
//
// $Id: //poco/1.1.0/XML/src/AttributesImpl.cpp#2 $
//
// Library: XML
// Package: SAX
// Module:  SAX
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


#include "SAX/AttributesImpl.h"


XML_BEGIN


AttributesImpl::AttributesImpl()
{
}


AttributesImpl::AttributesImpl(const Attributes& attributes)
{
	setAttributes(attributes);
}


AttributesImpl::~AttributesImpl()
{
}


AttributesImpl& AttributesImpl::operator = (const AttributesImpl& attributes)
{
	if (&attributes != this)
	{
		_attributes = attributes._attributes;
	}
	return *this;
}


int AttributesImpl::getIndex(const XMLString& qname) const
{
	int i = 0;
	AttributeVec::const_iterator it;
	for (it = _attributes.begin(); it != _attributes.end(); ++it)
	{
		if (it->qname == qname) return i;
		++i;
	}
	return -1;
}


int AttributesImpl::getIndex(const XMLString& namespaceURI, const XMLString& localName) const
{
	int i = 0;
	AttributeVec::const_iterator it;
	for (it = _attributes.begin(); it != _attributes.end(); ++it)
	{
		if (it->namespaceURI == namespaceURI && it->localName == localName) return i;
		++i;
	}
	return -1;
}


int AttributesImpl::getLength() const
{
	return (int) _attributes.size();
}


XMLString AttributesImpl::getLocalName(int i) const
{
	poco_assert (i < _attributes.size());
	return _attributes[i].localName;
}


XMLString AttributesImpl::getQName(int i) const
{
	poco_assert (i < _attributes.size());
	return _attributes[i].qname;
}


XMLString AttributesImpl::getType(int i) const
{
	poco_assert (i < _attributes.size());
	return _attributes[i].type;
}


XMLString AttributesImpl::getType(const XMLString& qname) const
{
	Attribute* pAttr = find(qname);
	if (pAttr)
		return pAttr->type;
	else
		return XMLString();
}


XMLString AttributesImpl::getType(const XMLString& namespaceURI, const XMLString& localName) const
{
	Attribute* pAttr = find(namespaceURI, localName);
	if (pAttr)
		return pAttr->type;
	else
		return XMLString();
}


XMLString AttributesImpl::getValue(int i) const
{
	poco_assert (i < _attributes.size());
	return _attributes[i].value;
}


XMLString AttributesImpl::getValue(const XMLString& qname) const
{
	Attribute* pAttr = find(qname);
	if (pAttr)
		return pAttr->value;
	else
		return XMLString();
}


XMLString AttributesImpl::getValue(const XMLString& namespaceURI, const XMLString& localName) const
{
	Attribute* pAttr = find(namespaceURI, localName);
	if (pAttr)
		return pAttr->value;
	else
		return XMLString();
}


XMLString AttributesImpl::getURI(int i) const
{
	poco_assert (i < _attributes.size());
	return _attributes[i].namespaceURI;
}


bool AttributesImpl::isSpecified(int i) const
{
	poco_assert (i < _attributes.size());
	return _attributes[i].specified;
}


bool AttributesImpl::isSpecified(const XMLString& qname) const
{
	Attribute* pAttr = find(qname);
	if (pAttr)
		return pAttr->specified;
	else
		return false;
}


bool AttributesImpl::isSpecified(const XMLString& namespaceURI, const XMLString& localName) const
{
	Attribute* pAttr = find(namespaceURI, localName);
	if (pAttr)
		return pAttr->specified;
	else
		return false;
}


void AttributesImpl::setValue(int i, const XMLString& value)
{
	poco_assert (i < _attributes.size());
	_attributes[i].value     = value;
	_attributes[i].specified = true;
}


void AttributesImpl::setValue(const XMLString& qname, const XMLString& value)
{
	Attribute* pAttr = find(qname);
	if (pAttr)
	{
		pAttr->value     = value;
		pAttr->specified = true;
	}
}


void AttributesImpl::setValue(const XMLString& namespaceURI, const XMLString& localName, const XMLString& value)
{
	Attribute* pAttr = find(namespaceURI, localName);
	if (pAttr)
	{
		pAttr->value     = value;
		pAttr->specified = true;
	}
}


void AttributesImpl::setAttributes(const Attributes& attributes)
{
	if (&attributes != this)
	{
		int count = attributes.getLength();
		_attributes.clear();
		_attributes.reserve(count);
		for (int i = 0; i < count; i++)
		{
			addAttribute(attributes.getURI(i), attributes.getLocalName(i), attributes.getQName(i), attributes.getType(i), attributes.getValue(i));
		}
	}
}


void AttributesImpl::setAttribute(int i, const XMLString& namespaceURI, const XMLString& localName, const XMLString& qname, const XMLString& type, const XMLString& value)
{
	poco_assert (i < _attributes.size());
	_attributes[i].namespaceURI = namespaceURI;
	_attributes[i].localName    = localName;
	_attributes[i].qname        = qname;
	_attributes[i].type         = type;
	_attributes[i].value        = value;
	_attributes[i].specified    = true;
}


void AttributesImpl::addAttribute(const XMLString& namespaceURI, const XMLString& localName, const XMLString& qname, const XMLString& type, const XMLString& value)
{
	AttributeVec::iterator it = _attributes.insert(_attributes.end(), Attribute());
	it->namespaceURI = namespaceURI;
	it->localName    = localName;
	it->qname        = qname;
	it->value        = value;
	it->type         = type;
	it->specified    = true;
}


void AttributesImpl::addAttribute(const XMLString& namespaceURI, const XMLString& localName, const XMLString& qname, const XMLString& type, const XMLString& value, bool specified)
{
	AttributeVec::iterator it = _attributes.insert(_attributes.end(), Attribute());
	it->namespaceURI = namespaceURI;
	it->localName    = localName;
	it->qname        = qname;
	it->value        = value;
	it->type         = type;
	it->specified    = specified;
}


void AttributesImpl::addAttribute(const XMLChar* namespaceURI, const XMLChar* localName, const XMLChar* qname, const XMLChar* type, const XMLChar* value, bool specified)
{
	AttributeVec::iterator it = _attributes.insert(_attributes.end(), Attribute());
	it->namespaceURI = namespaceURI;
	it->localName    = localName;
	it->qname        = qname;
	it->value        = value;
	it->type         = type;
	it->specified    = specified;
}


void AttributesImpl::removeAttribute(int i)
{
	int cur = 0;
	for (AttributeVec::iterator it = _attributes.begin(); it != _attributes.end(); ++it, ++cur)
	{
		if (cur == i)
		{
			_attributes.erase(it);
			break;
		}
	}
}


void AttributesImpl::removeAttribute(const XMLString& qname)
{
	for (AttributeVec::iterator it = _attributes.begin(); it != _attributes.end(); ++it)
	{
		if (it->qname == qname)
		{
			_attributes.erase(it);
			break;
		}
	}
}


void AttributesImpl::removeAttribute(const XMLString& namespaceURI, const XMLString& localName)
{
	for (AttributeVec::iterator it = _attributes.begin(); it != _attributes.end(); ++it)
	{
		if (it->namespaceURI == namespaceURI && it->localName == localName)
		{
			_attributes.erase(it);
			break;
		}
	}
}


void AttributesImpl::clear()
{
	_attributes.clear();
}


void AttributesImpl::setLocalName(int i, const XMLString& localName)
{
	poco_assert (i < _attributes.size());
	_attributes[i].localName = localName;
}


void AttributesImpl::setQName(int i, const XMLString& qname)
{
	poco_assert (i < _attributes.size());
	_attributes[i].qname = qname;
}


void AttributesImpl::setType(int i, const XMLString& type)
{
	poco_assert (i < _attributes.size());
	_attributes[i].type = type;
}


void AttributesImpl::setURI(int i, const XMLString& namespaceURI)
{
	poco_assert (i < _attributes.size());
	_attributes[i].namespaceURI = namespaceURI;
}


AttributesImpl::Attribute* AttributesImpl::find(const XMLString& qname) const
{
	for (AttributeVec::const_iterator it = _attributes.begin(); it != _attributes.end(); ++it)
	{
		if (it->qname == qname) 
			return const_cast<Attribute*>(&(*it));
	}
	return 0;
}


AttributesImpl::Attribute* AttributesImpl::find(const XMLString& namespaceURI, const XMLString& localName) const
{
	for (AttributeVec::const_iterator it = _attributes.begin(); it != _attributes.end(); ++it)
	{
		if (it->namespaceURI == namespaceURI && it->localName == localName) 
			return const_cast<Attribute*>(&(*it));
	}
	return 0;
}


XML_END
