#ifndef SOCKETADDRESS_H
#define SOCKETADDRESS_H
#pragma comment (lib, "ws2_32.lib");    // ищем нужную библиотеку
#include <winsock2.h>        // winsock2.h: typedef u_int SOCKET

class SocketAddress
{
    sockaddr_in _socketAddress;
public:
    SocketAddress();
    SocketAddress(unsigned short port);
    SocketAddress(const char* ip, unsigned short port);
};

#endif // SOCKETADDRESS_H
