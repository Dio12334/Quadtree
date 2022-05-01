objects = main.o Display.o Quadtree.o Point.o AABB.o 
CFLAGS = -Wall -O2 
LINKERFLAGS = -lSDL2 -lSDL2_image
debugflags = -g
CC = g++
execname = a.out

ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += $(debugflags)
endif

all: build

debug: clean build

build: $(objects)
	$(CC) $(CFLAGS) -o $(execname) $(objects) $(LINKERFLAGS) 

%.o : %.cpp
	$(CC) -c $(CFLAGS) $(LINKERFLAGS) $< -o $@

.PHONY: clean cleanall
clean:
	rm -f $(objects)

cleanall: clean
	rm -f $(execname)


