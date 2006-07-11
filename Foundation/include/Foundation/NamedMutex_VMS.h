//
// NamedMutex_VMS.h
//
// $Id: //poco/1.1.0/Foundation/include/Foundation/NamedMutex_VMS.h#2 $
//
// Library: Foundation
// Package: Processes
// Module:  NamedMutex
//
// Definition of the NamedMutexImpl class for OpenVMS.
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


#ifndef Foundation_NamedMutex_VMS_INCLUDED
#define Foundation_NamedMutex_VMS_INCLUDED


#ifndef Foundation_Foundation_INCLUDED
#include "Foundation/Foundation.h"
#endif
#ifndef STD_DESCRIP_INCLUDED
#include <descrip.h>
#define STD_DESCRIP_INCLUDED
#endif
#ifndef STD_LCKDEF_INCLUDED
#include <lckdef.h>
#define STD_LCKDEF_INCLUDED
#endif


Foundation_BEGIN


class Foundation_API NamedMutexImpl
{
protected:
	NamedMutexImpl(const std::string& name);
	~NamedMutexImpl();
	void lockImpl();
	bool tryLockImpl();
	void unlockImpl();
	
private:
	std::string             _name;
	struct dsc$descriptor_s _nameDesc;
	int                     _lksb[4];
};


Foundation_END


#endif // Foundation_NamedMutex_VMS_INCLUDED
