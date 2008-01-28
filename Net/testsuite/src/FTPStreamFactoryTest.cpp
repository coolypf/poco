//
// FTPStreamFactoryTest.cpp
//
// $Id: //poco/svn/Net/testsuite/src/FTPStreamFactoryTest.cpp#2 $
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


#include "FTPStreamFactoryTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "DialogServer.h"
#include "Poco/Net/FTPStreamFactory.h"
#include "Poco/Net/DialogSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetException.h"
#include "Poco/URI.h"
#include "Poco/StreamCopier.h"
#include <sstream>
#include <memory>


using Poco::Net::FTPStreamFactory;
using Poco::Net::FTPPasswordProvider;
using Poco::Net::DialogSocket;
using Poco::Net::SocketAddress;
using Poco::Net::FTPException;
using Poco::URI;
using Poco::StreamCopier;


namespace
{
	class TestPasswordProvider: public FTPPasswordProvider
	{
	public:
		std::string password(const std::string& username, const std::string& host)
		{
			return "secret";
		}
	};
}


FTPStreamFactoryTest::FTPStreamFactoryTest(const std::string& name): CppUnit::TestCase(name)
{
}


FTPStreamFactoryTest::~FTPStreamFactoryTest()
{
}


void FTPStreamFactoryTest::testDownload()
{
	FTPStreamFactory::setPasswordProvider(0);

	DialogServer server;
	server.addResponse("220 localhost FTP ready");
	server.addResponse("331 Password required");
	server.addResponse("230 Welcome");
	server.addResponse("200 Type set to I");
	server.addResponse("200 Type set to A");

	DialogServer dataServer(false);
	dataServer.addResponse("line1\r\nline2");
	std::ostringstream epsv;
	epsv << "229 Entering Extended Passive Mode (|||" << dataServer.port() << "|)";
	server.addResponse(epsv.str());
	server.addResponse("150 sending data\r\n226 Transfer complete");
	server.addResponse("221 Good bye");

	URI uri;
	uri.setScheme("ftp");
	uri.setHost("localhost");
	uri.setPort(server.port());
	uri.setPath("/test.txt;type=a");
	FTPStreamFactory sf;
	std::auto_ptr<std::istream> pStr(sf.open(uri));

	std::ostringstream dataStr;
	StreamCopier::copyStream(*pStr.get(), dataStr);
	
	pStr.reset();
		
	std::string s(dataStr.str());
	assert (s == "line1\r\nline2\r\n");
}


void FTPStreamFactoryTest::testList()
{
	FTPStreamFactory::setPasswordProvider(0);

	DialogServer server;
	server.addResponse("220 localhost FTP ready");
	server.addResponse("331 Password required");
	server.addResponse("230 Welcome");
	server.addResponse("200 Type set to I");
	server.addResponse("250 CWD OK");
	server.addResponse("250 CWD OK");

	DialogServer dataServer(false);
	dataServer.addResponse("file1\r\nfile2");
	std::ostringstream epsv;
	epsv << "229 Entering Extended Passive Mode (|||" << dataServer.port() << "|)";
	server.addResponse(epsv.str());
	server.addResponse("150 sending data\r\n226 Transfer complete");
	server.addResponse("221 Good bye");

	URI uri;
	uri.setScheme("ftp");
	uri.setHost("localhost");
	uri.setPort(server.port());
	uri.setPath("/usr/guest/data;type=d");
	FTPStreamFactory sf;
	std::auto_ptr<std::istream> pStr(sf.open(uri));

	std::ostringstream dataStr;
	StreamCopier::copyStream(*pStr.get(), dataStr);
	
	pStr.reset();
		
	std::string s(dataStr.str());
	assert (s == "file1\r\nfile2\r\n");
}


void FTPStreamFactoryTest::testUserInfo()
{
	FTPStreamFactory::setPasswordProvider(0);

	DialogServer server;
	server.addResponse("220 localhost FTP ready");
	server.addResponse("331 Password required");
	server.addResponse("230 Welcome");
	server.addResponse("200 Type set to I");
	server.addResponse("200 Type set to A");

	DialogServer dataServer(false);
	dataServer.addResponse("line1\r\nline2");
	std::ostringstream epsv;
	epsv << "229 Entering Extended Passive Mode (|||" << dataServer.port() << "|)";
	server.addResponse(epsv.str());
	server.addResponse("150 sending data\r\n226 Transfer complete");
	server.addResponse("221 Good bye");

	URI uri;
	uri.setScheme("ftp");
	uri.setHost("localhost");
	uri.setPort(server.port());
	uri.setPath("/test.txt;type=a");
	uri.setUserInfo("user:secret");
	FTPStreamFactory sf;
	std::auto_ptr<std::istream> pStr(sf.open(uri));

	std::ostringstream dataStr;
	StreamCopier::copyStream(*pStr.get(), dataStr);
	
	pStr.reset();
		
	std::string s(dataStr.str());
	assert (s == "line1\r\nline2\r\n");
}


void FTPStreamFactoryTest::testPasswordProvider()
{
	static TestPasswordProvider tpp;
	FTPStreamFactory::setPasswordProvider(&tpp);

	DialogServer server;
	server.addResponse("220 localhost FTP ready");
	server.addResponse("331 Password required");
	server.addResponse("230 Welcome");
	server.addResponse("200 Type set to I");
	server.addResponse("200 Type set to A");

	DialogServer dataServer(false);
	dataServer.addResponse("line1\r\nline2");
	std::ostringstream epsv;
	epsv << "229 Entering Extended Passive Mode (|||" << dataServer.port() << "|)";
	server.addResponse(epsv.str());
	server.addResponse("150 sending data\r\n226 Transfer complete");
	server.addResponse("221 Good bye");

	URI uri;
	uri.setScheme("ftp");
	uri.setHost("localhost");
	uri.setPort(server.port());
	uri.setPath("/test.txt;type=a");
	uri.setUserInfo("user");
	FTPStreamFactory sf;
	std::auto_ptr<std::istream> pStr(sf.open(uri));

	std::ostringstream dataStr;
	StreamCopier::copyStream(*pStr.get(), dataStr);
	
	pStr.reset();
		
	std::string s(dataStr.str());
	assert (s == "line1\r\nline2\r\n");
}


void FTPStreamFactoryTest::testMissingPasswordProvider()
{
	FTPStreamFactory::setPasswordProvider(0);

	DialogServer server;
	server.addResponse("220 localhost FTP ready");
	server.addResponse("221 Good bye");

	URI uri;
	uri.setScheme("ftp");
	uri.setHost("localhost");
	uri.setPort(server.port());
	uri.setPath("/test.txt;type=a");
	uri.setUserInfo("user");

	try
	{
		FTPStreamFactory sf;
		std::auto_ptr<std::istream> pStr(sf.open(uri));
		fail("no password provider - must throw");
	}
	catch (FTPException&)
	{
	}
}


void FTPStreamFactoryTest::setUp()
{
}


void FTPStreamFactoryTest::tearDown()
{
}


CppUnit::Test* FTPStreamFactoryTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("FTPStreamFactoryTest");

	CppUnit_addTest(pSuite, FTPStreamFactoryTest, testDownload);
	CppUnit_addTest(pSuite, FTPStreamFactoryTest, testList);
	CppUnit_addTest(pSuite, FTPStreamFactoryTest, testUserInfo);
	CppUnit_addTest(pSuite, FTPStreamFactoryTest, testPasswordProvider);
	CppUnit_addTest(pSuite, FTPStreamFactoryTest, testMissingPasswordProvider);

	return pSuite;
}
