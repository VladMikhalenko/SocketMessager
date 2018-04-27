#ifndef MESASGESERVER_H
#define MESASGESERVER_H

#pragma comment (lib, "ws2_32.lib");    // ищем нужную библиотеку
#include <winsock2.h>        // winsock2.h: typedef u_int SOCKET
#include <string>
class MessageServer
{
    WORD winSocketVersion;
    WSAData _socketData;
    SOCKET _socket;

    bool InitSocket();
    bool ProcessError(SOCKET sock,std::string what);
    bool CloseSocket();
public:
    MessageServer();
};

#endif // MESASGESERVER_H
