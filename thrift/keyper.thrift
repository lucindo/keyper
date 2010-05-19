
include "server.thrift"

namespace cpp keyper

struct item
{
    1:string key,
	2:binary value
}

service Keyper extends server.Server
{
    void keyspace(1:string name, 2:bool index),

	void put(1:string key, 2:binary data),
	
	binary get(1:string key),

	binary getput(1:string key, 2:binary data),

	list<item> mget(1:list<string> keys),

	void mput(1:list<item> items),

	bool exists(1:string key),

	void remove(1:string key),

	void rename(1:string oldkey, 2:string newkey),	

	i64 size(),

	list<string> keys(1:string pattern),

	list<string> search(1:string pattern)
}
