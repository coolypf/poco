//
// FTPClientSession.h
//
// $Id: //poco/1.1.0/Net/include/Net/FTPClientSession.h#2 $
//
// Library: Net
// Package: FTP
// Module:  FTPClientSession
//
// Definition of the FTPClientSession class.
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


#ifndef Net_FTPClientSession_INCLUDED
#define Net_FTPClientSession_INCLUDED


#ifndef Net_Net_INCLUDED
#include "Net/Net.h"
#endif
#ifndef Net_DialogSocket_INCLUDED
#include "Net/DialogSocket.h"
#endif
#ifndef Foundation_Timespan_INCLUDED
#include "Foundation/Timespan.h"
#endif
#ifndef STD_ISTREAM_INCLUDED
#include <istream>
#define STD_ISTREAM_INCLUDED
#endif
#ifndef STD_OSTREAM_INCLUDED
#include <ostream>
#define STD_OSTREAM_INCLUDED
#endif


Net_BEGIN


class SocketStream;


class Net_API FTPClientSession
	/// This class implements an File Transfer Protocol
	/// (FTP, RFC 959) client.
	///
	/// Most of the features of the FTP protocol, as specified
	/// in RFC 959, are supported. Not supported are EBCDIC and
	/// LOCAL data types and format control and structured files.
	///
	/// Also supported are the EPRT and EPSV commands from
	/// RFC 1738 (FTP Extensions for IPv6 and NAT).
	/// The client will first attempt to use the EPRT and EPSV
	/// commands. If the server does not supports these commands,
	/// the client will fall back to PORT and PASV.
{
public:
	enum
	{
		FTP_PORT = 21
	};
	
	enum FileType
	{
		TYPE_TEXT,   // TYPE A (ASCII)
		TYPE_BINARY  // TYPE I (Image)
	};
	
	FTPClientSession(const StreamSocket& socket);
		/// Creates an FTPClientSession using the given
		/// connected socket for the control connection.
		///
		/// Passive mode will be used for data transfers.
		
	FTPClientSession(const std::string& host, Foundation::UInt16 port = FTP_PORT);
		/// Creates an FTPClientSession using a socket connected
		/// to the given host and port.
		///
		/// Passive mode will be used for data transfers.
		
	virtual ~FTPClientSession();
		/// Destroys the FTPClientSession.
	
	void setTimeout(const Foundation::Timespan& timeout);
		/// Sets the timeout for socket operations.
		
	Foundation::Timespan getTimeout() const;
		/// Returns the timeout for socket operations.

	void setPassive(bool flag);
		/// Enables (default) or disables FTP passive mode for this session.
		
	bool getPassive() const;
		/// Returns true iff passive mode is enabled for this connection.
		
	void login(const std::string& username, const std::string& password);
		/// Authenticates the user against the FTP server. Must be
		/// called before any other commands (except QUIT) can be sent.
		///
		/// Sends a USER command followed by a PASS command with the
		/// respective arguments to the server.
		///
		/// Throws a FTPException in case of a FTP-specific error, or a
		/// NetException in case of a general network communication failure.

	void close();
		/// Sends a QUIT command and closes the connection to the server.	
		///
		/// Throws a FTPException in case of a FTP-specific error, or a
		/// NetException in case of a general network communication failure.
	
	std::string systemType();
		/// Returns the system type of the FTP server.
		///
		/// Sends a SYST command to the server and returns the result.
	
	void setFileType(FileType type);
		/// Sets the file type for transferring files.
		///
		/// Sends a TYPE command with a corresponsing argument to the
		/// server.
		///
		/// Throws a FTPException in case of a FTP-specific error, or a
		/// NetException in case of a general network communication failure.

	FileType getFileType() const;
		/// Returns the file type for transferring files.

	void setWorkingDirectory(const std::string& path);
		/// Changes the current working directory on the server.
		///
		/// Sends a CWD command with the given path as argument to the 
		/// server.
		///
		/// Throws a FTPException in case of a FTP-specific error, or a
		/// NetException in case of a general network communication failure.

	std::string getWorkingDirectory();
		/// Returns the current working directory on the server.
		///
		/// Throws a FTPException in case of a FTP-specific error, or a
		/// NetException in case of a general network communication failure.
		
	void cdup();
		/// Moves one directory up from the current working directory
		/// on teh server.
		///
		/// Sends a CDUP command to the server.
		///
		/// Throws a FTPException in case of a FTP-specific error, or a
		/// NetException in case of a general network communication failure.
		
	void rename(const std::string& oldName, const std::string& newName);
		/// Renames the file on the server given by oldName to newName.
		///
		/// Sends a RNFR command, followed by a RNTO command to the server.
		///
		/// Throws a FTPException in case of a FTP-specific error, or a
		/// NetException in case of a general network communication failure.
		
	void remove(const std::string& path);
		/// Deletes the file specified by path on the server.
		///
		/// Sends a DELE command with path as argument to the server.
		///
		/// Throws a FTPException in case of a FTP-specific error, or a
		/// NetException in case of a general network communication failure.

	void createDirectory(const std::string& path);
		/// Creates a new directory with the given path on the server.
		///
		/// Sends a MKD command with path as argument to the server.
		///
		/// Throws a FTPException in case of a FTP-specific error, or a
		/// NetException in case of a general network communication failure.

	void removeDirectory(const std::string& path);
		/// Removes the directory specified by path from the server.
		///
		/// Sends a RMD command with path as argument to the server.
		///
		/// Throws a FTPException in case of a FTP-specific error, or a
		/// NetException in case of a general network communication failure.

	std::istream& beginDownload(const std::string& path);
		/// Starts downloading the file with the given name.
		/// After all data has been read from the returned stream,
		/// endDownload() must be called to finish the download.
		///
		/// A stream for reading the file's content is returned.
		/// The stream is valid until endDownload() is called.
		///
		/// Creates a data connection between the client and the
		/// server. If passive mode is on, then the server waits for
		/// a connection request from the client. Otherwise, the
		/// client waits for a connection request from the server.
		/// After establishing the data connection, a SocketStream
		/// for transferring the data is created.
		///
		/// If ASCII transfer mode is selected, the caller is
		/// responsible for converting the received data to
		/// the native text file format.
		/// The InputLineEndingConverter class from the Foundation
		/// library can be used for that purpose.
		
	void endDownload();
		/// Must be called to complete a download initiated with
		/// beginDownload().
		
	std::ostream& beginUpload(const std::string& path);
		/// Starts uploading the file with the given name.
		/// After all data has been written to the returned stream,
		/// endUpload() must be called to finish the download.
		///
		/// A stream for reading the file's content is returned.
		/// The stream is valid until endUpload() is called.
		///
		/// Creates a data connection between the client and the
		/// server. If passive mode is on, then the server waits for
		/// a connection request from the client. Otherwise, the
		/// client waits for a connection request from the server.
		/// After establishing the data connection, a SocketStream
		/// for transferring the data is created.
		///
		/// If ASCII transfer mode is selected, the caller is
		/// responsible for converting the data to be sent
		/// into network (CR-LF line endings) format.
		/// The OutputLineEndingConverter class from the Foundation
		/// library can be used for that purpose.

	void endUpload();
		/// Must be called to complete an upload initiated with
		/// beginUpload().

	std::istream& beginList(const std::string& path = "", bool extended = false);
		/// Starts downloading a directory listing.
		/// After all data has been read from the returned stream,
		/// endList() must be called to finish the download.
		///
		/// A stream for reading the directory data is returned.
		/// The stream is valid until endList() is called.
		///
		/// Optionally, a path to a directory or file can be specified.
		/// According to the FTP prototol, if a path to a filename is
		/// given, only information for the specific file is returned.
		/// If a path to a directory is given, a listing of that directory
		/// is returned. If no path is given, a listing of the current
		/// working directory is returned.
		///
		/// If extended is false, only a filenames (one per line) are
		/// returned. Otherwise, a full directory listing including
		/// file attributes is returned. The format of this listing
		/// depends on the FTP server. No attempt is made to interpret
		/// this data.
		///
		/// Creates a data connection between the client and the
		/// server. If passive mode is on, then the server waits for
		/// a connection request from the client. Otherwise, the
		/// client waits for a connection request from the server.
		/// After establishing the data connection, a SocketStream
		/// for transferring the data is created.
		
	void endList();
		/// Must be called to complete a directory listing download 
		/// initiated with beginList().

	void abort();
		/// Aborts the download or upload currently in progress.
		///
		/// Sends a TELNET IP/SYNCH sequence, followed by an ABOR
		/// command to the server.
		///
		/// A separate call to endDownload() or endUpload() is
		/// not necessary.
		
	int sendCommand(const std::string& command, std::string& response);
		/// Sends the given command verbatim to the server
		/// and waits for a response.

	int sendCommand(const std::string& command, const std::string& arg, std::string& response);
		/// Sends the given command verbatim to the server
		/// and waits for a response.

protected:
	enum StatusClass
	{
		FTP_POSITIVE_PRELIMINARY  = 1,
		FTP_POSITIVE_COMPLETION   = 2,
		FTP_POSITIVE_INTERMEDIATE = 3,
		FTP_TRANSIENT_NEGATIVE    = 4,
		FTP_PERMANENT_NEGATIVE    = 5
	};
	enum
	{
		DEFAULT_TIMEOUT = 30000000 // 30 seconds default timeout for socket operations	
	};

	static bool isPositivePreliminary(int status);
	static bool isPositiveCompletion(int status);
	static bool isPositiveIntermediate(int status);
	static bool isTransientNegative(int status);
	static bool isPermanentNegative(int status);
	std::string extractPath(const std::string& response);
	StreamSocket establishDataConnection(const std::string& command, const std::string& arg);
	StreamSocket activeDataConnection(const std::string& command, const std::string& arg);
	StreamSocket passiveDataConnection(const std::string& command, const std::string& arg);
	void sendPortCommand(const SocketAddress& addr);
	SocketAddress sendPassiveCommand();
	bool sendEPRT(const SocketAddress& addr);
	void sendPORT(const SocketAddress& addr);
	bool sendEPSV(SocketAddress& addr);
	void sendPASV(SocketAddress& addr);
	void parseAddress(const std::string& str, SocketAddress& addr);
	void parseExtAddress(const std::string& str, SocketAddress& addr);
	void endTransfer();
	
private:
	FTPClientSession();
	FTPClientSession(const FTPClientSession&);
	FTPClientSession& operator = (const FTPClientSession&);
		
	DialogSocket         _controlSocket;
	SocketStream*        _pDataStream;
	bool                 _passiveMode;
	FileType             _fileType;
	bool                 _supports1738;
	bool                 _isOpen;
	Foundation::Timespan _timeout;
};


//
// inlines
//
inline bool FTPClientSession::isPositivePreliminary(int status)
{
	return status/100 == FTP_POSITIVE_PRELIMINARY;
}


inline bool FTPClientSession::isPositiveCompletion(int status)
{
	return status/100 == FTP_POSITIVE_COMPLETION;
}


inline bool FTPClientSession::isPositiveIntermediate(int status)
{
	return status/100 == FTP_POSITIVE_INTERMEDIATE;
}


inline bool FTPClientSession::isTransientNegative(int status)
{
	return status/100 == FTP_TRANSIENT_NEGATIVE;
}


inline bool FTPClientSession::isPermanentNegative(int status)
{
	return status/100 == FTP_PERMANENT_NEGATIVE;
}


Net_END


#endif // Net_FTPClientSession_INCLUDED
