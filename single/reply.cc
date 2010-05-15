// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "reply.hh"

namespace keyper
{
	
	std::vector<boost::asio::const_buffer> reply::to_buffers()
	{
		std::vector<boost::asio::const_buffer> buffers;

		buffers.push_back(boost::asio::buffer(buffer));

		return buffers;
	}

	namespace stock_replies 
	{
		const char ok[] = "ok";
		const char bad_request[] = "bad_request";
		const char internal_server_error[] = "server_error";

		std::string to_string(reply::status_type status)
		{
			switch (status)
			{
				case reply::ok: return ok;
				case reply::bad_request: return bad_request;
				default: return internal_server_error;
			}
		}
	} // namespace stock_replies

	reply reply::stock_reply(reply::status_type status)
	{
		reply rep;
		rep.buffer = stock_replies::to_string(status);
		return rep;
	}
} // namespace keyper
