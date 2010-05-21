// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "storage.hh"
#include "counter.hh"
#include "handler.hh"
#include "defaults.hh"
#include "log.hh"

namespace keyper
{
    KeyperHandler::KeyperHandler()
    {
    }

    // server

    void KeyperHandler::ping()
    {
        l(lg::debug, "ping called");
    }

    void KeyperHandler::version(std::string& _return)
    {
        l(lg::debug, "version called");

        _return = std::string(KEYPER_VERSION);
    }


    // key-valye

    void KeyperHandler::put(const std::string& key, const std::string& data)
    {
        l(lg::debug, "put called with key %s and %d bytes of value", key.c_str(), data.size());

        KVStore::instance().put(key, data);
    }

    void KeyperHandler::get(std::string& _return, const std::string& key)
    {
        l(lg::debug, "get called for key %s", key.c_str());

        KVStore::instance().get(key, _return);
    }

    void KeyperHandler::getput(std::string& _return, const std::string& key, const std::string& data)
    {
        l(lg::debug, "getput called for key %s and %d bytes of value", key.c_str(), data.size());

        KVStore::instance().get(key, _return);
        KVStore::instance().put(key, data);
    }

    void KeyperHandler::mget(std::vector<item> & _return, const std::vector<std::string> & keys)
    {
        l(lg::debug, "mget called witg %d keys", keys.size());

        _return.resize(keys.size());

        for (std::size_t key = 0; key < keys.size(); key++)
        {
            _return[key].key = keys[key];
            KVStore::instance().get(keys[key], _return[key].value);
        }
    }

    void KeyperHandler::mput(const std::vector<item> & items)
    {
        l(lg::debug, "mput called witg %d items", items.size());

        for (std::size_t item = 0; item < items.size(); item++)
        {
            KVStore::instance().put(items[item].key, items[item].value);
        }
    }

    bool KeyperHandler::exists(const std::string& key)
    {
        l(lg::debug, "exists called with key %s", key.c_str());

        return KVStore::instance().exists(key);
    }

    void KeyperHandler::remove(const std::string& key)
    {
        l(lg::debug, "remove called with key %s", key.c_str());

        KVStore::instance().remove(key);
    }

    void KeyperHandler::rename(const std::string& oldkey, const std::string& newkey)
    {
        l(lg::debug, "rename called with oldkey %s and newkey %s", oldkey.c_str(), newkey.c_str());

        KVStore::instance().rename(oldkey, newkey);
    }

    int64_t KeyperHandler::size()
    {
        l(lg::debug, "size called");

        return KVStore::instance().size();
    }

    void KeyperHandler::keys(std::vector<std::string> & _return, const std::string& pattern)
    {
        l(lg::debug, "keys called with pattern %s", pattern.c_str());

        KVStore::instance().keys(pattern, _return);
    }

    void KeyperHandler::search(std::vector<std::string> & _return, const std::string& pattern)
    {
        l(lg::debug, "search called with pattern %s", pattern.c_str());

        KVStore::instance().search(pattern, _return);
    }


    // queue (TODO)
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

    bool KeyperHandler::qexists(const std::string& name)
    {
        UNUSED_ARG(name);
        return false;
    }

    void KeyperHandler::qempty(const std::string& name)
    {
        UNUSED_ARG(name);
    }

    // counter
    int64_t KeyperHandler::cincr(const std::string& name, const int64_t delta)
    {
        l(lg::debug, "cincr called counter %s delta %d", name.c_str(), delta);

        return Counter::instance().update(name, delta);
    }

    int64_t KeyperHandler::cget(const std::string& name)
    {
        l(lg::debug, "cget called counter %s", name.c_str());

        return Counter::instance().get(name);
    }

    int64_t KeyperHandler::cdecr(const std::string& name, const int64_t delta)
    {
        l(lg::debug, "cdecr called counter %s delta %d", name.c_str(), -delta);

        return Counter::instance().update(name, -delta);
    }

    bool KeyperHandler::cexists(const std::string& name)
    {
        l(lg::debug, "cexists called counter %s", name.c_str());

        return Counter::instance().exists(name);
    }

    void KeyperHandler::cremove(const std::string& name)
    {
        l(lg::debug, "cremove called counter %s", name.c_str());

        Counter::instance().remove(name);
    }
}
