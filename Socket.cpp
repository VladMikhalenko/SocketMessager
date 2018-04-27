#include "Socket.h"
#include "SocketException.h"
Socket::Socket(int domain, int socket_type, int protocol)
{
    _socketDescriptor=socket(doamin,type,protocol);
    if(_socketDescriptor==SOCKET_ERROR)
        throw SocketException("Socket - failed to create a socket");
}

Socket::Bind(SocketAddress &addr)
{
    int result=bind(_socketDescriptor,reinterpret_cast<sockaddr*>(addr.getAddress()),sizeof(sockaddr_in));
    if(result==SOCKET_ERROR)
        throw SocketException("Socket - failed to bind socket with provided address");
}

void Socket::InitializeWINSockets()
{
    WORD winsock_version = MAKEWORD (2,0);
    WSADATA winsock_data;
    int error = WSAStartup (winsock_version, &winsock_data);	// непосредственно инициализци¤
    if (error != 0)
        throw SocketException("WIN Sock Initialization - could not initialize winsock");
}
void Socket::CleanUpWINSockets()
{
    int error = WSACleanup();
    if (error == SOCKET_ERROR)
        throw _sock_exception ("WIN Sock CleanUp - could not perform cleaning up");
}
