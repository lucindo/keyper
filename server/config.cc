// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "config.hh"
#include "defaults.hh"
#include "log.hh"

#include <unistd.h> // for getopt

#include <iostream>
#include <cstdlib>

Config::Config()
    : host_(DEFAULT_BIND_HOST),
      port_(DEFAULT_BIND_PORT),
      thread_pool_size_(DEFAULT_THREAD_POOL_SIZE),
      data_dir_(DEFAULT_DATA_DIR)
{
}

Config::~Config()
{
}

std::string Config::host() const
{
    return host_;
}

uint32_t Config::port() const
{
    return port_;
}

uint32_t Config::thread_pool_size() const
{
    return thread_pool_size_;
}

std::string Config::data_dir() const
{
    return data_dir_;
}

bool Config::command_line(int argc, char **argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "h:p:t:l:d:")) != -1)
    {
        switch (opt)
        {
            case 'h':
                host_ = std::string(optarg);
                break;
            case 'p':
                port_ = std::atoi(optarg);
                break;
            case 't':
                thread_pool_size_ = std::atoi(optarg);
                break;
            case 'l':
                lg::Logger::instance().level(optarg);
                break;
            case 'd':
                data_dir_ = std::string(optarg);
                if (data_dir_[data_dir_.size() - 1] != '/') data_dir_ += "/";
                break;
            default:
                return false;
        }
    }

    return true;
}

void Config::usage(const char * prog_name) const
{
    std::cerr
        << "usage: " << prog_name << " [options]" << std::endl
        << "options are:" << std::endl
        << "              -h <host>     (default " << DEFAULT_BIND_HOST << ")" << std::endl
        << "              -p <port>     (default " << DEFAULT_BIND_PORT << ")" << std::endl
        << "              -t <#threads> (default " << DEFAULT_THREAD_POOL_SIZE << ")" << std::endl
        << "              -d <data dir> (default " << DEFAULT_DATA_DIR << ")" << std::endl
        << "              -l <loglevel> (default " << DEFAULT_LOG_LEVEL_STR << ")" << std::endl;
}
