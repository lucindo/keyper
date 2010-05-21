// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef STORAGE_HH
#define STORAGE_HH

#include <kchashdb.h>
#include <string>

using namespace kyotocabinet;

class KVStore
{
private:
	static KVStore instance_;
	KVStore()
	{
	}
	~KVStore()
	{
	}

	KVStore(const KVStore&);
	KVStore & operator=(const KVStore&);

	HashDB db_;

public:
	static KVStore &instance();
    

	bool init(std::string data_dir);
	void fini();

    void put(const std::string& key, const std::string& data);

    void get(const std::string& key, std::string& data);
};

#endif // STORAGE_HH
