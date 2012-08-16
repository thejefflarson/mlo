OBJ = src/lm.o src/level.o

all: $(OBJ)

src/level.o: src/level.cpp src/level.h
src/lm.o: src/lm.cpp src/lm.h src/level.h src/status.h
lm: src/lm.o

.PHONY: all
