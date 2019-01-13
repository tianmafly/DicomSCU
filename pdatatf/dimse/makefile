all: dimse.o dimserq.o

dimse.o: dimse.h dimse.cpp
	g++ -c -g dimse.cpp
dimserq.o: dimserq.h dimserq.cpp
	g++ -c -g dimserq.cpp
clean:
	rm *.o