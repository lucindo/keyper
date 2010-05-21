// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include <kchashdb.h>

#include "keypers.hh"
#include "config.hh"
#include "log.hh"
#include "handler.hh"
#include "storage.hh"
#include "counter.hh"

#include <concurrency/ThreadManager.h>
#include <concurrency/PosixThreadFactory.h>
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <server/TThreadPoolServer.h>
#include <server/TThreadedServer.h>
#include <transport/TServerSocket.h>
#include <transport/TTransportUtils.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace apache::thrift::concurrency;
using namespace boost;
using namespace keyper;

int main(int argc, char** argv) try
{
    Config config;

    if (not config.command_line(argc, argv))
    {
        config.usage(argv[0]);
        return ERROR_PROCESSING_COMMAND_LINE;
    }

    l(lg::debug, "will bing at: %s:%d [%d threads] [data dir %s]", config.host().c_str(), config.port(), config.thread_pool_size(), config.data_dir().c_str());

    if (not KVStore::instance().init(config.data_dir()))
    {
        l(lg::critical, "error opening database, aborting.");
        return ERROR_OPENNING_DATABASE;
    }

    if (not Counter::instance().init(config.data_dir()))
    {
        l(lg::critical, "error opening counter, aborting.");
        return ERROR_OPENNING_DATABASE;
    }

    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    shared_ptr<KeyperHandler> handler(new KeyperHandler());
    shared_ptr<TProcessor> processor(new KeyperProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(config.port()));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());

    shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(config.thread_pool_size());
    shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();

    TThreadPoolServer server(processor,
                             serverTransport,
                             transportFactory,
                             protocolFactory,
                             threadManager);

    l(lg::info, "starting the server");

    server.serve();

    KVStore::instance().fini();

    Counter::instance().fini();

    l(lg::info, "exiting");

    return 0;
}
catch (std::exception& ex)
{
    l(lg::error, "exception in main thread: %s", ex.what());
}
