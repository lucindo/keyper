// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "config.hh"
#include "defaults.hh"
#include "log.hh"

#include <iostream>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
namespace pt = boost::property_tree;

Config::Config()
    : host_(BIND_HOST), port_(BIND_PORT), thread_pool_size_(THREAD_POOL_SIZE)
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

bool Config::load_config()
{
    pt::ptree tree;
    
    try
	{
		pt::read_xml(this->config_file, tree);
		
		host_ = tree.get<std::string>("keyper.bind.host", BIND_HOST);
		
		port_ = tree.get("keyper.bind.port", BIND_PORT);
		
		thread_pool_size_ = tree.get("keyper.thread-pool.size", THREAD_POOL_SIZE);

		try
		{
			std::string log_level = tree.get<std::string>("keyper.log.level");

			lg::Logger::instance().level(log_level.c_str());
		}
		catch(...) {} // it's ok, default already setted

		return true;
    }
    catch(std::exception& ex)
    {
		std::cerr << "error reading file " << ex.what() << std::endl;
    }

    return false;
}

bool Config::command_line(int argc, char **argv)
{
	po::options_description desc("allowed options");
	desc.add_options()
		("config", po::value<std::string>(), "configuration file")
		;
	
	try
	{
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
		
		if (vm.count("config"))
		{
			this->config_file = vm["config"].as<std::string>();
			return true;
		}
	}
	catch (std::exception& ex)
	{
		std::cerr << "" << ex.what() << std::endl;
	}
    
	return false;
}

void Config::usage(const char * prog_name) const
{
    std::cerr << "usage: " << prog_name << " --config <config_file>" << std::endl;
}
