// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef SERVER_HH
#define SERVER_HH

#include <string>
#include <vector>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "connection.hh"
#include "request_handler.hh"

namespace keyper 
{
	class server : private boost::noncopyable
	{
	private:
		// The number of threads that will call io_service::run().
		std::size_t thread_pool_size_;

		boost::asio::io_service io_service_;
		boost::asio::ip::tcp::acceptor acceptor_;

		// The next connection to be accepted.
		connection_ptr new_connection_;

		// The handler for all incoming requests.
		request_handler request_handler_;


	public:
		// Construct the server to listen on the specified TCP address and port.
		explicit server(const std::string& address, const std::string& port, uint32_t thread_pool_size);

		void run();

		void stop();

	private:
		void handle_accept(const boost::system::error_code& e);
	};

} // namespace keyper


#endif // SERVER_HH
