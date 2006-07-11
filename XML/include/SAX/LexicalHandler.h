//
// LexicalHandler.h
//
// $Id: //poco/1.1.0/XML/include/SAX/LexicalHandler.h#2 $
//
// Library: XML
// Package: SAX
// Module:  SAX
//
// SAX2-ext LexicalHandler Interface.
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


#ifndef SAX_LexicalHandler_INCLUDED
#define SAX_LexicalHandler_INCLUDED


#ifndef XML_XML_INCLUDED
#include "XML/XML.h"
#endif
#ifndef XML_XMLString_INCLUDED
#include "XML/XMLString.h"
#endif


XML_BEGIN


class XML_API LexicalHandler
	/// This is an optional extension handler for SAX2 to provide lexical information 
	/// about an XML document, such as comments and CDATA section boundaries. 
	/// XML readers are not required to recognize this handler, and it is not part of 
	/// core-only SAX2 distributions.
	/// 
	/// The events in the lexical handler apply to the entire document, not just to the 
	/// document element, and all lexical handler events must appear between the content 
	/// handler's startDocument and endDocument events.
	/// 
	/// To set the LexicalHandler for an XML reader, use the setProperty method with the 
	/// property name http://xml.org/sax/properties/lexical-handler and an object implementing 
	/// this interface (or null) as the value. If the reader does not report lexical events, 
	/// it will throw a SAXNotRecognizedException when you attempt to register the handler.
{
public:
	virtual void startDTD(const XMLString& name, const XMLString& publicId, const XMLString& systemId) = 0;
		/// Report the start of DTD declarations, if any.
		/// 
		/// This method is intended to report the beginning of the DOCTYPE declaration; 
		/// if the document has no DOCTYPE declaration, this method will not be invoked.
		/// 
		/// All declarations reported through DTDHandler or DeclHandler events must appear 
		/// between the startDTD and endDTD events. Declarations are assumed to belong to 
		/// the internal DTD subset unless they appear between startEntity and endEntity 
		/// events. Comments and processing instructions from the DTD should also be reported 
		/// between the startDTD and endDTD events, in their original order of (logical) occurrence; 
		/// they are not required to appear in their correct locations relative to DTDHandler or 
		/// DeclHandler events, however.
		/// 
		/// Note that the start/endDTD events will appear within the start/endDocument events from 
		/// ContentHandler and before the first startElement event.

	virtual void endDTD() = 0;
		/// Report the end of DTD declarations.
		/// 
		/// This method is intended to report the end of the DOCTYPE declaration; if the document 
		/// has no DOCTYPE declaration, this method will not be invoked.

	virtual void startEntity(const XMLString& name) = 0;
		/// Report the beginning of some internal and external XML entities.
		/// 
		/// The reporting of parameter entities (including the external DTD subset) is optional, 
		/// and SAX2 drivers that report LexicalHandler events may not implement it; you can use the 
		/// http://xml.org/sax/features/lexical-handler/parameter-entities feature to query or control 
		/// the reporting of parameter entities.
		/// 
		/// General entities are reported with their regular names, parameter entities have '%' 
		/// prepended to their names, and the external DTD subset has the pseudo-entity name "[dtd]".
		/// 
		/// When a SAX2 driver is providing these events, all other events must be properly nested 
		/// within start/end entity events. There is no additional requirement that events from 
		/// DeclHandler or DTDHandler be properly ordered.
		/// 
		/// Note that skipped entities will be reported through the skippedEntity event, which is part of 
		/// the ContentHandler interface.
		/// 
		/// Because of the streaming event model that SAX uses, some entity boundaries cannot be reported under 
		/// any circumstances:
		/// 
		///     * general entities within attribute values
		///     * parameter entities within declarations
		///
		/// These will be silently expanded, with no indication of where the original entity boundaries were.
		/// 
		/// Note also that the boundaries of character references (which are not really entities anyway) are not reported.
		/// 
		/// All start/endEntity events must be properly nested. 

	virtual void endEntity(const XMLString& name) = 0;
		/// Report the end of an entity.
		
	virtual void startCDATA() = 0;
		/// Report the start of a CDATA section.
		///
		/// The contents of the CDATA section will be reported through the regular characters event; 
		/// this event is intended only to report the boundary.

	virtual void endCDATA() = 0;
		/// Report the end of a CDATA section.
		
	virtual void comment(const XMLChar ch[], int start, int length) = 0;
		/// Report an XML comment anywhere in the document.
		/// 
		/// This callback will be used for comments inside or outside the document element, 
		/// including comments in the external DTD subset (if read). Comments in the DTD must 
		/// be properly nested inside start/endDTD and start/endEntity events (if used).

protected:
	virtual ~LexicalHandler();
};


XML_END


#endif // SAX_LexicalHandler_INCLUDED
