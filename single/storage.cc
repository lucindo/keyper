// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "storage.hh"

KVStore::KVStore(std::string home_dir) : home_dir_(home_dir)
{
}

bool KVStore::put(void * key, uint32_t keylen, void * value, uint64_t valuelen)
{
    return true;
}

void * KVStore::get(void * key, uint32_t keylen)
{
    return NULL;
}
