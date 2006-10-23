//
// HTTPServerResponse.h
//
// $Id: //poco/1.2/Net/include/Poco/Net/HTTPServerResponse.h#1 $
//
// Library: Net
// Package: HTTPServer
// Module:  HTTPServerResponse
//
// Definition of the HTTPServerResponse class.
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


#ifndef Net_HTTPServerResponse_INCLUDED
#define Net_HTTPServerResponse_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/HTTPResponse.h"
#include <ostream>


namespace Poco {
namespace Net {


class HTTPServerSession;
class HTTPCookie;


class Net_API HTTPServerResponse: public HTTPResponse
	/// This subclass of HTTPResponse is used for
	/// representing server-side HTTP responses.
	///
	/// A HTTPServerResponse is passed to the
	/// handleRequest() method of HTTPRequestHandler.
	///
	/// handleRequest() must set a status code
	/// and optional reason phrase, set headers
	/// as necessary, and provide a message body.
{
public:
	HTTPServerResponse(HTTPServerSession& session);
		/// Creates the HTTPServerResponse.

	~HTTPServerResponse();
		/// Destroys the HTTPServerResponse.

	void sendContinue();
		/// Sends a 100 Continue response to the
		/// client.
		
	std::ostream& send();
		/// Sends the response header to the client and
		/// returns an output stream for sending the
		/// response body.
		///
		/// The returned stream is valid until the response
		/// object is destroyed.
		///
		/// Must not be called after sendFile() or redirect() 
		/// has been called.
		
	void sendFile(const std::string& path, const std::string& mediaType);
		/// Sends the response header to the client, followed
		/// by the content of the given file.
		///
		/// Must not be called after send() or redirect() 
		/// has been called.
		///
		/// Throws a FileNotFoundException if the file
		/// cannot be found, or an OpenFileException if
		/// the file cannot be opened.
		
	void redirect(const std::string& uri);
		/// Sets the status code to 302 (Found)
		/// and sets the "Location" header field
		/// to the given URI, which according to
		/// the HTTP specification, must be absolute.
		///
		/// Must not be called after send() has been called.
		
	void requireAuthentication(const std::string& realm);
		/// Sets the status code to 401 (Unauthorized)
		/// and sets the "WWW-Authenticate" header field
		/// according to the given realm.

private:
	HTTPServerSession& _session;
	std::ostream*      _pStream;
};


} } // namespace Poco::Net


#endif // Net_HTTPServerResponse_INCLUDED
