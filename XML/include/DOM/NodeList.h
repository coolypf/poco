//
// NodeList.h
//
// $Id: //poco/1.1.0/XML/include/DOM/NodeList.h#2 $
//
// Library: XML
// Package: DOM
// Module:  DOM
//
// Definition of the DOM NodeList interface.
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


#ifndef DOM_NodeList_INCLUDED
#define DOM_NodeList_INCLUDED


#ifndef XML_XML_INCLUDED
#include "XML/XML.h"
#endif
#ifndef DOM_DOMObject_INCLUDED
#include "DOM/DOMObject.h"
#endif


XML_BEGIN


class Node;


class XML_API NodeList: public DOMObject
	/// The NodeList interface provides the abstraction of an ordered
	/// collection of nodes, without defining or constraining how this
	/// collection is implemented.
	///
	/// The items in the NodeList are accessible via an integral index, 
	/// starting from 0.
	///
	/// A NodeList returned from a method must be released with a call to 
	/// release() when no longer needed.
{
public:
	virtual Node* item(unsigned long index) const = 0;
		/// Returns the index'th item in the collection. If index is
		/// greater than or equal to the number of nodes in the list,
		/// this returns null.

	virtual unsigned long length() const = 0;
		/// Returns the number of nodes in the list. The range of valid
		/// node indices is 0 to length - 1 inclusive.
	
protected:
	virtual ~NodeList();
};


XML_END


#endif // DOM_NodeList_INCLUDED
