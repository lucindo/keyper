// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "keypers.hh"
#include "config.hh"
#include "log.hh"
#include "server.hh"

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <pthread.h>
#include <signal.h>

int main(int argc, char** argv) try
{
    Config config;
    
    if (not config.command_line(argc, argv))
    {
		config.usage(argv[0]);
		return ERROR_PROCESSING_COMMAND_LINE;
    }

    if (not config.load_config())
    {
		return ERROR_LOADING_CONFG_FILE;
    }

    l(lg::info, "will bing at: %s:%s [%d threads]", config.host().c_str(), config.port().c_str(), config.thread_pool_size());

	// Block all signals for background thread.
    sigset_t new_mask;
    sigfillset(&new_mask);
    sigset_t old_mask;
    pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask);	

	// Run server in background thread.
    keyper::server server(config.host(), config.port(), config.thread_pool_size());
    boost::thread main_thread(boost::bind(&keyper::server::run, &server));

	// Restore previous signals.
    pthread_sigmask(SIG_SETMASK, &old_mask, 0);

    // Wait for signal indicating time to shut down.
    sigset_t wait_mask;
    sigemptyset(&wait_mask);
    sigaddset(&wait_mask, SIGINT);
    sigaddset(&wait_mask, SIGQUIT);
    sigaddset(&wait_mask, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &wait_mask, 0);
    int sig = 0;
    sigwait(&wait_mask, &sig);

    // Stop the server.
    server.stop();
    main_thread.join();

    return 0;
}
catch (std::exception& ex)
{
	l(lg::error, "exception in main thread: %s", ex.what());
}
