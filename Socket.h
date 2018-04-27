#ifndef SOCKET_H
#define SOCKET_H
#pragma comment (lib, "ws2_32.lib");    // ищем нужную библиотеку
#include <winsock2.h>        // winsock2.h: typedef u_int SOCKET
#include "SocketAddress.h"
class Socket
{
    SOCKET _socketDescriptor;
public:
    static void InitializeWINSockets();
    static void CleanUpWINSockets();
    Socket(int domain=PF_INET, int socket_type=SOCK_DGRAM,int protocol=0);
    void Bind(SocketAddress &addr);
};

#endif // SOCKET_H
