.cpp.o:	$*.h
	g++	-Wall -c $*.cpp

all:	dominoes 

dominoes:	dominoes.o tadTile.o tadGame.o
	g++ -o $@ $^


clean:
	rm *.o dominoes 