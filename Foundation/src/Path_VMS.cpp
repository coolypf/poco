//
// Path_VMS.cpp
//
// $Id: //poco/1.2/Foundation/src/Path_VMS.cpp#1 $
//
// Library: Foundation
// Package: Filesystem
// Module:  Path
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


#include "Poco/Path_VMS.h"
#include "Poco/Environment_VMS.h"
#include <unistd.h>
#include <descrip.h>
#include <dvsdef.h>
#include <dcdef.h>
#include <iledef.h>
#include <gen64def.h>
#include <starlet.h>


namespace Poco {


std::string PathImpl::currentImpl()
{
	std::string path;
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)))
		path = cwd;
	else
		throw SystemException("cannot get current directory");
	return path;
}


std::string PathImpl::homeImpl()
{
	return EnvironmentImpl::trnlnm("SYS$LOGIN");
}


std::string PathImpl::tempImpl()
{
	std::string result = EnvironmentImpl::trnlnm("SYS$SCRATCH");
	if (result.empty())
		return homeImpl();
	else
		return result; 
}


std::string PathImpl::nullImpl()
{
	return "NLA0:";
}


std::string PathImpl::expandImpl(const std::string& path)
{
	std::string result = path;
	std::string::const_iterator it  = result.begin();
	std::string::const_iterator end = result.end();
	int n = 0;
	while (it != end && n < 10)
	{
		std::string logical;
		while (it != end && *it != ':') logical += *it++;
		if (it != end)
		{
			++it;
			if (it != end && *it == ':') return result;
			std::string val = EnvironmentImpl::trnlnm(logical);
			if (val.empty())
				return result;
			else
				result = val + std::string(it, end);
			it  = result.begin();
			end = result.end();
			++n;
		}
	}
	return result;
}


void PathImpl::listRootsImpl(std::vector<std::string>& roots)
{
	char device[64];
	$DESCRIPTOR(deviceDsc, device);
	int clss = DC$_DISK;
	ILE3 items[2];
	items[0].ile3$w_code         = DVS$_DEVCLASS;
	items[0].ile3$w_length       = sizeof(clss);
	items[0].ile3$ps_bufaddr     = &clss;
	items[0].ile3$ps_retlen_addr = 0;
	items[1].ile3$w_code         = 0;
	items[1].ile3$w_length       = 0;
	int stat;
	GENERIC_64 context;
	context.gen64$q_quadword = 0;
	do 
	{
		unsigned short length;
		stat = sys$device_scan(&deviceDsc, &length, 0, &items, &context);
		if (stat == SS$_NORMAL) 
			roots.push_back(std::string(device, length));
	}
	while (stat == SS$_NORMAL);
}


} // namespace Poco
