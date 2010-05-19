// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "keypers.hh"
#include "config.hh"
#include "log.hh"

int main(int argc, char** argv) try
{
    Config config;
    
    if (not config.command_line(argc, argv))
    {
		config.usage(argv[0]);
		return ERROR_PROCESSING_COMMAND_LINE;
    }

    if (not config.load_config())
    {
		return ERROR_LOADING_CONFG_FILE;
    }

    l(lg::info, "will bing at: %s:%s [%d threads]", config.host().c_str(), config.port().c_str(), config.thread_pool_size());

    return 0;
}
catch (std::exception& ex)
{
	l(lg::error, "exception in main thread: %s", ex.what());
}
