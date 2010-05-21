// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "counter.hh"
#include "log.hh"

using namespace kyotocabinet;

#include <sstream>

template<typename output, typename input>
output stream_cast(const input &in)
{
	std::stringstream ss;
	output out;
	
	ss << in;
	ss >> out;
	
	return out;
}


Counter Counter::instance_;

Counter& Counter::instance()
{
	return instance_;
}

bool Counter::init(std::string data_dir)
{
	std::string db_name = data_dir + "counter.kch";

	l(lg::debug, "opening hash db [%s]", db_name.c_str());

	if (not db_.open(db_name.c_str(), HashDB::OWRITER | HashDB::OCREATE))
	{
		l(lg::error, "error opening hash db [%s]: %s", db_name.c_str(), db_.error().name());
		return false;
	}
	
	return true;
}

void Counter::fini()
{
	if (not db_.close())
	{
		l(lg::error, "error closing hash db: %s", db_.error().name());
	}
} 
   
int64_t Counter::update(const std::string& name, int64_t delta)
{
	// TODO: use a smart pointer
	std::string* value = db_.get(name);
	int64_t data = 0;
	if (value)
	{
		data = stream_cast<int64_t>(*value);
		delete value;
		
		data += delta;

		db_.set(name, stream_cast<std::string>(data));
	}
	else
	{
		db_.set(name, stream_cast<std::string>(delta));
	}
}

int64_t Counter::get(const std::string& name)
{
	// TODO: use a smart pointer
	std::string* value = db_.get(name);
	int64_t data = 0;
	if (value)
	{
		data = stream_cast<int64_t>(*value);
		delete value;
	}
	return data;
}

uint64_t Counter::size()
{
	return db_.count();
}

bool Counter::exists(const std::string& name)
{
	// TODO: use a smart pointer
	std::string* value = db_.get(name);
	bool found = false;
	if (value)
	{
		found = true;
		delete value;
	}

	return found;
}

void Counter::remove(const std::string& name)
{
	db_.remove(name);
}
