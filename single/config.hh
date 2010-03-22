// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef CONFIG_HH
#define CONFIG_HH

#include <string>

class Config
{
private:
    std::string config_file;
    
public:
    Config();
    ~Config();

    bool command_line(int argc, char **argv);

    bool load_config();
    
    void usage(const char * prog_name) const;
};

#endif // CONFIG_HH
