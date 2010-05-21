// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef HANDLER_HH
#define HANDLER_HH

#include "Keyper.h"

namespace keyper
{

    class KeyperHandler : public KeyperIf
    {
    public:
        KeyperHandler();

        // server
        void ping();
        void version(std::string& _return);

        // key-value
        void put(const std::string& key, const std::string& data);
        void get(std::string& _return, const std::string& key);
        void getput(std::string& _return, const std::string& key, const std::string& data);
        void mget(std::vector<item> & _return, const std::vector<std::string> & keys);
        void mput(const std::vector<item> & items);
        bool exists(const std::string& key);
        void remove(const std::string& key);
        void rename(const std::string& oldkey, const std::string& newkey);
        int64_t size();
        void keys(std::vector<std::string> & _return, const std::string& pattern);
        void search(std::vector<std::string> & _return, const std::string& pattern);

        // queue
        void qput(const std::string& name, const std::string& data);
        void qpeek(std::string& _return, const std::string& name);
        void qpop(std::string& _return, const std::string& name);
        int64_t qsize(const std::string& name);
        bool qexists(const std::string& name);
        void qempty(const std::string& name);

        // counter
        int64_t cincr(const std::string& name, const int64_t delta);
        int64_t cget(const std::string& name);
        int64_t cdecr(const std::string& name, const int64_t delta);
        bool cexists(const std::string& name);
        void cremove(const std::string& name);
    };

}

#endif // HANDLER_HH
