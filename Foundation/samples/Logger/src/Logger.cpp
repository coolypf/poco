//
// Logger.cpp
//
// $Id: //poco/1.2/Foundation/samples/Logger/src/Logger.cpp#1 $
//
// This class demonstrates the Logger, PatternFormatter, FormattingChannel,
// ConsoleChannel and FileChannel classes.
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


#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Message.h"


using Poco::Logger;
using Poco::PatternFormatter;
using Poco::FormattingChannel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::Message;


int main(int argc, char** argv)
{
	// set up two channel chains - one to the
	// console and the other one to a log file.
	FormattingChannel* pFCConsole = new FormattingChannel(new PatternFormatter("%s: %p: %t"));
	pFCConsole->setChannel(new ConsoleChannel);
	pFCConsole->open();
	
	FormattingChannel* pFCFile = new FormattingChannel(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%q:%t"));
	pFCFile->setChannel(new FileChannel("sample.log"));
	pFCFile->open();

	// create two Logger objects - one for
	// each channel chain.
	Logger& consoleLogger = Logger::create("ConsoleLogger", pFCConsole, Message::PRIO_INFORMATION);
	Logger& fileLogger    = Logger::create("FileLogger", pFCFile, Message::PRIO_WARNING);
	
	// log some messages
	consoleLogger.error("An error message");
	fileLogger.error("An error message");
	
	consoleLogger.warning("A warning message");
	fileLogger.error("A warning message");
	
	consoleLogger.information("An information message");
	fileLogger.information("An information message");
	
	Logger::get("ConsoleLogger").error("Another error message");
	
	return 0;
}
