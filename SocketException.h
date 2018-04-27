#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H
#pragma comment (lib, "ws2_32.lib");    // ищем нужную библиотеку
#include <winsock2.h>        // winsock2.h: typedef u_int SOCKET
#include <string>
class SocketException
{
protected:
    int error_code;
    std::string description;
public:
    SocketException(const char* error_message);

    void Print() const;
    int  GetErrorCode();
};

#endif // SOCKETEXCEPTION_H
