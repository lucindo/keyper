// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef REQUEST_HANDLER_HH
#define REQUEST_HANDLER_HH

#include <string>
#include <boost/noncopyable.hpp>

namespace keyper
{
    struct reply;
    struct request;

    class request_handler : private boost::noncopyable
    {
    public:
        explicit request_handler();

        /// Handle a request and produce a reply.
        void handle_request(const request& req, reply& rep);
    };

} // keyper

#endif // REQUEST_HANDLER_HH
