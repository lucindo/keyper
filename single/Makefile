CPPFLAGS = -Wall -ansi -pedantic-errors -std=c++0x -I/usr/local/include 
ifeq ($(DEB),0)
  CPPFLAGS += -O2
else
ifeq ($(DEB),)
  CPPFLAGS += -O2
else
  CPPFLAGS += -g3 -DDEBUG=$(DEB)
endif
endif
LIB = -L/usr/local/lib -lkyotocabinet -lz -lstdc++ -lrt -lpthread -lm -lc
BIN = keypers
CXX = g++

cpps :=  $(wildcard *.cc)
objects := $(foreach file, $(cpps), $(basename $(file)).o)

all: $(BIN)

obj: $(objects)

$(BIN): $(objects)
	$(CXX) $(CPPFLAGS) -o $(BIN) $(objects) $(LIB)

$(objects): %.o: %.cc %.hh
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean cleanbin realclean 
realclean: cleanbin clean

cleanbin:
	-rm -f $(BIN)
clean:
	-rm -f *~ $(objects)
