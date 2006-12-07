//
// LoggingFactory.h
//
// $Id: //poco/1.2/Foundation/include/Poco/LoggingFactory.h#1 $
//
// Library: Foundation
// Package: Logging
// Module:  LoggingFactory
//
// Definition of the LoggingFactory class.
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


#ifndef Foundation_LoggingFactory_INCLUDED
#define Foundation_LoggingFactory_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/DynamicFactory.h"
#include "Poco/Channel.h"
#include "Poco/Formatter.h"


namespace Poco {


class Foundation_API LoggingFactory
	/// An extensible factory for channels and formatters.
	///
	/// The following channel classes are pre-registered:
	///   - AsyncChannel
	///   - ConsoleChannel
	///   - EventLogChannel (Windows platforms only)
	///   - FileChannel
	///   - FormattingChannel
	///   - NullChannel
	///   - OpcomChannel (OpenVMS only)
	///   - SplitterChannel
	///   - SyslogChannel (Unix platforms only)
	///
	/// The following formatter classes are pre-registered:
	///   - PatternFormatter
{
public:
	typedef AbstractInstantiator<Channel>   ChannelInstantiator;
	typedef AbstractInstantiator<Formatter> FormatterFactory;

	LoggingFactory();
		/// Creates the LoggingFactory.
		///
		/// Automatically registers class factories for the
		/// built-in channel and formatter classes.

	~LoggingFactory();
		/// Destroys the LoggingFactory.
		
	void registerChannelClass(const std::string& className, ChannelInstantiator* pFactory);
		/// Registers a channel class with the LoggingFactory.
		
	void registerFormatterClass(const std::string& className, FormatterFactory* pFactory);
		/// Registers a formatter class with the LoggingFactory.

	Channel* createChannel(const std::string& className) const;
		/// Creates a new Channel instance from specified class.
		///
		/// Throws a NotFoundException if the specified channel class 
		/// has not been registered.
		
	Formatter* createFormatter(const std::string& className) const;
		/// Creates a new Formatter instance from specified class.
		///
		/// Throws a NotFoundException if the specified formatter class 
		/// has not been registered.

	static LoggingFactory& defaultFactory();
		/// Returns a reference to the default
		/// LoggingFactory.

private:
	void registerBuiltins();
	
	DynamicFactory<Channel>   _channelFactory;
	DynamicFactory<Formatter> _formatterFactory;
};


} // namespace Poco


#endif // Foundation_LoggingFactory_INCLUDED
