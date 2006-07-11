//
// StreamTokenizerTest.cpp
//
// $Id: //poco/1.1.0/Foundation/testsuite/src/StreamTokenizerTest.cpp#2 $
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


#include "StreamTokenizerTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Foundation/StreamTokenizer.h"
#include "Foundation/Token.h"
#include <ctype.h>
#include <sstream>


using Foundation::StreamTokenizer;
using Foundation::Token;
using Foundation::InvalidToken;
using Foundation::EOFToken;
using Foundation::WhitespaceToken;


class IdentifierToken: public Token
{
public:
	IdentifierToken()
	{
	}
	
	~IdentifierToken()
	{
	}

	Class tokenClass() const
	{
		return Token::IDENTIFIER_TOKEN;
	}
	
	bool start(char c, std::istream& istr)
	{
		if (isalpha(c))
		{
			_value = c;
			return true;
		}
		else return false;
	}
	
	void finish(std::istream& istr)
	{
		int c = istr.peek();
		while (isalnum(c))
		{
			istr.get();
			_value += c;
			c = istr.peek();
		}
	}
};


class IntLiteralToken: public Token
{
public:
	IntLiteralToken()
	{
	}
	
	~IntLiteralToken()
	{
	}

	Class tokenClass() const
	{
		return Token::INTEGER_LITERAL_TOKEN;
	}
	
	bool start(char c, std::istream& istr)
	{
		if (isdigit(c))
		{
			_value = c;
			return true;
		}
		else return false;
	}
	
	void finish(std::istream& istr)
	{
		int c = istr.peek();
		while (isdigit(c))
		{
			istr.get();
			_value += c;
			c = istr.peek();
		}
	}
};


StreamTokenizerTest::StreamTokenizerTest(const std::string& name): CppUnit::TestCase(name)
{
}


StreamTokenizerTest::~StreamTokenizerTest()
{
}


void StreamTokenizerTest::testTokenizer1()
{
	std::string data = "";
	std::istringstream istr(data);
	StreamTokenizer tokenizer(istr);
	tokenizer.addToken(new WhitespaceToken());
	tokenizer.addToken(new IdentifierToken());
	tokenizer.addToken(new IntLiteralToken());
	
	const Token* next = tokenizer.next();
	assert (next->tokenClass() == Token::EOF_TOKEN);
}


void StreamTokenizerTest::testTokenizer2()
{
	std::string data = "foo";
	std::istringstream istr(data);
	StreamTokenizer tokenizer(istr);
	tokenizer.addToken(new WhitespaceToken());
	tokenizer.addToken(new IdentifierToken());
	tokenizer.addToken(new IntLiteralToken());
	
	const Token* next = tokenizer.next();
	assert (next->tokenClass() == Token::IDENTIFIER_TOKEN);
	assert (next->tokenString() == "foo");
	
	next = tokenizer.next();
	assert (next->tokenClass() == Token::EOF_TOKEN);
}


void StreamTokenizerTest::testTokenizer3()
{
	std::string data = "foo bar";
	std::istringstream istr(data);
	StreamTokenizer tokenizer(istr);
	tokenizer.addToken(new WhitespaceToken());
	tokenizer.addToken(new IdentifierToken());
	tokenizer.addToken(new IntLiteralToken());
	
	const Token* next = tokenizer.next();
	assert (next->tokenClass() == Token::IDENTIFIER_TOKEN);
	assert (next->tokenString() == "foo");

	next = tokenizer.next();
	assert (next->tokenClass() == Token::IDENTIFIER_TOKEN);
	assert (next->tokenString() == "bar");

	next = tokenizer.next();
	assert (next->tokenClass() == Token::EOF_TOKEN);
}


