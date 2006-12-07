//
// File_WIN32.cpp
//
// $Id: //poco/1.2/Foundation/src/File_WIN32.cpp#2 $
//
// Library: Foundation
// Package: Filesystem
// Module:  File
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


#include "Poco/File_WIN32.h"
#include "Poco/Exception.h"
#include <windows.h>


namespace Poco {


class FileHandle
{
public:
	FileHandle(const std::string& path, DWORD access, DWORD share, DWORD disp)
	{
		_h = CreateFile(path.c_str(), access, share, 0, disp, 0, 0);
		if (!_h) FileImpl::handleError(path);
	}
	
	~FileHandle()
	{
		if (_h) CloseHandle(_h);
	}
	
	HANDLE get() const
	{
		return _h;
	}
	
private:
	HANDLE _h;
};


FileImpl::FileImpl()
{
}


FileImpl::FileImpl(const std::string& path): _path(path)
{
	std::string::size_type n = _path.size();
	if (n > 1 && (_path[n - 1] == '\\' || _path[n - 1] == '/') && !((n == 3 && _path[1]==':')))
	{
		_path.resize(n - 1);
	}
}


FileImpl::~FileImpl()
{
}


void FileImpl::swapImpl(FileImpl& file)
{
	std::swap(_path, file._path);
}


void FileImpl::setPathImpl(const std::string& path)
{
	_path = path;
	std::string::size_type n = _path.size();
	if (n > 1 && (_path[n - 1] == '\\' || _path[n - 1] == '/') && !((n == 3 && _path[1]==':')))
	{
		_path.resize(n - 1);
	}
}


bool FileImpl::existsImpl() const
{
	poco_assert (!_path.empty());

	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == 0xFFFFFFFF)
	{
		switch (GetLastError())
		{
		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
		case ERROR_NOT_READY:
		case ERROR_INVALID_DRIVE:
			return false;
		default:
			handleError(_path);
		}
	}
	return true;
}


bool FileImpl::canReadImpl() const
{
	poco_assert (!_path.empty());
	
	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == 0xFFFFFFFF)
	{
		switch (GetLastError())
		{
		case ERROR_ACCESS_DENIED:
			return false;
		default:
			handleError(_path);
		}
	}
	return true;
}


bool FileImpl::canWriteImpl() const
{
	poco_assert (!_path.empty());
	
	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == 0xFFFFFFFF)
		handleError(_path);
	return (attr & FILE_ATTRIBUTE_READONLY) == 0;
}


bool FileImpl::isFileImpl() const
{
	poco_assert (!_path.empty());

	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == 0xFFFFFFFF)
		handleError(_path);
	return (attr & FILE_ATTRIBUTE_DIRECTORY) == 0;
}


bool FileImpl::isDirectoryImpl() const
{
	poco_assert (!_path.empty());

	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == 0xFFFFFFFF)
		handleError(_path);
	return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}


bool FileImpl::isLinkImpl() const
{
	return false;
}


Timestamp FileImpl::createdImpl() const
{
	poco_assert (!_path.empty());

	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
		handleError(_path);
	return Timestamp::fromFileTimeNP(fad.ftCreationTime.dwLowDateTime, fad.ftCreationTime.dwHighDateTime);
}


Timestamp FileImpl::getLastModifiedImpl() const
{
	poco_assert (!_path.empty());

	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
		handleError(_path);
	return Timestamp::fromFileTimeNP(fad.ftLastWriteTime.dwLowDateTime, fad.ftLastWriteTime.dwHighDateTime);
}


void FileImpl::setLastModifiedImpl(const Timestamp& ts)
{
	poco_assert (!_path.empty());

	UInt32 low;
	UInt32 high;
	ts.toFileTimeNP(low, high);
	FILETIME ft;
	ft.dwLowDateTime  = low;
	ft.dwHighDateTime = high;
	FileHandle fh(_path, FILE_ALL_ACCESS, FILE_SHARE_WRITE, OPEN_EXISTING);
	if (SetFileTime(fh.get(), 0, &ft, &ft) == 0)
		handleError(_path);
}


