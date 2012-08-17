OBJ = src/level.o src/lm.o
CPPFLAGS ?= -I$(shell pwd)/src/ -Wall -Wextra -pedantic -Werror -std=c++11 -stdlib=libc++ -O3 -ggdb

all: mlo.a

src/level.o: src/level.cpp src/level.h
src/lm.o: src/lm.cpp src/lm.h src/level.h src/status.h

mlo.a: $(OBJ)
	libtool -static -o $@ $^

test: all
	$(CXX) $(CPPFLAGS) -I$(shell pwd) -c -o test/test.o test/test.cpp
	$(CXX) $(CPPFLAGS) -o test/test test/test.o  mlo.a
	cd test && ./test && cd ..

.PHONY: all test
