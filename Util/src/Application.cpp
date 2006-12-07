//
// Application.cpp
//
// $Id: //poco/1.2/Util/src/Application.cpp#2 $
//
// Library: Util
// Package: Application
// Module:  Application
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


#include "Poco/Util/Application.h"
#include "Poco/Util/SystemConfiguration.h"
#include "Poco/Util/MapConfiguration.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/Util/IniFileConfiguration.h"
#include "Poco/Util/XMLConfiguration.h"
#include "Poco/Util/LoggingSubsystem.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionProcessor.h"
#include "Poco/Util/Validator.h"
#include "Poco/Environment.h"
#include "Poco/Exception.h"
#include "Poco/NumberFormatter.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/String.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/AutoPtr.h"
#if defined(POCO_OS_FAMILY_WINDOWS)
#include <windows.h>
#endif
#if defined(POCO_OS_FAMILY_UNIX)
#include "Poco/SignalHandler.h"
#endif
#if defined(POCO_WIN32_UTF8)
#include "Poco/UnicodeConverter.h"
#endif


using Poco::Logger;
using Poco::Path;
using Poco::File;
using Poco::Environment;
using Poco::SystemException;
using Poco::ConsoleChannel;
using Poco::NumberFormatter;
using Poco::AutoPtr;
using Poco::icompare;


