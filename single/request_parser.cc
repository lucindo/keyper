// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "request_parser.hh"
#include "request.hh"

namespace keyper
{
	request_parser::request_parser()
	{
	}

	boost::tribool request_parser::consume(request& req, char input)
	{
		if (is_ctl(input))
		{
			req.line = req.buffer;
			req.buffer.clear();
			return true;
		}
		else
		{
			req.buffer.push_back(input);
			return boost::indeterminate;
		}
	}

	bool request_parser::is_ctl(int c)
	{
		return (c >= 0 && c <= 31) || (c == 127);
	}
} // namespace keyper
