// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef COUNTER_HH
#define COUNTER_HH

#include <kchashdb.h>
#include <string>

using namespace kyotocabinet;

class Counter
{
private:
	static Counter instance_;
	Counter()
	{
	}
	~Counter()
	{
	}

	Counter(const Counter&);
	Counter & operator=(const Counter&);

	HashDB db_;

public:
	static Counter &instance();
    

	bool init(std::string data_dir);
	void fini();

	int64_t update(const std::string& name, int64_t delta);

	int64_t get(const std::string& name);

	uint64_t size();

	bool exists(const std::string& name);

	void remove(const std::string& name);
};

#endif // Counter_HH