namespace Poco {
namespace Util {


Application* Application::_pInstance = 0;


Application::Application():
	_pConfig(new LayeredConfiguration),
	_initialized(false),
	_unixOptions(true),
	_pLogger(&Logger::get("ApplicationStartup")),
	_stopOptionsProcessing(false)
{
	setup();
}


Application::Application(int argc, char* argv[]):
	_pConfig(new LayeredConfiguration),
	_initialized(false),
	_unixOptions(true),
	_pLogger(&Logger::get("ApplicationStartup")),
	_stopOptionsProcessing(false)
{
	setup();
	init(argc, argv);
}


Application::~Application()
{
	try
	{
		uninitialize();
	}
	catch (...)
	{
	}
	_pInstance = 0;
}


void Application::setup()
{
	poco_assert (_pInstance == 0);

	_pConfig->add(new SystemConfiguration, PRIO_SYSTEM, false, false);
	_pConfig->add(new MapConfiguration, PRIO_APPLICATION, true, false);
	
	addSubsystem(new LoggingSubsystem);
	
#if defined(POCO_OS_FAMILY_UNIX)
	#if !defined(_DEBUG)
	Poco::SignalHandler::install();
	#endif
#else
	setUnixOptions(false);
#endif

	_pInstance = this;

	AutoPtr<ConsoleChannel> pCC = new ConsoleChannel;
	Logger::setChannel("", pCC);
}


void Application::addSubsystem(Subsystem* pSubsystem)
{
	poco_check_ptr (pSubsystem);

	_subsystems.push_back(pSubsystem);
}


void Application::init(int argc, char* argv[])
{
	setArgs(argc, argv);
	init();
}


#if defined(POCO_WIN32_UTF8)
void Application::init(int argc, wchar_t* argv[])
{
	std::vector<std::string> args;
	for (int i = 0; i < argc; ++i)
	{
		std::string arg;
		Poco::UnicodeConverter::toUTF8(argv[i], arg);
		args.push_back(arg);
	}
	init(args);
}
#endif


void Application::init(const std::vector<std::string>& args)
{
	setArgs(args);
	init();
}


void Application::init()
{
	Path appPath;
	getApplicationPath(appPath);
	_pConfig->setString("application.path", appPath.toString());
	_pConfig->setString("application.name", appPath.getFileName());
	_pConfig->setString("application.baseName", appPath.getBaseName());
	_pConfig->setString("application.dir", appPath.parent().toString());
	_pConfig->setString("application.configDir", appPath.parent().toString());
	processOptions();
	initialize(*this);
}


const char* Application::name() const
{
	return "Application";
}


void Application::initialize(Application& self)
{
	for (SubsystemVec::iterator it = _subsystems.begin(); it != _subsystems.end(); ++it)
	{
		_pLogger->debug(std::string("Initializing subsystem: ") + (*it)->name());
		(*it)->initialize(self);
	}
	_initialized = true;
}

	
void Application::uninitialize()
{
	if (_initialized)
	{
		for (SubsystemVec::reverse_iterator it = _subsystems.rbegin(); it != _subsystems.rend(); ++it)
		{
			_pLogger->debug(std::string("Uninitializing subsystem: ") + (*it)->name());
			(*it)->uninitialize();
		}
		_initialized = false;
	}
}


void Application::reinitialize(Application& self)
{
	for (SubsystemVec::iterator it = _subsystems.begin(); it != _subsystems.end(); ++it)
	{
		_pLogger->debug(std::string("Re-initializing subsystem: ") + (*it)->name());
		(*it)->reinitialize(self);
	}
}


void Application::setUnixOptions(bool flag)
{
	_unixOptions = flag;
}


int Application::loadConfiguration(int priority)
{
	int n = 0;
	Path appPath;
	getApplicationPath(appPath);
	Path cfgPath;
	if (findAppConfigFile(appPath.getBaseName(), "properties", cfgPath))
	{
		_pConfig->add(new PropertyFileConfiguration(cfgPath.toString()), priority, false, false);
		++n;
	}
	if (findAppConfigFile(appPath.getBaseName(), "ini", cfgPath))
	{
		_pConfig->add(new IniFileConfiguration(cfgPath.toString()), priority, false, false);
		++n;
	}
	if (findAppConfigFile(appPath.getBaseName(), "xml", cfgPath))
	{
		_pConfig->add(new XMLConfiguration(cfgPath.toString()), priority, false, false);
		++n;
	}
	if (n > 0)
	{
		_pConfig->setString("application.configDir", cfgPath.parent().toString());
	}
	return n;
}


void Application::loadConfiguration(const std::string& path, int priority)
{
	Path confPath(path);
	std::string ext = confPath.getExtension();
	if (icompare(ext, "properties") == 0)
		_pConfig->add(new PropertyFileConfiguration(confPath.toString()), priority, false, false);
	else if (icompare(ext, "ini") == 0)
		_pConfig->add(new IniFileConfiguration(confPath.toString()), priority, false, false);
	else if (icompare(ext, "xml") == 0)
		_pConfig->add(new XMLConfiguration(confPath.toString()), priority, false, false);
	else
		throw Poco::InvalidArgumentException("Unsupported configuration file type", ext);
}


std::string Application::commandName() const
{
	return _pConfig->getString("application.baseName");
}


void Application::stopOptionsProcessing()
{
	_stopOptionsProcessing = true;
}


int Application::run()
{
	try
	{
		return main(_args);
	}
	catch (Poco::Exception& exc)
	{
		logger().log(exc);
	}
	catch (std::exception& exc)
	{
		logger().error(exc.what());
	}
	catch (...)
	{
		logger().fatal("system exception");
	}
	return EXIT_SOFTWARE;
}


int Application::main(const std::vector<std::string>& args)
{
	return EXIT_OK;
}


void Application::setArgs(int argc, char* argv[])
{
	_command = argv[0];
	_pConfig->setInt("application.argc", argc);
	_args.reserve(argc);
	std::string argvKey = "application.argv[";
	for (int i = 0; i < argc; ++i)
	{
		std::string arg(argv[i]);
		_pConfig->setString(argvKey + NumberFormatter::format(i) + "]", arg);
		_args.push_back(arg);
	}
}


void Application::setArgs(const std::vector<std::string>& args)
{
	poco_assert (!args.empty());
	
	_command = args[0];
	_pConfig->setInt("application.argc", (int) args.size());
	_args = args;
	std::string argvKey = "application.argv[";
	for (int i = 0; i < args.size(); ++i)
	{
		_pConfig->setString(argvKey + NumberFormatter::format(i) + "]", args[i]);
	}
}


void Application::processOptions()
{
	defineOptions(_options);
	OptionProcessor processor(_options);
	processor.setUnixStyle(_unixOptions);
	_args.erase(_args.begin());
	ArgVec::iterator it = _args.begin();
	while (it != _args.end() && !_stopOptionsProcessing)
	{
		std::string name;
		std::string value;
		if (processor.process(*it, name, value))
		{
			handleOption(name, value);
			it = _args.erase(it);
		}
		else ++it;
	}
	if (!_stopOptionsProcessing)
		processor.checkRequired();
}


void Application::getApplicationPath(Poco::Path& appPath) const
{
#if defined(POCO_OS_FAMILY_UNIX)
	if (_command.find('/') != std::string::npos)
	{
		Path path(_command);
		if (path.isAbsolute())
		{
			appPath = path;
		}
		else
		{
			appPath = Path::current();
			appPath.append(path);
		}
	}
	else
	{
		if (!Path::find(Environment::get("PATH"), _command, appPath))
			appPath = Path(Path::current(), _command);
	}
#elif defined(POCO_OS_FAMILY_WINDOWS)
	#if defined(POCO_WIN32_UTF8)
		wchar_t path[1024];
		int n = GetModuleFileNameW(0, path, sizeof(path)/sizeof(wchar_t));
		if (n > 0)
		{
			std::string p;
			Poco::UnicodeConverter::toUTF8(path, p);
			appPath = p;
		}
		else throw SystemException("Cannot get application file name.");
	#else
		char path[1024];
		int n = GetModuleFileName(0, path, sizeof(path));
		if (n > 0)
			appPath = path;
		else
			throw SystemException("Cannot get application file name.");
	#endif
#else
	appPath = _command;
#endif
}


bool Application::findFile(Poco::Path& path) const
{
	if (path.isAbsolute()) return true;
	
	Path appPath;
	getApplicationPath(appPath);
	Path base = appPath.parent();
	while (base.depth() > 0)
	{
		Path p(base, path);
		File f(p);
		if (f.exists())
		{
			path = p;
			return true;
		}
		base.popDirectory();
	}
	return false;
}


bool Application::findAppConfigFile(const std::string& appName, const std::string& extension, Path& path) const
{
	poco_assert (!appName.empty());

	Path p(appName);
	p.setExtension(extension);
	bool found = findFile(p);
	if (!found)
	{
#if defined(_DEBUG)
		if (appName[appName.length() - 1] == 'd')
		{
			p.setBaseName(appName.substr(0, appName.length() - 1));
			found = findFile(p);
		}
#endif
	}
	if (found)
		path = p;
	return found;
}


void Application::defineOptions(OptionSet& options)
{
}


void Application::handleOption(const std::string& name, const std::string& value)
{
	const Option& option = _options.getOption(name);
	if (option.validator())
	{
		option.validator()->validate(option, value);
	}
	if (!option.binding().empty())
	{
		AbstractConfiguration* pConfig = option.config();
		if (!pConfig) pConfig = &config();
		pConfig->setString(option.binding(), value);
	}
	if (option.callback())
	{
		option.callback()->invoke(name, value);
	}
}


void Application::setLogger(Logger& logger)
{
	_pLogger = &logger;
}


} } // namespace Poco::Util
