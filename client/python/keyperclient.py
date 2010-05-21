#!/usr/bin/env python

import sys, getopt
sys.path.append("../../thrift/gen-py")

from keyper import Keyper
from keyper.ttypes import *

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

class Client(Keyper.Client):
    def __init__(self, ip, port):
        transport = TSocket.TSocket(ip, port)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocol(transport)
        Keyper.Client.__init__(self, protocol)
        transport.open()
