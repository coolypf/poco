//
// DocumentEvent.h
//
// $Id: //poco/1.2/XML/include/Poco/DOM/DocumentEvent.h#1 $
//
// Library: XML
// Package: DOM
// Module:  DOM
//
// Definition of the DOM DocumentEvent interface.
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


#ifndef DOM_DocumentEvent_INCLUDED
#define DOM_DocumentEvent_INCLUDED


#include "Poco/XML/XML.h"
#include "Poco/XML/XMLString.h"


namespace Poco {
namespace XML {


class Event;


class XML_API DocumentEvent
	/// The DocumentEvent interface provides a mechanism by which the user can create
	/// an Event of a type supported by the implementation. It is expected that
	/// the DocumentEvent interface will be implemented on the same object which
	/// implements the Document interface in an implementation which supports the
	/// Event model.
{
public:
	virtual Event* createEvent(const XMLString& eventType) const = 0;
		/// Creates an event of the specified type.
		///
		/// The eventType parameter specifies the type of Event interface to be created.
		/// If the Event interface specified is supported by the implementation this
		/// method will return a new Event of the interface type requested. If the Event
		/// is to be dispatched via the dispatchEvent method the appropriate event init
		/// method must be called after creation in order to initialize the Event's
		/// values. As an example, a user wishing to synthesize some kind of UIEvent
		/// would call createEvent with the parameter "UIEvents". The initUIEvent method
		/// could then be called on the newly created UIEvent to set the specific type
		/// of UIEvent to be dispatched and set its context information.
		/// The createEvent method is used in creating Events when it is either inconvenient
		/// or unnecessary for the user to create an Event themselves. In cases where
		/// the implementation provided Event is insufficient, users may supply their
		/// own Event implementations for use with the dispatchEvent method.

protected:
	virtual ~DocumentEvent();
};


} } // namespace Poco::XML


#endif // DOM_DocumentEvent_INCLUDED
