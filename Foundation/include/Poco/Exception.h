//
// Exception.h
//
// $Id: //poco/1.2/Foundation/include/Poco/Exception.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  Exception
//
// Definition of various Poco exception classes.
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


#ifndef Foundation_Exception_INCLUDED
#define Foundation_Exception_INCLUDED


#include "Poco/Foundation.h"
#include <stdexcept>


namespace Poco {


class Foundation_API Exception: public std::exception
	/// This is the base class for all exceptions defined
	/// in the Poco class library.
{
public:
	Exception(const std::string& msg);
		/// Creates an exception.

	Exception(const std::string& msg, const std::string& arg);
		/// Creates an exception.

	Exception(const std::string& msg, const Exception& nested);
		/// Creates an exception and stores a clone
		/// of the nested exception.

	Exception(const Exception& exc);
		/// Copy constructor.
		
	~Exception() throw();
		/// Destroys the exception and deletes the nested exception.

	Exception& operator = (const Exception& exc);
		/// Assignment operator.

	virtual const char* name() const throw();
		/// Returns a static string describing the exception.
		
	virtual const char* className() const throw();
		/// Returns the name of the exception class.
		
	virtual const char* what() const throw();
		/// Returns the message text as a C string.
		
	const Exception* nested() const;
		/// Returns a pointer to the nested exception, or
		/// null if no nested exception exists.
			
	const std::string& message() const;
		/// Returns the message text.
		
	std::string displayText() const;
		/// Returns a string consisting of the
		/// message name and the message text.

	virtual Exception* clone() const;
		/// Creates an exact copy of the exception.
		///
		/// The copy can later be thrown again by
		/// invoking rethrow() on it.
		
	virtual void rethrow() const;
		/// (Re)Throws the exception.
		///
		/// This is useful for temporarily storing a
		/// copy of an exception (see clone()), then
		/// throwing it again.

protected:
	Exception();
		/// Standard constructor.
		
private:
	std::string _msg;
	Exception*  _pNested;
};


//
// inlines
//
inline const Exception* Exception::nested() const
{
	return _pNested;
}


inline const std::string& Exception::message() const
{
	return _msg;
}


//
// Macros for quickly declaring and implementing exception classes.
// Unfortunately, we cannot use a template here because character
// pointers (which we need for specifying the exception name)
// are not allowed as template arguments.
//
#define POCO_DECLARE_EXCEPTION(API, CLS, BASE) \
	class API CLS: public BASE							\
	{																	\
	public:																\
		CLS();															\
		CLS(const std::string& msg);									\
		CLS(const std::string& msg, const std::string& arg);			\
		CLS(const std::string& msg, const Poco::Exception& exc);	\
		CLS(const CLS& exc);											\
		~CLS() throw();													\
		CLS& operator = (const CLS& exc);								\
		const char* name() const throw();								\
		const char* className() const throw();							\
		Poco::Exception* clone() const;							\
		void rethrow() const;											\
	};


#define POCO_IMPLEMENT_EXCEPTION(CLS, BASE, NAME) \
	CLS::CLS()																			\
	{																					\
	}																					\
	CLS::CLS(const std::string& msg): BASE(msg)											\
	{																					\
	}																					\
	CLS::CLS(const std::string& msg, const std::string& arg): BASE(msg, arg)			\
	{																					\
	}																					\
	CLS::CLS(const std::string& msg, const Poco::Exception& exc): BASE(msg, exc)	\
	{																					\
	}																					\
	CLS::CLS(const CLS& exc): BASE(exc)													\
	{																					\
	}																					\
	CLS::~CLS() throw()																	\
	{																					\
	}																					\
	CLS& CLS::operator = (const CLS& exc)												\
	{																					\
		BASE::operator = (exc);															\
		return *this;																	\
	}																					\
	const char* CLS::name() const throw()												\
	{																					\
		return NAME;																	\
	}																					\
	const char* CLS::className() const throw()											\
	{																					\
		return typeid(*this).name();													\
	}																					\
	Poco::Exception* CLS::clone() const											\
	{																					\
		return new CLS(*this);															\
	}																					\
	void CLS::rethrow() const															\
	{																					\
		throw *this;																	\
	}


//
// Standard exception classes
//
POCO_DECLARE_EXCEPTION(Foundation_API, LogicException, Exception)
POCO_DECLARE_EXCEPTION(Foundation_API, AssertionViolationException, LogicException)
POCO_DECLARE_EXCEPTION(Foundation_API, NullPointerException, LogicException)
POCO_DECLARE_EXCEPTION(Foundation_API, BugcheckException, LogicException)
POCO_DECLARE_EXCEPTION(Foundation_API, InvalidArgumentException, LogicException)
POCO_DECLARE_EXCEPTION(Foundation_API, NotImplementedException, LogicException)
POCO_DECLARE_EXCEPTION(Foundation_API, RangeException, LogicException)
POCO_DECLARE_EXCEPTION(Foundation_API, IllegalStateException, LogicException)
POCO_DECLARE_EXCEPTION(Foundation_API, InvalidAccessException, LogicException)
POCO_DECLARE_EXCEPTION(Foundation_API, SignalException, LogicException)
POCO_DECLARE_EXCEPTION(Foundation_API, UnhandledException, LogicException)

POCO_DECLARE_EXCEPTION(Foundation_API, RuntimeException, Exception)
POCO_DECLARE_EXCEPTION(Foundation_API, NotFoundException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, ExistsException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, TimeoutException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, SystemException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, RegularExpressionException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, LibraryLoadException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, LibraryAlreadyLoadedException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, NoThreadAvailableException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, PropertyNotSupportedException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, PoolOverflowException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, NoPermissionException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, OutOfMemoryException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, DataException, RuntimeException)

POCO_DECLARE_EXCEPTION(Foundation_API, DataFormatException, DataException)
POCO_DECLARE_EXCEPTION(Foundation_API, SyntaxException, DataException)
POCO_DECLARE_EXCEPTION(Foundation_API, CircularReferenceException, DataException)
POCO_DECLARE_EXCEPTION(Foundation_API, PathSyntaxException, SyntaxException)
POCO_DECLARE_EXCEPTION(Foundation_API, IOException, RuntimeException)
POCO_DECLARE_EXCEPTION(Foundation_API, FileException, IOException)
POCO_DECLARE_EXCEPTION(Foundation_API, FileExistsException, FileException)
POCO_DECLARE_EXCEPTION(Foundation_API, FileNotFoundException, FileException)
POCO_DECLARE_EXCEPTION(Foundation_API, PathNotFoundException, FileException)
POCO_DECLARE_EXCEPTION(Foundation_API, FileReadOnlyException, FileException)
POCO_DECLARE_EXCEPTION(Foundation_API, FileAccessDeniedException, FileException)
POCO_DECLARE_EXCEPTION(Foundation_API, CreateFileException, FileException)
POCO_DECLARE_EXCEPTION(Foundation_API, OpenFileException, FileException)
POCO_DECLARE_EXCEPTION(Foundation_API, WriteFileException, FileException)
POCO_DECLARE_EXCEPTION(Foundation_API, ReadFileException, FileException)
POCO_DECLARE_EXCEPTION(Foundation_API, UnknownURISchemeException, RuntimeException)

POCO_DECLARE_EXCEPTION(Foundation_API, ApplicationException, Exception)
POCO_DECLARE_EXCEPTION(Foundation_API, BadCastException, RuntimeException)


} // namespace Poco


#endif // Foundation_Exception_INCLUDED
