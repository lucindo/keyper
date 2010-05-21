// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "storage.hh"
#include "log.hh"

using namespace kyotocabinet;

KVStore KVStore::instance_;

KVStore& KVStore::instance()
{
	return instance_;
}

bool KVStore::init(std::string data_dir)
{
	std::string db_name = data_dir + "default.kch";

	l(lg::debug, "opening hash db [%s]", db_name.c_str());

	if (not db_.open(db_name.c_str(), HashDB::OWRITER | HashDB::OCREATE))
	{
		l(lg::error, "error opening hash db [%s]: %s", db_name.c_str(), db_.error().name());
		return false;
	}
	
	return true;
}

void KVStore::fini()
{
	if (not db_.close())
	{
		l(lg::error, "error closing hash db: %s", db_.error().name());
	}
} 
   
void KVStore::put(const std::string& key, const std::string& data)
{
	db_.set(key, data);
}

void KVStore::get(const std::string& key, std::string& data)
{
	std::string* value = db_.get(key);
	if (value)
	{
		data = *value;
	}
}

