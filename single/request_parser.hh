// Copyright (c) 2010 R. Lucindo (lucindo@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See file LICENSE_1_0.txt or http://boost.org/LICENSE_1_0.txt)

#ifndef REQUEST_PARSER_HH
#define REQUEST_PARSER_HH

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

namespace keyper
{

    struct request;
	
    class request_parser
    {
    public:
        request_parser();

        /// Parse some data. The tribool return value is true when a complete request
        /// has been parsed, false if the data is invalid, indeterminate when more
        /// data is required. The InputIterator return value indicates how much of the
        /// input has been consumed.
        template <typename InputIterator>
        boost::tuple<boost::tribool, InputIterator> parse(request& req,
                                                          InputIterator begin, InputIterator end)
        {
            while (begin != end)
            {
                boost::tribool result = consume(req, *begin++);
                if (result || !result)
                    return boost::make_tuple(result, begin);
            }
            boost::tribool result = boost::indeterminate;
            return boost::make_tuple(result, begin);
        }

    private:
        /// Handle the next character of input.
        boost::tribool consume(request& req, char input);

        /// Check if a byte is an HTTP control character.
        static bool is_ctl(int c);
    };

} // keyper

#endif // REQUEST_PARSER_HH
