// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "server.hh"
#include "log.hh"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace keyper
{
	server::server(const std::string& address, const std::string& port, uint32_t thread_pool_size)
		: thread_pool_size_(thread_pool_size),
		  acceptor_(io_service_),
		  new_connection_(new connection(io_service_, request_handler_))
	{
		// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
		boost::asio::ip::tcp::resolver resolver(io_service_);
		boost::asio::ip::tcp::resolver::query query(address, port);
		boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
		acceptor_.open(endpoint.protocol());
		acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		l(lg::debug, "attempting to bind address %s:%s", address.c_str(), port.c_str());
		acceptor_.bind(endpoint);
		l(lg::debug, "address %s:%s successfully bound", address.c_str(), port.c_str());
		l(lg::debug, "attempting to listen on %s:%s", address.c_str(), port.c_str());
		acceptor_.listen();
		l(lg::info, "listening for connections on %s:%s", address.c_str(), port.c_str());
		acceptor_.async_accept(new_connection_->socket(),
							   boost::bind(&server::handle_accept, this,
										   boost::asio::placeholders::error));
	}

	void server::run()
	{
		l(lg::debug, "creating thread-pool with %d threads", thread_pool_size_);

		// Create a pool of threads to run all of the io_services.
		std::vector<boost::shared_ptr<boost::thread> > threads;
		for (std::size_t i = 0; i < thread_pool_size_; ++i)
		{
			boost::shared_ptr<boost::thread> thread(new boost::thread(
														boost::bind(&boost::asio::io_service::run, &io_service_)));
			threads.push_back(thread);
		}

		l(lg::info, "thread-pool (%d threads) created", thread_pool_size_);

		// Wait for all threads in the pool to exit.
		for (std::size_t i = 0; i < threads.size(); ++i)
			threads[i]->join();
	}

	void server::stop()
	{
		l(lg::debug, "stopping I/O service");
		io_service_.stop();
		l(lg::info, "system I/O service stopped successfully");
	}

	void server::handle_accept(const boost::system::error_code& error)
	{
		if (not error)
		{
			l(lg::debug, "new connection accepted, starting handler");
			new_connection_->start();
			new_connection_.reset(new connection(io_service_, request_handler_));
			acceptor_.async_accept(new_connection_->socket(),
								   boost::bind(&server::handle_accept, this,
											   boost::asio::placeholders::error));
		}
	}
} // namespace keyper
