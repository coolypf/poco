//
// LogFile_VMS.cpp
//
// $Id: //poco/1.1.0/Foundation/src/LogFile_VMS.cpp#2 $
//
// Library: Foundation
// Package: Logging
// Module:  LogFile
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


#include "Foundation/LogFile_VMS.h"
#include "Foundation/File.h"
#include "Foundation/Exception.h"


Foundation_BEGIN


LogFileImpl::LogFileImpl(const std::string& path): _path(path)
{
	_file = fopen(path.c_str(), "a", "ctx=rec,bin", "shr=get", "fop=dfw", "alq=500", "deq=500");
	if (!_file) throw OpenFileException(path);
	if (size() == 0)
		_creationDate = File(path).getLastModified();
	else
		_creationDate = File(path).created();
}


LogFileImpl::~LogFileImpl()
{
	fclose(_file);
}


void LogFileImpl::writeImpl(const std::string& text)
{
	int rc = fputs(text.c_str(), _file);
	if (rc == EOF) throw WriteFileException(_path);
	rc = fputc('\n', _file);
	if (rc == EOF) throw WriteFileException(_path);
	rc = fflush(_file);
	if (rc == EOF) throw WriteFileException(_path);
}


UInt64 LogFileImpl::sizeImpl() const
{
	return (UInt64) ftell(_file);
}


Timestamp LogFileImpl::creationDateImpl() const
{
	return _creationDate;
}


const std::string& LogFileImpl::pathImpl() const
{
	return _path;
}


Foundation_END
