//
// grep.cpp
//
// $Id: //poco/1.1.0/Foundation/samples/grep/src/grep.cpp#2 $
//
// This sample demonstrates the RegularExpression class.
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


#include "Foundation/RegularExpression.h"
#include <iostream>


using Foundation::RegularExpression;


int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "usage: " << argv[0] << ": [-i] [-x] pattern" << std::endl;
		return 1;
	}
	
	std::string pattern;
	int options = 0;
	for (int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		if (arg == "-i")
			options += RegularExpression::RE_CASELESS;
		else if (arg == "-x")
			options += RegularExpression::RE_EXTENDED;
		else
			pattern = arg;
	}
	
	RegularExpression re(pattern, options);
	
	int c = std::cin.get();
	while (c != -1)
	{
		std::string line;
		while (c != -1 && c != '\n')
		{
			line += (char) c;
			c = std::cin.get();
		}

		RegularExpression::Match mtch;
		if (re.match(line, mtch))
			std::cout << line << std::endl;

		if (c != -1) c = std::cin.get();
	}
	
	return 0;
}
