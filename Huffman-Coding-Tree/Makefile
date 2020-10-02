CC=g++
CXXFLAGS=-std=c++11 -g -gdwarf-3 -Wall
LDFLAGS=-g

all: compress uncompress

compress: BitInputStream.o BitOutputStream.o HCNode.o HCTree.o

uncompress: BitInputStream.o BitOutputStream.o HCNode.o HCTree.o

#compress: HCNode.o HCTree.o 

#uncompress: HCNode.o HCTree.o

HCTree.o: BitInputStream.h BitOutputStream.h HCNode.h HCTree.h

#HCTree: HCNode.h HCNode.cpp HCTree.h HCTree.cpp

test: HCNode.o HCTree.o test.cpp

#HCNode.o: HCNode.h

HCNode: HCNode.h HCNode.cpp

BitOutputStream.o: BitOutputStream.h

BitInputStream.o: BitInputStream.h

clean:
	rm -f compress uncompress *.o core*
