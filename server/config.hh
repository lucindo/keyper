// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef CONFIG_HH
#define CONFIG_HH

#include <string>
#include <stdint.h> // avoiding <cstdint>

class Config
{
private:
    std::string host_;
    uint32_t port_;
    uint32_t thread_pool_size_;
    std::string data_dir_;

public:
    Config();
    ~Config();

    bool command_line(int argc, char **argv);

    void usage(const char * prog_name) const;

    // getters

    std::string host() const;
    uint32_t port() const;
    uint32_t thread_pool_size() const;
    std::string data_dir() const;
};

#endif // CONFIG_HH
