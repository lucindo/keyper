// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "config.hh"
#include <iostream>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
namespace pt = boost::property_tree;

Config::Config()
{
}

Config::~Config()
{
}

bool Config::load_config()
{
    pt::ptree tree;
    
    try
    {
	pt::read_xml(this->config_file, tree);

	//m_file = tree.get<std::string>("keyper.filename");
    
	//m_level = tree.get("debug.level", 0);

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
   catch (...) // we're returning false anyway
   {
   }
    
   return false;
}

void Config::usage(const char * prog_name) const
{
    std::cerr << "usage: " << prog_name << " --config <config_file>" << std::endl;
}
