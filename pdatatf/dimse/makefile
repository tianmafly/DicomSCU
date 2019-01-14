all: dimse.o dimserq.o dimsersp.o

dimse.o: dimse.h dimse.cpp
	g++ -c -g dimse.cpp
dimserq.o: dimserq.h dimserq.cpp
	g++ -c -g dimserq.cpp
dimsersp.o: dimsersp.h dimsersp.cpp
	g++ -c -g dimsersp.cpp
clean:
	rm *.o