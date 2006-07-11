//
// URIStreamOpener.cpp
//
// $Id: //poco/1.1.0/Foundation/src/URIStreamOpener.cpp#2 $
//
// Library: Foundation
// Package: URI
// Module:  URIStreamOpener
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


#include "Foundation/URIStreamOpener.h"
#include "Foundation/URIStreamFactory.h"
#include "Foundation/FileStreamFactory.h"
#include "Foundation/URI.h"
#include "Foundation/Path.h"
#include "Foundation/SingletonHolder.h"
#include "Foundation/Exception.h"


Foundation_BEGIN


URIStreamOpener::URIStreamOpener()
{
	registerStreamFactory("file", new FileStreamFactory);
}


URIStreamOpener::~URIStreamOpener()
{
	for (FactoryMap::iterator it = _map.begin(); it != _map.end(); ++it)
		delete it->second;
}


std::istream* URIStreamOpener::open(const URI& uri) const
{
	FastMutex::ScopedLock lock(_mutex);

	std::string scheme;
	if (uri.isRelative())
		scheme = "file";
	else
		scheme = uri.getScheme();
	FactoryMap::const_iterator it = _map.find(scheme);
	if (it != _map.end())
		return it->second->open(uri);
	else
		throw UnknownURISchemeException(scheme);
}


std::istream* URIStreamOpener::open(const std::string& pathOrURI) const
{
	FastMutex::ScopedLock lock(_mutex);

	try
	{
		URI uri(pathOrURI);
		std::string scheme(uri.getScheme());
		FactoryMap::const_iterator it = _map.find(scheme);
		if (it != _map.end())
			return it->second->open(uri);
	}
	catch (Exception&)
	{
	}
	Path path(pathOrURI, Path::PATH_GUESS);
	return openFile(path);
}


std::istream* URIStreamOpener::open(const std::string& basePathOrURI, const std::string& pathOrURI) const
{
	FastMutex::ScopedLock lock(_mutex);

	try
	{
		URI uri(basePathOrURI);
		std::string scheme(uri.getScheme());
		FactoryMap::const_iterator it = _map.find(scheme);
		if (it != _map.end())
		{
			uri.resolve(pathOrURI);
			return it->second->open(uri);
		}
	}
	catch (Exception&)
	{
	}
	Path base(basePathOrURI, Path::PATH_GUESS);
	Path path(pathOrURI, Path::PATH_GUESS);
	base.resolve(path);
	return openFile(base);
}

	
void URIStreamOpener::registerStreamFactory(const std::string& scheme, URIStreamFactory* pFactory)
{
	poco_check_ptr (pFactory);

	FastMutex::ScopedLock lock(_mutex);
	if (_map.find(scheme) == _map.end())
	{
		_map[scheme] = pFactory;
	}
	else throw ExistsException("An URIStreamFactory for the given scheme has already been registered", scheme);
}


void URIStreamOpener::unregisterStreamFactory(const std::string& scheme)
{
	FastMutex::ScopedLock lock(_mutex);
	
	FactoryMap::iterator it = _map.find(scheme);
	if (it != _map.end())
	{
		URIStreamFactory* pFactory = it->second;
		_map.erase(it);
		delete pFactory;
	}
	else throw NotFoundException("No URIStreamFactory has been registered for the given scheme", scheme);
}


bool URIStreamOpener::supportsScheme(const std::string& scheme)
{
	FastMutex::ScopedLock lock(_mutex);
	return _map.find(scheme) != _map.end();
}


URIStreamOpener& URIStreamOpener::defaultOpener()
{
	static SingletonHolder<URIStreamOpener> sh;
	return *sh.get();
}


std::istream* URIStreamOpener::openFile(const Path& path) const
{
	FileStreamFactory factory;
	return factory.open(path);
}



Foundation_END
