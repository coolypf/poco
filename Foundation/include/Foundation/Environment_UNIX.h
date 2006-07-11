//
// Environment_UNIX.h
//
// $Id: //poco/1.1.0/Foundation/include/Foundation/Environment_UNIX.h#2 $
//
// Library: Foundation
// Package: Core
// Module:  Environment
//
// Definition of the EnvironmentImpl class for Unix.
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


#ifndef Foundation_Environment_UNIX_INCLUDED
#define Foundation_Environment_UNIX_INCLUDED


#ifndef Foundation_Foundation_INCLUDED
#include "Foundation/Foundation.h"
#endif
#ifndef Foundation_Mutex_INCLUDED
#include "Foundation/Mutex.h"
#endif
#ifndef STD_MAP_INCLUDED
#include <map>
#define STD_MAP_INCLUDED
#endif


Foundation_BEGIN


class Foundation_API EnvironmentImpl
{
public:
	static std::string getImpl(const std::string& name);	
	static bool hasImpl(const std::string& name);	
	static void setImpl(const std::string& name, const std::string& value);
	static std::string osNameImpl();
	static std::string osVersionImpl();
	static std::string osArchitectureImpl();
	static std::string nodeNameImpl();

private:
	typedef std::map<std::string, std::string> StringMap;
	
	static StringMap _map;
	static FastMutex _mutex;
};


Foundation_END


#endif // Foundation_Environment_UNIX_INCLUDED
