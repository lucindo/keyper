// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

include "server.thrift"

namespace cpp keyper
namespace py keyper

// A simple key-value item
struct item
{
	1:string key,
	2:binary value
}

service Keyper extends server.Server
{
    # key-value methods

	// set a value for a given key (create/replace)
	void put(1:string key, 2:binary data),
	
	// get the value of a key
	binary get(1:string key),

	// set a value for a key and returns the old one
	binary getput(1:string key, 2:binary data),

	// multiple get
	list<item> mget(1:list<string> keys),

	// multiple put
	void mput(1:list<item> items),

	// verify if a key exists
	bool exists(1:string key),

	// deletes a key
	void remove(1:string key),

	// rename a key (replace destination if exists)
	void rename(1:string oldkey, 2:string newkey),	

	// number of existing keys
	i64 size(),

	// return a list of keys that match a pattern
	list<string> keys(1:string pattern),

	// return a list of keys with its values match a pattern
	list<string> search(1:string pattern),

	# queue methods

	// equeue a element (may create a new queue)
	void qput(1:string name, 2:binary data),

	// return the first element (but not remove)
	binary qpeek(1:string name),

	// return and removes the first element
	binary qpop(1:string name),

	// return the number of itens queued
	i64 qsize(1:string name),

	// delete the queue
	void qempty(1:string name),

	# counter protocol

	// increments the counter and returns its new value (may create it)
	i64 cincr(1:string name, 2:i64 delta),

	// get the counter value
	i64 cget(1:string name),

	// decrements the counter and returns its new value
	i64 cdecr(1:string name, 2:i64 delta),

	// removes the counter
	void cremove(1:string name)
}
