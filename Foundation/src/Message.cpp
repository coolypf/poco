//
// Message.cpp
//
// $Id: //poco/1.1.0/Foundation/src/Message.cpp#2 $
//
// Library: Foundation
// Package: Logging
// Module:  Message
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


#include "Foundation/Message.h"
#include "Foundation/Exception.h"
#include "Foundation/Process.h"
#include "Foundation/Thread.h"


Foundation_BEGIN


Message::Message(): 
	_prio(PRIO_FATAL), 
	_pMap(0), 
	_tid(0), 
	_pid(0)
{
	init();
}


Message::Message(const std::string& source, const std::string& text, Priority prio): 
	_source(source), 
	_text(text), 
	_prio(prio), 
	_pMap(0), 
	_tid(0),
	_pid(0)
{
	init();
}


Message::Message(const Message& msg)
{
	_source = msg._source;
	_text   = msg._text;
	_prio   = msg._prio;
	_time   = msg._time;
	_thread = msg._thread;
	_tid    = msg._tid;
	_pid    = msg._pid;
	if (msg._pMap)
		_pMap = new StringMap(*msg._pMap);
	else
		_pMap = 0;
}


Message::Message(const Message& msg, const std::string& text)
{
	_source = msg._source;
	_text   = text;
	_prio   = msg._prio;
	_time   = msg._time;
	_thread = msg._thread;
	_tid    = msg._tid;
	_pid    = msg._pid;
	if (msg._pMap)
		_pMap = new StringMap(*msg._pMap);
	else
		_pMap = 0;
}


Message::~Message()
{
	delete _pMap;
}


void Message::init()
{
	_pid = Process::id();
	Thread* pThread = Thread::current();
	if (pThread)
	{
		_tid    = pThread->id();
		_thread = pThread->name();
	}
}


Message& Message::operator = (const Message& msg)
{
	if (this == &msg) return *this;
	
	_source = msg._source;
	_text   = msg._text;
	_prio   = msg._prio;
	_time   = msg._time;
	_thread = msg._thread;
	_pid    = msg._pid;
	if (msg._pMap)
		_pMap = new StringMap(*msg._pMap);
	else
		_pMap = 0;
		
	return *this;
}


void Message::setSource(const std::string& src)
{
	_source = src;
}


void Message::setText(const std::string& text)
{
	_text = text;
}


void Message::setPriority(Priority prio)
{
	_prio = prio;
}


void Message::setTime(const Timestamp& t)
{
	_time = t;
}


const Timestamp& Message::getTime() const
{
	return _time;
}


void Message::setThread(const std::string& thread)
{
	_thread = thread;
}


void Message::setTid(long tid)
{
	_tid = tid;
}


void Message::setPid(long pid)
{
	_pid = pid;
}


const std::string& Message::operator [] (const std::string& param) const
{
	if (_pMap)
		return (*_pMap)[param];
	else
		throw NotFoundException();
}


std::string& Message::operator [] (const std::string& param)
{
	if (!_pMap)
		_pMap = new StringMap;
	return (*_pMap)[param];
}


Foundation_END
