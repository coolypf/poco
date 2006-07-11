//
// WinRegistryKey.h
//
// $Id: //poco/1.1.0/Util/include/Util/WinRegistryKey.h#2 $
//
// Library: Util
// Package: Windows
// Module:  WinRegistryKey
//
// Definition of the WinRegistryKey class.
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


#ifndef Util_WinRegistryKey_INCLUDED
#define Util_WinRegistryKey_INCLUDED


#ifndef Util_Util_INCLUDED
#include "Util/Util.h"
#endif
#ifndef STD_WINDOWS_INCLUDED
#include <windows.h>
#define STD_WINDOWS_INCLUDED
#endif


Util_BEGIN


class Util_API WinRegistryKey
	/// This class implements a convenient interface to the
	/// Windows Registry.
	///
	/// This class is only available on Windows platforms.
{
public:
	WinRegistryKey(const std::string& key);
		/// Creates the WinRegistryKey.
		///
		/// The key must start with one of the root key names
		/// like HKEY_CLASSES_ROOT, e.g. HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services.

	WinRegistryKey(HKEY hRootKey, const std::string& subKey);
		/// Creates the WinRegistryKey.

	~WinRegistryKey();
		/// Destroys the WinRegistryKey.

	void setString(const std::string& name, const std::string& value);
		/// Sets the string value (REG_SZ) with the given name.
		/// An empty name denotes the default value.
		
	std::string getString(const std::string& name);
		/// Returns the string value (REG_SZ) with the given name.
		/// An empty name denotes the default value.
		///
		/// Throws a NotFoundException if the value does not exist.

	void setStringExpand(const std::string& name, const std::string& value);
		/// Sets the expandable string value (REG_EXPAND_SZ) with the given name.
		/// An empty name denotes the default value.
		
	std::string getStringExpand(const std::string& name);
		/// Returns the string value (REG_EXPAND_SZ) with the given name.
		/// An empty name denotes the default value.
		/// All references to environment variables (%VAR%) in the string
		/// are expanded.
		///
		/// Throws a NotFoundException if the value does not exist.

	void setInt(const std::string& name, int value);
		/// Sets the numeric (REG_DWORD) value with the given name.
		/// An empty name denotes the default value.
		
	int getInt(const std::string& name);
		/// Returns the numeric value (REG_DWORD) with the given name.
		/// An empty name denotes the default value.
		///
		/// Throws a NotFoundException if the value does not exist.

	void deleteValue(const std::string& name);
		/// Deletes the value with the given name.
		///
		/// Throws a NotFoundException if the value does not exist.

	void deleteKey();
		/// Deletes the key. The key must not have subkeys.

	bool exists();
		/// Returns true iff the key exists.
		
	bool exists(const std::string& name);
		/// Returns true iff the given value exists under that key.

protected:
	void open();
	void close();
	std::string key() const;
	std::string key(const std::string& valueName) const;
	void handleSetError(const std::string& name);
	static HKEY handleFor(const std::string& rootKey);

private:
	WinRegistryKey();
	WinRegistryKey(const WinRegistryKey&);
	WinRegistryKey& operator = (const WinRegistryKey&);
	
	HKEY        _hRootKey;
	std::string _subKey;
	HKEY        _hKey;
};


Util_END


#endif // Util_WinRegistryKey_INCLUDED
