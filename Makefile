all:
	@cd thrift && $(MAKE)
	@cd server && cmake . && $(MAKE)
