#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <string>
using namespace std;

class TcpSocket
{
public:
    TcpSocket();
    ~TcpSocket();
public:
    void OpenSocket(int Port);
    int Accept();
    int Connet(string IP, int Port);
    void Send(int conn, const char* buff, int len);
    void Reveive(int conn, char* buff);
private:
    int mainsocket;
};

#endif