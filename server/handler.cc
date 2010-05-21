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


    // key-valye

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


    // queue
    void KeyperHandler::qput(const std::string& name, const std::string& data)
	{
		UNUSED_ARG(name);
		UNUSED_ARG(data);
	}

    void KeyperHandler::qpeek(std::string& _return, const std::string& name)
	{
		UNUSED_ARG(name);
		UNUSED_ARG(_return);
	}

    void KeyperHandler::qpop(std::string& _return, const std::string& name)
	{
		UNUSED_ARG(name);
		UNUSED_ARG(_return);
	}

    int64_t KeyperHandler::qsize(const std::string& name)
	{
		UNUSED_ARG(name);
	}

    void KeyperHandler::qempty(const std::string& name)
	{
		UNUSED_ARG(name);
	}

    // counter
    int64_t KeyperHandler::cincr(const std::string& name, const int64_t delta)
	{
		UNUSED_ARG(name);
		UNUSED_ARG(delta);
	}

    int64_t KeyperHandler::cget(const std::string& name)
	{
		UNUSED_ARG(name);
	}

    int64_t KeyperHandler::cdecr(const std::string& name, const int64_t delta)
	{
		UNUSED_ARG(name);
		UNUSED_ARG(delta);
	}

    void KeyperHandler::cremove(const std::string& name)
	{
		UNUSED_ARG(name);
	}
}
