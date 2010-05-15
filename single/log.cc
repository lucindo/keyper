// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "log.hh"
#include <cstdarg>
#include <ctime>
#include <cstdio>
#include <cstring>

#include <iostream>

#include "defaults.hh"

namespace lg
{
    Logger Logger::instance_;
	
    Logger& Logger::instance()
    {
		return instance_;
    }
	
    const char * Logger::name_of(log_level level) const
    {
		switch (level)
		{
			case debug:   return "debug";
			case info:    return "info";
			case notice:  return "notice";
			case error:   return "error";
			case warning: return "warning";
			case critial: return "critial";
			default: break;
		}
		return "unknown";
    }

	log_level Logger::level_of(const char * name) const
	{
		if (strcasecmp("debug", name) == 0) return debug;
		else if (strcasecmp("info", name) == 0) return info;
		else if (strcasecmp("notice", name) == 0) return notice;
		else if (strcasecmp("error", name) == 0) return error;
		else if (strcasecmp("warning", name) == 0) return warning;
		else if (strcasecmp("critial", name) == 0) return critial;
		return DEFAULT_LOG_LEVEL;
	}

	void Logger::level(const char *name)
	{
		this->level(level_of(name));
	}

    void Logger::level(log_level level)
    {
		this->level_ = level;
    }
    
    log_level Logger::level() const
    {
		return this->level_;
    }

    void Logger::log(const char * str)
    {
		const int size = 256;
		char buffer[size] = { 0, };
		time_t now = time(NULL);
		struct tm * tnow;

		tnow = localtime(&now);
		strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tnow);
	
		std::cout << name_of(level_) << " | " << buffer << " | "<< str << std::endl;
    }
}

void l(lg::log_level level, const char * fmt, ...)
{
    if (level >= lg::Logger::instance().level())
    {
		const int size = 1024;
		char buffer[size] = { 0, };
		va_list ap;
	
		va_start(ap, fmt);
		vsnprintf(buffer, size, fmt, ap);
		va_end(ap);
		
		lg::Logger::instance().log(buffer);
    }
}
