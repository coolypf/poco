//
// HTTPStreamFactory.h
//
// $Id: //poco/1.2/Net/include/Poco/Net/HTTPStreamFactory.h#1 $
//
// Library: Net
// Package: HTTP
// Module:  HTTPStreamFactory
//
// Definition of the HTTPStreamFactory class.
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


#ifndef Net_HTTPStreamFactory_INCLUDED
#define Net_HTTPStreamFactory_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/HTTPSession.h"
#include "Poco/URIStreamFactory.h"


namespace Poco {
namespace Net {


class Net_API HTTPStreamFactory: public Poco::URIStreamFactory
	/// An implementation of the URIStreamFactory interface
	/// that handles Hyper-Text Transfer Protocol (http) URIs.
{
public:
	HTTPStreamFactory();
		/// Creates the HTTPStreamFactory.

	HTTPStreamFactory(const std::string& proxyHost, Poco::UInt16 proxyPort = HTTPSession::HTTP_PORT);
		/// Creates the HTTPStreamFactory.
		///
		/// HTTP connections will use the given proxy.

	virtual ~HTTPStreamFactory();
		/// Destroys the HTTPStreamFactory.
		
	virtual std::istream* open(const Poco::URI& uri);
		/// Creates and opens a HTTP stream for the given URI.
		/// The URI must be a http://... URI.
		///
		/// Throws a NetException if anything goes wrong.
		///
		/// Redirect responses are handled and the redirect
		/// location is automatically resolved, as long
		/// as the redirect location is still accessible
		/// via the HTTP protocol. If a redirection to
		/// a non http://... URI is received, a 
		/// UnsupportedRedirectException exception is thrown.
		/// The offending URI can then be obtained via the message()
		/// method of UnsupportedRedirectException.
		
	static void registerFactory();
		/// Registers the HTTPStreamFactory with the
		/// default URIStreamOpener instance.	
		
private:
	enum
	{
		MAX_REDIRECTS = 10
	};
	
	std::string  _proxyHost;
	Poco::UInt16 _proxyPort;
};


} } // namespace Poco::Net


#endif // Net_HTTPStreamFactory_INCLUDED
