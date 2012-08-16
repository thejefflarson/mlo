OBJ = src/level.o src/lm.o
CPPFLAGS ?= -I$(shell pwd)/src/ -Wall -pedantic -Werror -stdlib=libc++

all: lm

src/level.o: src/level.cpp src/level.h
src/lm.o: src/lm.cpp src/lm.h src/level.h src/status.h

lm: $(OBJ)
	c++ -stdlib=libc++ $^ -o $@

.PHONY: all
