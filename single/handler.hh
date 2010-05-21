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


        // keyper
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
    };

}

#endif // HANDLER_HH
