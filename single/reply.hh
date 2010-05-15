// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef REPLY_HH
#define REPLY_HH

#include <string>
#include <vector>
#include <boost/asio.hpp>

namespace keyper
{
	struct reply
	{
		enum status_type
		{
			ok,
			bad_request
		} status;

		std::string buffer;

		std::vector<boost::asio::const_buffer> to_buffers();

		static reply stock_reply(status_type status);
	};

} // namespace keyper

#endif // REPLY_HH
