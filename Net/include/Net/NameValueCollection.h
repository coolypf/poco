//
// NameValueCollection.h
//
// $Id: //poco/1.1.0/Net/include/Net/NameValueCollection.h#2 $
//
// Library: Net
// Package: Messages
// Module:  NameValueCollection
//
// Definition of the NameValueCollection class.
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


#ifndef Net_NameValueCollection_INCLUDED
#define Net_NameValueCollection_INCLUDED


#ifndef Net_Net_INCLUDED
#include "Net/Net.h"
#endif
#ifndef Foundation_String_INCLUDED
#include "Foundation/String.h"
#endif
#ifndef STD_MAP_INCLUDED
#include <map>
#define STD_MAP_INCLUDED
#endif


Net_BEGIN


class Net_API NameValueCollection
	/// A collection of name-value pairs that are used in
	/// various internet protocols like HTTP and SMTP.
	///
	/// The name is case-insensitive.
	///
	/// There can be more than one name-value pair with the 
	/// same name.
{
public:
	struct ILT
	{
		bool operator() (const std::string& s1, const std::string& s2) const
		{
			return Foundation::icompare(s1, s2) < 0;
		}
	};
	
	typedef std::multimap<std::string, std::string, ILT> HeaderMap;
	typedef HeaderMap::iterator Iterator;
	typedef HeaderMap::const_iterator ConstIterator;
	
	NameValueCollection();
		/// Creates an empty NameValueCollection.

	NameValueCollection(const NameValueCollection& nvc);
		/// Creates a NameValueCollection by copying another one.

	virtual ~NameValueCollection();
		/// Destroys the NameValueCollection.

	NameValueCollection& operator = (const NameValueCollection& nvc);
		/// Assigns the name-value pairs of another NameValueCollection to this one.
		
	void swap(NameValueCollection& nvc);
		/// Swaps the NameValueCollection with another one.
		
	const std::string& operator [] (const std::string& name) const;
		/// Returns the value of the (first) name-value pair with the given name.
		///
		/// Throws a NotFoundException if the name-value pair does not exist.
		
	void set(const std::string& name, const std::string& value);	
		/// Sets the value of the (first) name-value pair with the given name.
		
	void add(const std::string& name, const std::string& value);
		/// Adds a new name-value pair with the given name and value.
		
	const std::string& get(const std::string& name) const;
		/// Returns the value of the first name-value pair with the given name.
		///
		/// Throws a NotFoundException if the name-value pair does not exist.

	bool has(const std::string& name) const;
		/// Returns true if there is at least one name-value pair
		/// with the given name.

	ConstIterator find(const std::string& name) const;
		/// Returns an iterator pointing to the first name-value pair
		/// with the given name.
		
	ConstIterator begin() const;
		/// Returns an iterator pointing to the begin of
		/// the name-value pair collection.
		
	ConstIterator end() const;
		/// Returns an iterator pointing to the end of 
		/// the name-value pair collection.
		
	bool empty() const;
		/// Returns true iff the header does not have any content.

	int size() const;
		/// Returns the number of name-value pairs in the
		/// collection.

	void erase(const std::string& name);
		/// Removes all name-value pairs with the given name.

	void clear();
		/// Removes all name-value pairs and their values.

private:
	HeaderMap _map;
};


//
// inlines
//
inline void swap(NameValueCollection& nvc1, NameValueCollection& nvc2)
{
	nvc1.swap(nvc2);
}


Net_END


#endif // Net_NameValueCollection_INCLUDED
