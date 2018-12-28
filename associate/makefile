main: main.cpp associate.o
	g++ -g main.cpp associate.o -o main
associate.o: associate.h associate.cpp associaterq.o
	g++ -g -c associate.cpp
associaterq.o: associaterq.h associaterq.cpp
	g++ -g -c associaterq.cpp
