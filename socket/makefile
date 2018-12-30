main:socket.o main.cpp
	g++ -g main.cpp socket.o -o main
socket.o: socket.h socket.cpp
	g++ -g -c socket.cpp
clean:
	rm *.o