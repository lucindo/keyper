#!/usr/bin/env python

import sys, getopt
sys.path.append("../../thrift/gen-py")

from keyper import Keyper
from keyper.ttypes import *

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

class Item(item):
    def __init__(self):
        item.__init__(self)

class Client(Keyper.Client):
    def __init__(self, ip, port):
        transport = TSocket.TSocket(ip, port)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocol(transport)
        Keyper.Client.__init__(self, protocol)
        transport.open()

    def cincr(self, name, delta = 1):
        return Keyper.Client.cincr(self, name, delta)

    def cdecr(self, name, delta = 1):
        return Keyper.Client.cdecr(self, name, delta)
