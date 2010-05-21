$:.push('../../thrift/gen-rb')

require 'thrift'
require 'keyper'

class KeyperClient < Keyper.Client
  def initialize(ip, port)
    transport = Thrift::BufferedTransport.new(Thrift::Socket.new(ip, port))
    protocol = Thrift::BinaryProtocol.new(transport)
    super(protocol)

    transport.open()
  end
end
