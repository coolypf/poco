//
// HTTPRequest.h
//
// $Id: //poco/1.2/Net/include/Poco/Net/HTTPRequest.h#1 $
//
// Library: Net
// Package: HTTP
// Module:  HTTPRequest
//
// Definition of the HTTPRequest class.
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


#ifndef Net_HTTPRequest_INCLUDED
#define Net_HTTPRequest_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/HTTPMessage.h"


namespace Poco {
namespace Net {


class Net_API HTTPRequest: public HTTPMessage
	/// This class encapsulates an HTTP request
	/// message.
	///
	/// In addition to the properties common to
	/// all HTTP messages, a HTTP request has
	/// a method (e.g. GET, HEAD, POST, etc.) and
	/// a request URI.
{
public:
	HTTPRequest();
		/// Creates a GET / HTTP/1.0 HTTP request.
		
	HTTPRequest(const std::string& version);
		/// Creates a GET / HTTP/1.x request with
		/// the given version (HTTP/1.0 or HTTP/1.1).
		
	HTTPRequest(const std::string& method, const std::string& uri);
		/// Creates a HTTP/1.0 request with the given method and URI.

	HTTPRequest(const std::string& method, const std::string& uri, const std::string& version);
		/// Creates a HTTP request with the given method, URI and version.

	virtual ~HTTPRequest();
		/// Destroys the HTTPRequest.

	void setMethod(const std::string& method);
		/// Sets the method.

	const std::string& getMethod() const;
		/// Returns the method.

	void setURI(const std::string& uri);
		/// Sets the request URI.
		
	const std::string& getURI() const;
		/// Returns the request URI.
		
	void setHost(const std::string& host);
		/// Sets the value of the Host header field.
		
	void setHost(const std::string& host, Poco::UInt16 port);
		/// Sets the value of the Host header field.
		
	const std::string& getHost() const;
		/// Returns the value of the Host header field.
		///
		/// Throws a NotFoundException if the request
		/// does not have a Host header field.

	void setCookies(const NameValueCollection& cookies);
		/// Adds a Cookie header with the names and
		/// values from cookies.
		
	void getCookies(NameValueCollection& cookies) const;
		/// Fills cookies with the cookies extracted
		/// from the Cookie headers in the request.

	bool hasCredentials() const;
		/// Returns true iff the request contains authentication
		/// information in the form of an Authorization header.
		
	void getCredentials(std::string& scheme, std::string& authInfo) const;
		/// Returns the authentication scheme and additional authentication
		/// information contained in this request.
		///
		/// Throws a NotAuthenticatedException if no authentication information
		/// is contained in the request.
		
	void setCredentials(const std::string& scheme, const std::string& authInfo);
		/// Sets the authentication scheme and information for
		/// this request.

	void write(std::ostream& ostr) const;
		/// Writes the HTTP request to the given
		/// output stream.

	void read(std::istream& istr);
		/// Reads the HTTP request from the
		/// given input stream.
		
	static const std::string HTTP_GET;
	static const std::string HTTP_HEAD;
	static const std::string HTTP_PUT;
	static const std::string HTTP_POST;
	static const std::string HTTP_OPTIONS;
	static const std::string HTTP_DELETE;
	static const std::string HTTP_TRACE;
	static const std::string HTTP_CONNECT;
	
	static const std::string HOST;
	static const std::string COOKIE;
	static const std::string AUTHORIZATION;

private:
	enum Limits
	{
		MAX_METHOD_LENGTH  = 32,
		MAX_URI_LENGTH     = 4096,
		MAX_VERSION_LENGTH = 8
	};
	
	std::string _method;
	std::string _uri;
};


//
// inlines
//
inline const std::string& HTTPRequest::getMethod() const
{
	return _method;
}


inline const std::string& HTTPRequest::getURI() const
{
	return _uri;
}


} } // namespace Poco::Net


#endif // Net_HTTPRequest_INCLUDED