void StreamTokenizerTest::testTokenizer4()
{
	std::string data = "foo   123";
	std::istringstream istr(data);
	StreamTokenizer tokenizer(istr);
	tokenizer.addToken(new WhitespaceToken());
	tokenizer.addToken(new IdentifierToken());
	tokenizer.addToken(new IntLiteralToken());
	
	const Token* next = tokenizer.next();
	assert (next->tokenClass() == Token::IDENTIFIER_TOKEN);
	assert (next->tokenString() == "foo");

	next = tokenizer.next();
	assert (next->tokenClass() == Token::INTEGER_LITERAL_TOKEN);
	assert (next->asInteger() == 123);

	next = tokenizer.next();
	assert (next->tokenClass() == Token::EOF_TOKEN);
}


void StreamTokenizerTest::testTokenizer5()
{
	std::string data = "foo # 123";
	std::istringstream istr(data);
	StreamTokenizer tokenizer(istr);
	tokenizer.addToken(new WhitespaceToken());
	tokenizer.addToken(new IdentifierToken());
	tokenizer.addToken(new IntLiteralToken());
	
	const Token* next = tokenizer.next();
	assert (next->tokenClass() == Token::IDENTIFIER_TOKEN);
	assert (next->tokenString() == "foo");

	next = tokenizer.next();
	assert (next->tokenClass() == Token::INVALID_TOKEN);
	assert (next->tokenString() == "#");

	next = tokenizer.next();
	assert (next->tokenClass() == Token::INTEGER_LITERAL_TOKEN);
	assert (next->asInteger() == 123);

	next = tokenizer.next();
	assert (next->tokenClass() == Token::EOF_TOKEN);
}


void StreamTokenizerTest::testTokenizer6()
{
	std::string data = "foo 123 #";
	std::istringstream istr(data);
	StreamTokenizer tokenizer(istr);
	tokenizer.addToken(new WhitespaceToken());
	tokenizer.addToken(new IdentifierToken());
	tokenizer.addToken(new IntLiteralToken());
	
	const Token* next = tokenizer.next();
	assert (next->tokenClass() == Token::IDENTIFIER_TOKEN);
	assert (next->tokenString() == "foo");

	next = tokenizer.next();
	assert (next->tokenClass() == Token::INTEGER_LITERAL_TOKEN);
	assert (next->asInteger() == 123);

	next = tokenizer.next();
	assert (next->tokenClass() == Token::INVALID_TOKEN);
	assert (next->tokenString() == "#");

	next = tokenizer.next();
	assert (next->tokenClass() == Token::EOF_TOKEN);
}


void StreamTokenizerTest::testTokenizer7()
{
	std::string data = "  foo 123   ";
	std::istringstream istr(data);
	StreamTokenizer tokenizer(istr);
	tokenizer.addToken(new WhitespaceToken());
	tokenizer.addToken(new IdentifierToken());
	tokenizer.addToken(new IntLiteralToken());
	
	const Token* next = tokenizer.next();
	assert (next->tokenClass() == Token::IDENTIFIER_TOKEN);
	assert (next->tokenString() == "foo");

	next = tokenizer.next();
	assert (next->tokenClass() == Token::INTEGER_LITERAL_TOKEN);
	assert (next->asInteger() == 123);

	next = tokenizer.next();
	assert (next->tokenClass() == Token::EOF_TOKEN);
}


void StreamTokenizerTest::setUp()
{
}


void StreamTokenizerTest::tearDown()
{
}


CppUnit::Test* StreamTokenizerTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("StreamTokenizerTest");

	CppUnit_addTest(pSuite, StreamTokenizerTest, testTokenizer1);
	CppUnit_addTest(pSuite, StreamTokenizerTest, testTokenizer2);
	CppUnit_addTest(pSuite, StreamTokenizerTest, testTokenizer3);
	CppUnit_addTest(pSuite, StreamTokenizerTest, testTokenizer4);
	CppUnit_addTest(pSuite, StreamTokenizerTest, testTokenizer5);
	CppUnit_addTest(pSuite, StreamTokenizerTest, testTokenizer6);
	CppUnit_addTest(pSuite, StreamTokenizerTest, testTokenizer7);

	return pSuite;
}
