//
// Platform.h
//
// $Id: //poco/1.2/Foundation/include/Poco/Platform.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  Platform
//
// Platform and architecture identification macros.
//
// NOTE: This file may be included from both C++ and C code, so it
//       must not contain any C++ specific things.
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


#ifndef Foundation_Platform_INCLUDED
#define Foundation_Platform_INCLUDED


//
// Platform Identification
//
#define POCO_OS_FREE_BSD      0x0001
#define POCO_OS_AIX           0x0002
#define POCO_OS_HPUX          0x0003
#define POCO_OS_TRU64         0x0004
#define POCO_OS_LINUX         0x0005
#define POCO_OS_MAC_OS_X      0x0006
#define POCO_OS_NET_BSD       0x0007
#define POCO_OS_OPEN_BSD      0x0008
#define POCO_OS_IRIX          0x0009
#define POCO_OS_SOLARIS       0x000a
#define POCO_OS_QNX           0x000b
#define POCO_OS_VXWORKS       0x000c
#define POCO_OS_CYGWIN        0x000d
#define POCO_OS_UNKNOWN_UNIX  0x00ff
#define POCO_OS_WINDOWS_NT    0x1001
#define POCO_OS_WINDOWS_CE    0x1011
#define POCO_OS_VMS           0x2001


#if defined(__FreeBSD__)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS_FAMILY_BSD 1
	#define POCO_OS POCO_OS_FREE_BSD
#elif defined(_AIX) || defined(__TOS_AIX__)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS POCO_OS_AIX
#elif defined(hpux) || defined(_hpux)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS POCO_OS_HPUX
#elif defined(__digital__) || defined(__osf__)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS POCO_OS_TRU64
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS POCO_OS_LINUX
#elif defined(__APPLE__) || defined(__TOS_MACOS__)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS_FAMILY_BSD 1
	#define POCO_OS POCO_OS_MAC_OS_X
#elif defined(__NetBSD__)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS_FAMILY_BSD 1
	#define POCO_OS POCO_OS_NET_BSD
#elif defined(__OpenBSD__)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS_FAMILY_BSD 1
	#define POCO_OS POCO_OS_OPEN_BSD
#elif defined(sgi) || defined(__sgi)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS POCO_OS_IRIX
#elif defined(sun) || defined(__sun)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS POCO_OS_SOLARIS
#elif defined(__QNX__)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS POCO_OS_QNX
#elif defined(unix) || defined(__unix) || defined(__unix__)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS POCO_OS_UNKNOWN_UNIX
#elif defined(_WIN32_WCE)
	#define POCO_OS_FAMILY_WINDOWS 1
	#define POCO_OS POCO_OS_WINDOWS_CE
#elif defined(_WIN32) || defined(_WIN64)
	#define POCO_OS_FAMILY_WINDOWS 1
	#define POCO_OS POCO_OS_WINDOWS_NT
#elif defined(__CYGWIN__)
	#define POCO_OS_FAMILY_UNIX 1
	#define POCO_OS POCO_OS_CYGWIN
#elif defined(__VMS)
	#define POCO_OS_FAMILY_VMS 1
	#define POCO_OS POCO_OS_VMS
#endif


//
// Hardware Architecture and Byte Order
//
#define POCO_ARCH_ALPHA   0x01
#define POCO_ARCH_IA32    0x02
#define POCO_ARCH_IA64    0x03
#define POCO_ARCH_MIPS    0x04
#define POCO_ARCH_HPPA    0x05
#define POCO_ARCH_PPC     0x06
#define POCO_ARCH_POWER   0x07
#define POCO_ARCH_SPARC   0x08
#define POCO_ARCH_AMD64   0x09
#define POCO_ARCH_ARM     0x0a


#if defined(__ALPHA) || defined(__alpha) || defined(__alpha__) || defined(_M_ALPHA)
	#define POCO_ARCH POCO_ARCH_ALPHA
	#define POCO_ARCH_LITTLE_ENDIAN 1
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86)
	#define POCO_ARCH POCO_ARCH_IA32
	#define POCO_ARCH_LITTLE_ENDIAN 1
#elif defined(_IA64) || defined(__IA64__) || defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
	#define POCO_ARCH POCO_ARCH_IA64
	#if defined(hpux) || defined(_hpux)
		#define POCO_ARCH_BIG_ENDIAN 1
	#else
		#define POCO_ARCH_LITTLE_ENDIAN 1
	#endif
#elif defined(__x86_64__)
	#define POCO_ARCH POCO_ARCH_AMD64
	#define POCO_ARCH_LITTLE_ENDIAN 1
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__) || defined(_M_MRX000)
	#define POCO_ARCH POCO_ARCH_MIPS
	#define POCO_ARCH_BIG_ENDIAN 1
#elif defined(__hppa) || defined(__hppa__)
	#define POCO_ARCH POCO_ARCH_HPPA
	#define POCO_ARCH_BIG_ENDIAN 1
#elif defined(__PPC) || defined(__POWERPC__) || defined(__powerpc) || defined(__PPC__) || \
      defined(__powerpc__) || defined(__ppc__) || defined(_ARCH_PPC) || defined(_M_PPC)
	#define POCO_ARCH POCO_ARCH_PPC
	#define POCO_ARCH_BIG_ENDIAN 1
#elif defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || \
      defined(_ARCH_PWR4) || defined(__THW_RS6000)
	#define POCO_ARCH POCO_ARCH_POWER
	#define POCO_ARCH_BIG_ENDIAN 1
#elif defined(__sparc__) || defined(__sparc) || defined(sparc)
	#define POCO_ARCH POCO_ARCH_SPARC
	#define POCO_ARCH_BIG_ENDIAN 1
#elif defined(__arm__) || defined(__arm) || defined(ARM) || defined(_ARM_) || defined(__ARM__) || defined(_M_ARM)
	#define POCO_ARCH POCO_ARCH_ARM
	#if defined(__ARMEB__)
		#define POCO_ARCH_BIG_ENDIAN 1
	#else
		#define POCO_ARCH_LITTLE_ENDIAN 1
	#endif
#endif


#endif // Foundation_Platform_INCLUDED
