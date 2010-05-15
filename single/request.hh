// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef REQUEST_HH
#define REQUEST_HH

#include <string>

namespace keyper
{

	struct request
	{
		std::string buffer;
		std::string line;
	};

} // namespace keyper

#endif // REQUEST_HH
