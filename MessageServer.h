#pragma comment (lib, "ws2_32.lib");    // ищем нужную библиотеку
#include <winsock2.h>        // winsock2.h: typedef u_int SOCKET
#ifndef MESASGESERVER_H
#define MESASGESERVER_H
#include "Socket.h"
#include "SocketAddress.h"
#include <string>
#define PORT 2808

class MessageServer
{
    Socket _socket;
    SocketAddress _address;
public:
    MessageServer();
    void InitSocket();
    void CloseSocket();
    //int  Send(Socket _sock,std::string msg,)
    void SetSocketAddress(unsigned char family=AF_INET, unsigned short port=PORT, const char *ip ="127.0.0.1");
};

#endif // MESASGESERVER_H
