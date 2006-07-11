//
// HTTPServerParams.h
//
// $Id: //poco/1.1.0/Net/include/Net/HTTPServerParams.h#2 $
//
// Library: Net
// Package: HTTPServer
// Module:  HTTPServerParams
//
// Definition of the HTTPServerParams class.
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


#ifndef Net_HTTPServerParams_INCLUDED
#define Net_HTTPServerParams_INCLUDED


#ifndef Net_Net_INCLUDED
#include "Net/Net.h"
#endif
#ifndef Net_TCPServerParams_INCLUDED
#include "Net/TCPServerParams.h"
#endif


Net_BEGIN


class Net_API HTTPServerParams: public TCPServerParams
	/// This class is used to specify parameters to both the
	/// HTTPServer, as well as to HTTPRequestHandler objects.
	///
	/// Subclasses may add new parameters to the class.
{
public:
	HTTPServerParams();
		/// Creates the HTTPServerParams.
		///
		/// Sets the following default values:
		///   - timeout:              60 seconds
		///   - keepAlive:            true
		///   - maxKeepAliveRequests: 0
		///   - keepAliveTimeout:     10 seconds
		
	void setServerName(const std::string& serverName);
		/// Sets the name and port (name:port) that the server uses to identify itself.
		///
		/// If this is not set to valid DNS name for your host, server-generated
		/// redirections will not work.
		
	const std::string& getServerName() const;
		/// Returns the name and port (name:port) that the server uses to identify itself.

	void setSoftwareVersion(const std::string& softwareVersion);
		/// Sets the server software name and version that the server uses to identify
		/// itself. If this is set to a non-empty string, the server will
		/// automatically include a Server header field with the value given
		/// here in every response it sends.
		///
		/// The format of the softwareVersion string should be name/version
		/// (e.g. MyHTTPServer/1.0).

	const std::string& getSoftwareVersion() const;
		/// Returns the server software name and version that the server uses to
		/// identify itself.

	void setTimeout(const Foundation::Timespan& timeout);
		/// Sets the connection timeout for HTTP connections.
		
	const Foundation::Timespan& getTimeout() const;
		/// Returns the connection timeout for HTTP connections.
		
	void setKeepAlive(bool keepAlive);
		/// Enables (keepAlive == true) or disables (keepAlive == false)
		/// persistent connections.
		
	bool getKeepAlive() const;
		/// Returns true iff persistent connections are enabled.
		
	void setKeepAliveTimeout(const Foundation::Timespan& timeout);
		/// Sets the connection timeout for HTTP connections.
		
	const Foundation::Timespan& getKeepAliveTimeout() const;
		/// Returns the connection timeout for HTTP connections.
	
	void setMaxKeepAliveRequests(int maxKeepAliveRequests);
		/// Specifies the maximun number of requests allowed
		/// during a persistent connection. 0 means unlimited
		/// connections.
		
	int getMaxKeepAliveRequests() const;
		/// Returns the maximum number of requests allowed
		/// during a persistent connection, or 0 if
		/// unlimited connections are allowed.

protected:
	virtual ~HTTPServerParams();
		/// Destroys the HTTPServerParams.

private:
	std::string          _serverName;
	std::string          _softwareVersion;
	Foundation::Timespan _timeout;
	bool                 _keepAlive;
	int                  _maxKeepAliveRequests;
	Foundation::Timespan _keepAliveTimeout;
};


//
// inlines
//
inline const std::string& HTTPServerParams::getServerName() const
{
	return _serverName;
}


inline const std::string& HTTPServerParams::getSoftwareVersion() const
{
	return _softwareVersion;
}


inline const Foundation::Timespan& HTTPServerParams::getTimeout() const
{
	return _timeout;
}


inline bool HTTPServerParams::getKeepAlive() const
{
	return _keepAlive;
}


inline int HTTPServerParams::getMaxKeepAliveRequests() const
{
	return _maxKeepAliveRequests;
}


inline const Foundation::Timespan& HTTPServerParams::getKeepAliveTimeout() const
{
	return _keepAliveTimeout;
}


Net_END


#endif // Net_HTTPServerParams_INCLUDED