FileImpl::FileSizeImpl FileImpl::getSizeImpl() const
{
	poco_assert (!_path.empty());

	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
		handleError(_path);
	LARGE_INTEGER li;
	li.LowPart  = fad.nFileSizeLow;
	li.HighPart = fad.nFileSizeHigh;
	return li.QuadPart;
}


void FileImpl::setSizeImpl(FileSizeImpl size)
{
	poco_assert (!_path.empty());

	FileHandle fh(_path, GENERIC_WRITE, FILE_SHARE_WRITE, OPEN_EXISTING);
	LARGE_INTEGER li;
	li.QuadPart = size;
	if (SetFilePointer(fh.get(), li.LowPart, &li.HighPart, FILE_BEGIN) == -1)
		handleError(_path);
	if (SetEndOfFile(fh.get()) == 0) 
		handleError(_path);
}


void FileImpl::setWriteableImpl(bool flag)
{
	poco_assert (!_path.empty());

	DWORD attr = GetFileAttributes(_path.c_str());
	if (attr == -1)
		handleError(_path);
	if (flag)
		attr &= ~FILE_ATTRIBUTE_READONLY;
	else
		attr |= FILE_ATTRIBUTE_READONLY;
	if (SetFileAttributes(_path.c_str(), attr) == 0)
		handleError(_path);
}


void FileImpl::copyToImpl(const std::string& path) const
{
	poco_assert (!_path.empty());

	if (CopyFile(_path.c_str(), path.c_str(), FALSE) == 0) 
		handleError(_path);
}


void FileImpl::renameToImpl(const std::string& path)
{
	poco_assert (!_path.empty());

	if (MoveFile(_path.c_str(), path.c_str()) == 0) 
		handleError(_path);
}


void FileImpl::removeImpl()
{
	poco_assert (!_path.empty());

	if (isDirectoryImpl())
	{
		if (RemoveDirectory(_path.c_str()) == 0) 
			handleError(_path);
	}
	else
	{
		if (DeleteFile(_path.c_str()) == 0)
			handleError(_path);
	}
}


bool FileImpl::createFileImpl()
{
	poco_assert (!_path.empty());

	HANDLE hFile = CreateFile(_path.c_str(), GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
	if (hFile)
	{
		CloseHandle(hFile);
		return true;
	}
	else if (GetLastError() == ERROR_ALREADY_EXISTS)
		return false;
	else
		handleError(_path);
	return false;
}


bool FileImpl::createDirectoryImpl()
{
	poco_assert (!_path.empty());
	
	if (existsImpl() && isDirectoryImpl())
		return false;
	if (CreateDirectory(_path.c_str(), 0) == 0)
		handleError(_path);
	return true;
}


void FileImpl::handleError(const std::string& path)
{
	switch (GetLastError())
	{
	case ERROR_FILE_NOT_FOUND:
		throw FileNotFoundException(path);
	case ERROR_PATH_NOT_FOUND:
	case ERROR_BAD_NETPATH:
	case ERROR_CANT_RESOLVE_FILENAME:
	case ERROR_INVALID_DRIVE:
		throw PathNotFoundException(path);
	case ERROR_ACCESS_DENIED:
		throw FileAccessDeniedException(path);
	case ERROR_ALREADY_EXISTS:
	case ERROR_FILE_EXISTS:
		throw FileExistsException(path);
	case ERROR_INVALID_NAME:
	case ERROR_DIRECTORY:
	case ERROR_FILENAME_EXCED_RANGE:
	case ERROR_BAD_PATHNAME:
		throw PathSyntaxException(path);
	case ERROR_FILE_READ_ONLY:
		throw FileReadOnlyException(path);
	case ERROR_CANNOT_MAKE:
		throw CreateFileException(path);
	case ERROR_DIR_NOT_EMPTY:
		throw FileException("directory not empty", path);
	default:
		throw FileException(path);
	}
}


} // namespace Poco
