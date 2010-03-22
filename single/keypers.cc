// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "keypers.hh"
#include "config.hh"

int main(int argc, char** argv)
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
    
    return 0;
}
