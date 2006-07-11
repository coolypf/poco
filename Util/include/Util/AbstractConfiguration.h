//
// AbstractConfiguration.h
//
// $Id: //poco/1.1.0/Util/include/Util/AbstractConfiguration.h#2 $
//
// Library: Util
// Package: Configuration
// Module:  AbstractConfiguration
//
// Definition of the AbstractConfiguration class.
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


#ifndef Util_AbstractConfiguration_INCLUDED
#define Util_AbstractConfiguration_INCLUDED


#ifndef Util_Util_INCLUDED
#include "Util/Util.h"
#endif
#ifndef Foundation_Mutex_INCLUDED
#include "Foundation/Mutex.h"
#endif
#ifndef Foundation_RefCountedObject_INCLUDED
#include "Foundation/RefCountedObject.h"
#endif
#ifndef STD_VECTOR_INCLUDED
#include <vector>
#define STD_VECTOR_INCLUDED
#endif


Util_BEGIN


class Util_API AbstractConfiguration: public Foundation::RefCountedObject
	/// AbstractConfiguration is an abstract base class for different
	/// kinds of configuration data, such as INI files, property files,
	/// XML configuration files or the Windows Registry.
	///
	/// Configuration property keys have a hierarchical format, consisting
	/// of names separated by periods. The exact interpretation of key names
	/// is up to the actual subclass implementation of AbstractConfiguration.
	/// Keys are case sensitive.
	///
	/// All public methods are synchronized, so the class is safe for multithreaded use.
	/// AbstractConfiguration implements reference counting based garbage collection.
	///
	/// Subclasses must override the getRaw(), setRaw() and enumerate() methods.
{
public:
	typedef std::vector<std::string> Keys;

	AbstractConfiguration();
		/// Creates the AbstractConfiguration.

	bool hasProperty(const std::string& key) const;
		/// Returns true iff the property with the given key exists.

	bool hasOption(const std::string& key) const;
		/// Returns true iff the property with the given key exists.
		/// Same as hasProperty().
		
	std::string getString(const std::string& key) const;
		/// Returns the string value of the property with the given name.
		/// Throws a NotFoundException if the key does not exist.
		/// If the value contains references to other properties (${<property>}), these
		/// are expanded.
		
	std::string getString(const std::string& key, const std::string& defaultValue) const;
		/// If a property with the given key exists, returns the property's string value,
		/// otherwise returns the given default value.
		/// If the value contains references to other properties (${<property>}), these
		/// are expanded.

	std::string getRawString(const std::string& key) const;
		/// Returns the raw string value of the property with the given name.
		/// Throws a NotFoundException if the key does not exist.
		/// References to other properties are not expanded.
		
	std::string getRawString(const std::string& key, const std::string& defaultValue) const;
		/// If a property with the given key exists, returns the property's raw string value,
		/// otherwise returns the given default value.
		/// References to other properties are not expanded.
		
	int getInt(const std::string& key) const;
		/// Returns the int value of the property with the given name.
		/// Throws a NotFoundException if the key does not exist.
		/// Throws a SyntaxException if the property can not be converted
		/// to an int.
		/// Numbers starting with 0x are treated as hexadecimal.
		/// If the value contains references to other properties (${<property>}), these
		/// are expanded.
		
	int getInt(const std::string& key, int defaultValue) const;
		/// If a property with the given key exists, returns the property's int value,
		/// otherwise returns the given default value.
		/// Throws a SyntaxException if the property can not be converted
		/// to an int.
		/// Numbers starting with 0x are treated as hexadecimal.
		/// If the value contains references to other properties (${<property>}), these
		/// are expanded.

	double getDouble(const std::string& key) const;
		/// Returns the double value of the property with the given name.
		/// Throws a NotFoundException if the key does not exist.
		/// Throws a SyntaxException if the property can not be converted
		/// to a double.
		/// If the value contains references to other properties (${<property>}), these
		/// are expanded.
		
	double getDouble(const std::string& key, double defaultValue) const;
		/// If a property with the given key exists, returns the property's double value,
		/// otherwise returns the given default value.
		/// Throws a SyntaxException if the property can not be converted
		/// to an double.
		/// If the value contains references to other properties (${<property>}), these
		/// are expanded.

	bool getBool(const std::string& key) const;
		/// Returns the double value of the property with the given name.
		/// Throws a NotFoundException if the key does not exist.
		/// Throws a SyntaxException if the property can not be converted
		/// to a double.
		/// If the value contains references to other properties (${<property>}), these
		/// are expanded.
		
	bool getBool(const std::string& key, bool defaultValue) const;
		/// If a property with the given key exists, returns the property's bool value,
		/// otherwise returns the given default value.
		/// Throws a SyntaxException if the property can not be converted
		/// to a boolean.
		/// The following string values can be converted into a boolean:
		///   - numerical values: non zero becomes true, zero becomes false
		///   - strings: true, yes, on become true, false, no, off become false
		/// Case does not matter.
		/// If the value contains references to other properties (${<property>}), these
		/// are expanded.
		
	void setString(const std::string& key, const std::string& value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		
	void setInt(const std::string& key, int value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.

	void setDouble(const std::string& key, double value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.

	void setBool(const std::string& key, bool value);
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		
	void keys(Keys& range) const;
		/// Returns in range the names of all keys at root level.

	void keys(const std::string& key, Keys& range) const;
		/// Returns in range the names of all subkeys under the given key.
		/// If an empty key is passed, all root level keys are returned.
	
	const AbstractConfiguration* createView(const std::string& prefix) const;
		/// Creates a non-mutable view (see ConfigurationView) into the configuration.

	AbstractConfiguration* createView(const std::string& prefix);
		/// Creates a view (see ConfigurationView) into the configuration.
	
	std::string expand(const std::string& value) const;
		/// Replaces all occurences of ${<property>} in value with the
		/// value of the <property>. If <property> does not exist,
		/// nothing is changed.
		///
		/// If a circular property reference is detected, a
		/// CircularReferenceException will be thrown.
	
protected:
	virtual bool getRaw(const std::string& key, std::string& value) const = 0;
		/// If the property with the given key exists, stores the property's value
		/// in value and returns true. Otherwise, returns false.
		///
		/// Must be overridden by subclasses.

	virtual void setRaw(const std::string& key, const std::string& value) = 0;
		/// Sets the property with the given key to the given value.
		/// An already existing value for the key is overwritten.
		///
		/// Must be overridden by subclasses.
		
	virtual void enumerate(const std::string& key, Keys& range) const = 0;
		/// Returns in range the names of all subkeys under the given key.
		/// If an empty key is passed, all root level keys are returned.

	static int parseInt(const std::string& value);
	static bool parseBool(const std::string& value);
	
	virtual ~AbstractConfiguration();

private:
	std::string internalExpand(const std::string& value) const;
	std::string uncheckedExpand(const std::string& value) const;

	AbstractConfiguration(const AbstractConfiguration&);
	AbstractConfiguration& operator = (const AbstractConfiguration&);

	mutable int _depth;
	mutable Foundation::FastMutex _mutex;
	
	friend class LayeredConfiguration;
	friend class ConfigurationView;
	friend class ConfigurationMapper;
};


Util_END


#endif // Util_AbstractConfiguration_INCLUDED
