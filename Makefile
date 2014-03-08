proj1: main.o
	g++ -o proj1 main.o
main.o: main.cpp
	g++ -c main.cpp
