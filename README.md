keyper
======

**keyper** is a hardcore distributed and elastic key-value storage

Building and Installing
-----------------------

First you must install the following dependencies:

* [Kyoto Cabinet] [1]
* [Boost C++ library] [2]
* [Xapian Search Engine Library] [3]
* [CMake cross-platform build system] [4]

After that, to build the single server (keypers):

        cd single && cmake . && make

Features
--------

Supported types:

* key-value (with indexing)
* counters
* queues

System features:

* No single point of failure
* Data distribution (sharding)
* Data replication (copies)
* No need to ever stop de system
* No limits (virtually)
* Advanced system control and monitoring

Future
------

Support for:

* Map-reduce tasks
* Data indexing
* Security: Auth, SSL and cryptography
* ?? Key expiration (LRU, etc)

Copyright and License
---------------------

> Boost Software License - Version 1.0 - August 17th, 2003
> 
> Permission is hereby granted, free of charge, to any person or organization
> obtaining a copy of the software and accompanying documentation covered by
> this license (the "Software") to use, reproduce, display, distribute,
> execute, and transmit the Software, and to prepare derivative works of the
> Software, and to permit third-parties to whom the Software is furnished to
> do so, all subject to the following:
> 
> The copyright notices in the Software and this entire statement, including
> the above license grant, this restriction and the following disclaimer,
> must be included in all copies of the Software, in whole or in part, and
> all derivative works of the Software, unless such copies or derivative
> works are solely in the form of machine-executable object code generated by
> a source language processor.
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
> SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
> FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
> ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
> DEALINGS IN THE SOFTWARE.



  [1]: http://1978th.net/kyotocabinet/            "Kyoto Cabinet"
  [2]: http://www.boost.org/                      "Boost C++ library"
  [3]: http://xapian.org/                         "Xapian"
  [4]: http://www.cmake.org/					  "CMake"
