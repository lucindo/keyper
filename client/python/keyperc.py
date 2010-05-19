#!/usr/bin/env python

import sys, getopt
sys.path.append("../../thrift/gen-py")

from keyper import Keyper
from keyper.ttypes import *

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

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
        transport = TSocket.TSocket(ip, port)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocol(transport)

        client = Keyper.Client(protocol)

        print "connecting to %s:%d" % (ip, port)
        transport.open()

        client.ping()
        print 'ping()'

    except Thrift.TException, tx:
        print '%s' % (tx.message)


if __name__ == '__main__':
    main()
