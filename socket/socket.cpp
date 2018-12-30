#include "socket.h"
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>



TcpSocket::TcpSocket()
{
    this->mainsocket = 0;
}

TcpSocket::~TcpSocket()
{

}

void TcpSocket::OpenSocket(int Port)
{
    int backlog = 5;
    this->mainsocket = socket(AF_INET, SOCK_STREAM, 0);
    //printf("%d\n",ss);
    sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(Port);
    //printf("%d\n",INADDR_ANY);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(this->mainsocket, (struct sockaddr* ) &server_sockaddr, sizeof(server_sockaddr))==-1) {
        perror("bind");
        return;
    }
    if(listen(this->mainsocket, backlog) == -1) {
        perror("listen");
        return;
    }
}

int TcpSocket::Accept()
{
    sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    ///成功返回非负描述字，出错返回-1
    int conn = accept(this->mainsocket, (struct sockaddr*)&client_addr, &length);
    if( conn < 0 ) {
        perror("Accept");
        return 0;
    }
    
    return conn;
}
int TcpSocket::Connet(string IP, int Port)
{
    ///定义sockfd
    int socketfd = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(Port);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr(IP.c_str());  ///服务器ip
    int conn = connect(socketfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (conn < 0)
    {
        perror("Connet");
        return 0;
    }

    return socketfd;
}

void TcpSocket::Send(int socketfd, const char* buff, int len)
{
    int retlen = send(socketfd, buff,  len, 0);
    if(retlen != len)
    {
        perror("Send");
        return;
    }

}

void TcpSocket::Reveive(int conn, char* buff)
{
    int buflen = sizeof(buff);
    int retlen = recv(conn, buff, buflen, 0);
    if(retlen != buflen)
    {
        perror("Reveive");
        return;
    }
}