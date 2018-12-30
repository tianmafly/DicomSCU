#include "socket.h"
#include <string.h>


int main()
{
    char * buff = new char[20];
    char *sendbuff = "hehe!";

    memset(buff, 0, sizeof(buff));
    TcpSocket socket_scp = TcpSocket();
    socket_scp.OpenSocket(4100);
    int conn = socket_scp.Accept();
    socket_scp.Reveive(conn, buff);
    socket_scp.Send(conn, sendbuff);
    int b = 312;
    
}