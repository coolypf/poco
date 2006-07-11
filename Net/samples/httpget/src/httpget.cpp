//
// httpget.cpp
//
// $Id: //poco/1.1.0/Net/samples/httpget/src/httpget.cpp#2 $
//
// This sample demonstrates the HTTPClientSession class.
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


#include "Net/HTTPClientSession.h"
#include "Net/HTTPRequest.h"
#include "Net/HTTPResponse.h"
#include "Foundation/StreamCopier.h"
#include "Foundation/Path.h"
#include "Foundation/URI.h"
#include "Foundation/Exception.h"
#include <iostream>


using Net::HTTPClientSession;
using Net::HTTPRequest;
using Net::HTTPResponse;
using Net::HTTPMessage;
using Foundation::StreamCopier;
using Foundation::Path;
using Foundation::URI;
using Foundation::Exception;


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		Path p(argv[0]);
		std::cout << "usage: " << p.getBaseName() << " <uri>" << std::endl;
		std::cout << "       fetches the resource identified by <uri> and print it to the standard output" << std::endl;
		return 1;
	}

	try
	{
		URI uri(argv[1]);
		std::string path(uri.getPathAndQuery());
		if (path.empty()) path = "/";

		HTTPClientSession session(uri.getHost(), uri.getPort());
		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		session.sendRequest(req);
		HTTPResponse res;
		std::istream& rs = session.receiveResponse(res);
		std::cout << res.getStatus() << " " << res.getReason() << std::endl;
		StreamCopier::copyStream(rs, std::cout);
	}
	catch (Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return 1;
	}
	return 0;
}
