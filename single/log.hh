// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef LOG_HH
#define LOG_HH

#include "defaults.hh"

namespace log
{
    enum log_level
    {
	debug = 1,
	info,
	notice,
	error,
	warning,
	critial
    };
    
    class Logger
    {
    private:
	// Singleton
	static Logger instance_;
	Logger() :
	    level_(DEFAULT_LOG_LEVEL)
	{
	}
	~Logger() {} 
	Logger(const Logger &);
	Logger & operator=(const Logger &);

	// private functions
	const char * name_of(log_level level);
	
	// members
	log_level level_;
	
    public:
	static Logger &instance();

	void level(log_level level);
	log_level level() const;

	void log(const char * str);
    };
}

void l(log::log_level level, char * fmt, ...);

#endif // LOG_HH
