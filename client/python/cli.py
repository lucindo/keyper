#!/usr/bin/env python

import sys, getopt
import keyperclient

def parse_options(args):
    usage_string = "usage: %s -i <host> -p <port>" % args[0]
    ip, port = None, None

    try:
        optlist, args = getopt.getopt(args[1:], 'hi:p:')
    except getopt.GetoptError:
        exit(usage_string)

    for opt, arg in optlist:
        if opt == '-h': exit(usage_string)
        elif opt == '-i': ip = arg
        elif opt == '-p': port = int(arg)
        else: exit(usage_string)
        
    if None in (ip, port): exit(usage_string)

    return (ip, port)

def main():
    (ip, port) = parse_options(sys.argv)

    try:
        print "connecting to %s:%d" % (ip, port)

        klient = keyperclient.Client(ip, port)

        klient.ping()
        print 'ping()'

        print "server version: %s " % klient.version()

        print "get(key) = %s " % klient.get("key")

        klient.put("key", "value")
        print "put()"

        print "get(key) = %s " % klient.get("key")

    except Exception, ex:
        print '%s' % str(ex)

if __name__ == '__main__':
    main();
