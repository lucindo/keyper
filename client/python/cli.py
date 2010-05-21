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
        print "put(key, value)"

        print "get(key) = %s " % klient.get("key")

        print "# keys = %d " % klient.size()

        print "exists a_chave = %s" % klient.exists("a_chave")

        klient.put("a_chave", "o_valor")
        print "put(a_chave, o_valor)"
        
        print "exists a_chave = %s" % klient.exists("a_chave")

        klient.remove("a_chave")
        print "remove(a_chave)"

        print "exists a_chave = %s" % klient.exists("a_chave")

        klient.put("chave1", "42")
        print "put(chave1, 42)"

        klient.rename("chave1", "xuxu")
        print "rename(chave1, xuxu)"
        
        print "exists chave1 = %s" % klient.exists("chave1")

        print "exists xuxu = %s" % klient.exists("xuxu")

        print "get(xuxu) = %s " % klient.get("xuxu")

        print "counter exists? %s" % klient.cexists("counter")

        klient.cincr("counter", 1)
        print "cincr(counter, 1)"

        print "counter exists? %s" % klient.cexists("counter")

        print "counter %d" % klient.cget("counter")

        klient.cdecr("counter", 1)
        print "cdecr(counter, 1)"

        print "counter %d" % klient.cget("counter")

        klient.cremove("counter")
        print "cremove(counter)"

        print "counter exists? %s" % klient.cexists("counter")

    except Exception, ex:
        print '%s' % str(ex)

if __name__ == '__main__':
    main();
