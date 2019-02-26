#Makefile

prog2: splayTree.o prog2.o
	g++ -g -std=c++11 -o $@ $^

prog2.o: prog2.cpp 
	g++ -g -std=c++11 -c prog2.cpp

splayTree.o: splayTree.h splayTree.cpp
	g++ -g -std=c++11 -c splayTree.cpp

clean:
	rm *.o prog2
