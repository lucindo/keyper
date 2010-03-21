all:
	@cd single && $(MAKE) $(@)
	@cd distributed && $(MAKE) $(@)

clean:
	@cd single && $(MAKE) clean $(@)
	@cd distributed && $(MAKE) clean $(@)
