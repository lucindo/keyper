// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "handler.hh"
#include "defaults.hh"

namespace keyper
{
    KeyperHandler::KeyperHandler()
    {
    }

    // server
    void KeyperHandler::ping()
    {
    }

    void KeyperHandler::version(std::string& _return)
    {
        UNUSED_ARG(_return);
    }


    // keyper

	void KeyperHandler::keyspace(const std::string& name, const bool index)
	{
		UNUSED_ARG(name);
		UNUSED_ARG(index);
	}

    void KeyperHandler::put(const std::string& key, const std::string& data)
    {
        UNUSED_ARG(key);
        UNUSED_ARG(data);
    }

    void KeyperHandler::get(std::string& _return, const std::string& key)
    {
        UNUSED_ARG(_return);
        UNUSED_ARG(key);
    }

    void KeyperHandler::getput(std::string& _return, const std::string& key, const std::string& data)
    {
        UNUSED_ARG(_return);
        UNUSED_ARG(key);
        UNUSED_ARG(data);
    }

    void KeyperHandler::mget(std::vector<item> & _return, const std::vector<std::string> & keys)
    {
        UNUSED_ARG(_return);
        UNUSED_ARG(keys);
    }

    void KeyperHandler::mput(const std::vector<item> & items)
    {
        UNUSED_ARG(items);
    }

    bool KeyperHandler::exists(const std::string& key)
    {
        UNUSED_ARG(key);
        return false;
    }

    void KeyperHandler::remove(const std::string& key)
    {
        UNUSED_ARG(key);
    }

    void KeyperHandler::rename(const std::string& oldkey, const std::string& newkey)
    {
        UNUSED_ARG(oldkey);
        UNUSED_ARG(newkey);
    }

    int64_t KeyperHandler::size()
    {
        return 0;
    }

    void KeyperHandler::keys(std::vector<std::string> & _return, const std::string& pattern)
    {
        UNUSED_ARG(_return);
        UNUSED_ARG(pattern);
    }

    void KeyperHandler::search(std::vector<std::string> & _return, const std::string& pattern)
    {
        UNUSED_ARG(_return);
        UNUSED_ARG(pattern);
    }
}
