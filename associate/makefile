main: main.cpp associate.o
	g++ -g main.cpp associate.o associaterq.o associateac.o ../dul/dulassociaterq.o ../dul/dulassociateac.o ../socket/socket.o ../dimse/dimse.o ../dimse/cfind/cfindrq.o ../pdatatf/pdatatf.o -o main
associate.o: associate.h associate.cpp associaterq.o associateac.o
	g++ -g -c associate.cpp
associaterq.o: associaterq.h associaterq.cpp 
	g++ -g -c associaterq.cpp -o associaterq.o
associateac.o: associateac.h associateac.cpp 
	g++ -g -c associateac.cpp -o associateac.o
clean:
	rm main *.o
