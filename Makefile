all:
	@cd thrift && $(MAKE)
	@cd single && cmake . && $(MAKE)
