//
// FTPClientSession.cpp
//
// $Id: //poco/1.2/Net/src/FTPClientSession.cpp#1 $
//
// Library: Net
// Package: FTP
// Module:  FTPClientSession
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


#include "Poco/Net/FTPClientSession.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/NumberFormatter.h"
#include <ctype.h>


using Poco::NumberFormatter;


namespace Poco {
namespace Net {


FTPClientSession::FTPClientSession(const StreamSocket& socket):
	_controlSocket(socket),
	_pDataStream(0),
	_passiveMode(true),
	_fileType(TYPE_BINARY),
	_supports1738(true),
	_isOpen(true),
	_timeout(DEFAULT_TIMEOUT)
{
	_controlSocket.setReceiveTimeout(_timeout);
}

	
FTPClientSession::FTPClientSession(const std::string& host, Poco::UInt16 port):
	_controlSocket(SocketAddress(host, port)),
	_pDataStream(0),
	_passiveMode(true),
	_fileType(TYPE_BINARY),
	_supports1738(true),
	_isOpen(true),
	_timeout(DEFAULT_TIMEOUT)
{
	_controlSocket.setReceiveTimeout(_timeout);
}


FTPClientSession::~FTPClientSession()
{
	try
	{
		close();
	}
	catch (...)
	{
	}
}


void FTPClientSession::setTimeout(const Poco::Timespan& timeout)
{
	_timeout = timeout;
	_controlSocket.setReceiveTimeout(timeout);
}

	
Poco::Timespan FTPClientSession::getTimeout() const
{
	return _timeout;
}


void FTPClientSession::setPassive(bool flag)
{
	_passiveMode = flag;
}

	
bool FTPClientSession::getPassive() const
{
	return _passiveMode;
}


void FTPClientSession::login(const std::string& username, const std::string& password)
{
	std::string response;
	int status = _controlSocket.receiveStatusMessage(response);
	if (!isPositiveCompletion(status)) throw FTPException("Cannot login to server", response);
	status = sendCommand("USER", username, response);
	if (isPositiveIntermediate(status))
		status = sendCommand("PASS", password, response);
	if (!isPositiveCompletion(status)) throw FTPException("Login denied", response);
	setFileType(_fileType);
}


void FTPClientSession::close()
{
	if (_isOpen)
	{
		try
		{
			endTransfer(); 
		}
		catch (...)
		{
		}
		std::string response;
		sendCommand("QUIT", response);
		_controlSocket.close();
		_isOpen = false;
	}
}


void FTPClientSession::setFileType(FTPClientSession::FileType type)
{
	std::string response;
	int status = sendCommand("TYPE", (type == TYPE_TEXT ? "A" : "I"), response);
	if (!isPositiveCompletion(status)) throw FTPException("Cannot set file type", response);
	_fileType = type;
}


FTPClientSession::FileType FTPClientSession::getFileType() const
{
	return _fileType;
}


std::string FTPClientSession::systemType()
{
	std::string response;
	int status = sendCommand("SYST", response);
	if (isPositiveCompletion(status))
		return response.substr(4);
	else
		throw FTPException("Cannot get remote system type", response);
}


void FTPClientSession::setWorkingDirectory(const std::string& path)
{
	std::string response;
	int status = sendCommand("CWD", path, response);
	if (!isPositiveCompletion(status)) throw FTPException("Cannot change directory", response);
}


std::string FTPClientSession::getWorkingDirectory()
{
	std::string response;
	int status = sendCommand("PWD", response);
	if (isPositiveCompletion(status))
		return extractPath(response);
	else
		throw FTPException("Cannot get current working directory", response);
}


void FTPClientSession::cdup()
{
	std::string response;
	int status = sendCommand("CDUP", response);
	if (!isPositiveCompletion(status)) throw FTPException("Cannot change directory", response);
}

	
void FTPClientSession::rename(const std::string& oldName, const std::string& newName)
{
	std::string response;
	int status = sendCommand("RNFR", oldName, response);
	if (!isPositiveIntermediate(status)) throw FTPException(std::string("Cannot rename ") + oldName, response);
	status = sendCommand("RNTO", newName, response);
	if (!isPositiveCompletion(status)) throw FTPException(std::string("Cannot rename to ") + newName, response);
}

	
void FTPClientSession::remove(const std::string& path)
{
	std::string response;
	int status = sendCommand("DELE", path, response);
	if (!isPositiveCompletion(status)) throw FTPException(std::string("Cannot remove " + path), response);
}


void FTPClientSession::createDirectory(const std::string& path)
{
	std::string response;
	int status = sendCommand("MKD", path, response);
	if (!isPositiveCompletion(status)) throw FTPException(std::string("Cannot create directory ") + path, response);
}


void FTPClientSession::removeDirectory(const std::string& path)
{
	std::string response;
	int status = sendCommand("RMD", path, response);
	if (!isPositiveCompletion(status)) throw FTPException(std::string("Cannot remove directory ") + path, response);
}


std::istream& FTPClientSession::beginDownload(const std::string& path)
{
	delete _pDataStream;
	_pDataStream = 0;
	_pDataStream = new SocketStream(establishDataConnection("RETR", path));
	return *_pDataStream;
}

	
void FTPClientSession::endDownload()
{
	endTransfer();
}

	
std::ostream& FTPClientSession::beginUpload(const std::string& path)
{
	delete _pDataStream;
	_pDataStream = 0;
	_pDataStream = new SocketStream(establishDataConnection("STOR", path));
	return *_pDataStream;
}


void FTPClientSession::endUpload()
{
	endTransfer();
}


std::istream& FTPClientSession::beginList(const std::string& path, bool extended)
{
	delete _pDataStream;
	_pDataStream = 0;
	_pDataStream = new SocketStream(establishDataConnection(extended ? "LIST" : "NLST", path));
	return *_pDataStream;
}


void FTPClientSession::endList()
{
	endTransfer();
}

	
void FTPClientSession::abort()
{
	_controlSocket.sendByte(DialogSocket::TELNET_IP);
	_controlSocket.synch();
	std::string response;
	int status = sendCommand("ABOR", response);
	if (status == 426)
		status = _controlSocket.receiveStatusMessage(response);
	if (status != 226) throw FTPException("Cannot abort transfer", response);
}


int FTPClientSession::sendCommand(const std::string& command, std::string& response)
{
	_controlSocket.sendMessage(command);
	return _controlSocket.receiveStatusMessage(response);
}


int FTPClientSession::sendCommand(const std::string& command, const std::string& arg, std::string& response)
{
	_controlSocket.sendMessage(command, arg);
	return _controlSocket.receiveStatusMessage(response);
}


std::string FTPClientSession::extractPath(const std::string& response)
{
	std::string path;
	std::string::const_iterator it  = response.begin();
	std::string::const_iterator end = response.end();
	while (it != end && *it != '"') ++it;
	if (it != end)
	{
		++it;
		while (it != end)
		{
			if (*it == '"')
			{
				++it;
				if (it != end && *it != '"') break;
			}
			path += *it++;
		}
	}
	return path;
}


StreamSocket FTPClientSession::establishDataConnection(const std::string& command, const std::string& arg)
{
	if (_passiveMode)
		return passiveDataConnection(command, arg);
	else
		return activeDataConnection(command, arg);
}


StreamSocket FTPClientSession::activeDataConnection(const std::string& command, const std::string& arg)
{
	ServerSocket server(SocketAddress(_controlSocket.address().host(), 0));
	sendPortCommand(server.address());
	std::string response;
	int status = sendCommand(command, arg, response);
	if (!isPositivePreliminary(status)) throw FTPException(command + " command failed", response);
	if (server.poll(_timeout, Socket::SELECT_READ))
		return server.acceptConnection();
	else
		throw FTPException("The server has not initiated a data connection");
}


StreamSocket FTPClientSession::passiveDataConnection(const std::string& command, const std::string& arg)
{
	SocketAddress sa(sendPassiveCommand());
	StreamSocket sock(sa);
	std::string response;
	int status = sendCommand(command, arg, response);
	if (!isPositivePreliminary(status)) throw FTPException(command + " command failed", response);
	return sock;
}


void FTPClientSession::sendPortCommand(const SocketAddress& addr)
{
	if (_supports1738)
	{
		if (sendEPRT(addr))
			return;
		else
			_supports1738 = false;
	}
	sendPORT(addr);
}


SocketAddress FTPClientSession::sendPassiveCommand()
{
	SocketAddress addr;
	if (_supports1738)
	{
		if (sendEPSV(addr))
			return addr;
		else
			_supports1738 = false;
	}
	sendPASV(addr);
	return addr;
}


bool FTPClientSession::sendEPRT(const SocketAddress& addr)
{
	std::string arg("|");
	arg += addr.af() == AF_INET ? '1' : '2';
	arg += '|';
	arg += addr.host().toString();
	arg += '|';
	arg += NumberFormatter::format(addr.port());
	arg += '|';
	std::string response;
	int status = sendCommand("EPRT", arg, response);
	if (isPositiveCompletion(status))
		return true;
	else if (isPermanentNegative(status))
		return false;
	else
		throw FTPException("EPRT command failed", response);
}


void FTPClientSession::sendPORT(const SocketAddress& addr)
{
	std::string arg(addr.host().toString());
	for (std::string::iterator it = arg.begin(); it != arg.end(); ++it)
	{
		if (*it == '.') *it = ',';
	}
	arg += ',';
	Poco::UInt16 port = addr.port();
	arg += NumberFormatter::format(port/256);
	arg += ',';
	arg += NumberFormatter::format(port % 256);
	std::string response;
	int status = sendCommand("PORT", arg, response);
	if (!isPositiveCompletion(status)) throw FTPException("PORT command failed", response);
}


bool FTPClientSession::sendEPSV(SocketAddress& addr)
{
	std::string response;
	int status = sendCommand("EPSV", response);
	if (isPositiveCompletion(status))
	{
		parseExtAddress(response, addr);
		return true;
	}
	else if (isPermanentNegative(status))
	{
		return false;
	}
	else throw FTPException("EPSV command failed", response);
}


void FTPClientSession::sendPASV(SocketAddress& addr)
{
	std::string response;
	int status = sendCommand("PASV", response);
	if (!isPositiveCompletion(status)) throw FTPException("PASV command failed", response);
	parseAddress(response, addr);
}


void FTPClientSession::parseAddress(const std::string& str, SocketAddress& addr)
{
	std::string::const_iterator it  = str.begin();
	std::string::const_iterator end = str.end();
	while (it != end && *it != '(') ++it;
	if (it != end) ++it;
	std::string host;
	while (it != end && isdigit(*it)) host += *it++;
	if (it != end && *it == ',') { host += '.'; ++it; }
	while (it != end && isdigit(*it)) host += *it++;
	if (it != end && *it == ',') { host += '.'; ++it; }
	while (it != end && isdigit(*it)) host += *it++;
	if (it != end && *it == ',') { host += '.'; ++it; }
	while (it != end && isdigit(*it)) host += *it++;
	if (it != end && *it == ',') ++it;
	Poco::UInt16 portHi = 0;
	while (it != end && isdigit(*it)) { portHi *= 10; portHi += *it++ - '0'; }
	if (it != end && *it == ',') ++it;
	Poco::UInt16 portLo = 0;
	while (it != end && isdigit(*it)) { portLo *= 10; portLo += *it++ - '0'; }
	addr = SocketAddress(host, portHi*256 + portLo);
}


void FTPClientSession::parseExtAddress(const std::string& str, SocketAddress& addr)
{
	std::string::const_iterator it  = str.begin();
	std::string::const_iterator end = str.end();
	while (it != end && *it != '(') ++it;
	if (it != end) ++it;
	char delim = '|';
	if (it != end) delim = *it++;
	if (it != end && *it == delim) ++it;
	if (it != end && *it == delim) ++it;
	Poco::UInt16 port = 0;
	while (it != end && isdigit(*it)) { port *= 10; port += *it++ - '0'; }	
	addr = SocketAddress(_controlSocket.peerAddress().host(), port);	
}


void FTPClientSession::endTransfer()
{
	if (_pDataStream)
	{
		delete _pDataStream;
		_pDataStream = 0;
		std::string response;
		int status = _controlSocket.receiveStatusMessage(response);
		if (!isPositiveCompletion(status)) throw FTPException("Data transfer failed", response);
	}
}


} } // namespace Poco::Net
