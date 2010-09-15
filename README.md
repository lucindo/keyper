keyper
======

**keyper** is a simple key-value store, result of my NIH syndrome.

Warning
-------

While this warning is here beware of very alpha piece of software.


Building and Installing
-----------------------

First you must install the following dependencies:

* [Kyoto Cabinet] [1]
* [Apache Thrift] [2]
* [Xapian Search Engine Library] [3]
* [CMake cross-platform build system] [4]

After that, to build the single server (keypers):

        make

Or these steps:

* generate C++ code from thrift IDL (on thrift directory):
        thrift -r --gen cpp keyper.thrift
* build keypers ("s" stands for single/server, distributed version to come), on server directory:
        cmake .
		make
* build clients stubs, thrift directory:
        thrift -r --gen py keyper.thrift # python
        thrift -r --gen rb keyper.thrift # ruby

Small python example (client directory): [cly.py] [5]

Features
--------

Supported types:

* key-value (with indexing)
* counters
* queues

Future
------

Support for:

* Security: Auth, cryptography
* Key expiration (LRU, etc)

Implement as a distributed system with the following features:

* No single point of failure
* Data distribution (sharding)
* Data replication (copies)
* No need to ever stop the system
* No limits (virtually)
* Advanced system control and monitoring
* Map-reduce tasks

Copyright and License
---------------------

[BOLA - Buena Onda License Agreement (v1.1)] [6]

<pre>
I don't like licenses, because I don't like having to worry about all this
legal stuff just for a simple piece of software I don't really mind anyone
using. But I also believe that it's important that people share and give back;
so I'm placing this work under the following license.


BOLA - Buena Onda License Agreement (v1.1)
------------------------------------------

This work is provided 'as-is', without any express or implied warranty. In no
event will the authors be held liable for any damages arising from the use of
this work.

To all effects and purposes, this work is to be considered Public Domain.


However, if you want to be "buena onda", you should:

1. Not take credit for it, and give proper recognition to the authors.
2. Share your modifications, so everybody benefits from them.
3. Do something nice for the authors.
4. Help someone who needs it: sign up for some volunteer work or help your
   neighbour paint the house.
5. Don't waste. Anything, but specially energy that comes from natural
   non-renewable resources. Extra points if you discover or invent something
   to replace them.
6. Be tolerant. Everything that's good in nature comes from cooperation.
</pre>

  [1]: http://1978th.net/kyotocabinet/            "Kyoto Cabinet"
  [2]: http://incubator.apache.org/thrift/        "Apache Thrift"
  [3]: http://xapian.org/                         "Xapian"
  [4]: http://www.cmake.org/                      "CMake"
  [5]: http://github.com/lucindo/keyper/blob/master/client/python/cli.py "cli.py"
  [6]: http://blitiri.com.ar/p/bola/               "BOLA - Buena Onda License Agreement (v1.1)"
