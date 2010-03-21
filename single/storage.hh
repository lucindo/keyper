// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef STORAGE_HH
#define STORAGE_HH

#include <string>
#include <cstdint>

class KVStore
{
private:
    std::string home_dir_;

public:
    KVStore(std::string home_dir);

    bool put(void * key, uint32_t keylen, void * value, uint64_t valuelen);

    void * get(void * key, uint32_t keylen);
};

#endif // STORAGE_HH
