// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#include "request_handler.hh"
#include "reply.hh"
#include "request.hh"
#include "log.hh"

namespace keyper
{

    request_handler::request_handler()
    {
    }

    void request_handler::handle_request(const request& req, reply& rep)
    {
		l(lg::debug, "handling request with line = [%s]", req.line.c_str());
		rep.buffer = "oie..";
    }

} // namespace keyper
