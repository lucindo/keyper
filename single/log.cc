// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "log.hh"
#include <cstdarg>
#include <ctime>
#include <cstdio>

#include <iostream>

namespace log
{
    Logger Logger::instance_;

    Logger& Logger::instance()
    {
	return instance_;
    }

    const char * Logger::name_of(log_level level)
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

void l(log::log_level level, char * fmt, ...)
{
    if (level >= log::Logger::instance().level())
    {
	const int size = 1024;
	char buffer[size] = { 0, };
	va_list ap;
	
	va_start(ap, fmt);
	vsnprintf(buffer, size, fmt, ap);
	va_end(ap);

	log::Logger::instance().log(buffer);
    }
}
