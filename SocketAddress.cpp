#include "SocketAddress.h"
#include "SocketException.h"
SocketAddress::SocketAddress():_socketAddress()
{
    _socketAddress.sin_family = AF_INET;
    _socketAddress.sin_addr.s_addr = INADDR_ANY;
    _socketAddress.sin_port=0;
}

SocketAddress::SocketAddress(unsigned short port):_socketAddress()
{
    _socketAddress.sin_family = AF_INET;
    _socketAddress.sin_addr.s_addr = INADDR_ANY;
    _socketAddress.sin_port=port;
}
SocketAddress::SocketAddress(const char *ip,unsigned short port)
{
    _socketAddress.sin_family = AF_INET;
    _socketAddress.sin_addr.s_addr = inet_addr(ip);
    _socketAddress.sin_port=port;
    if(_socketAddress.sin_addr.s_addr==INADDR_NONE)
    {
        throw SocketException("SocketAddress - invalid ip value");
    }
    _socketAddress.sin_port=htons(port);
}

sockaddr_in &SocketAddress::GetSocketAddress() const
{
    return _socketAddress;
}

char * SocketAddress::GetIP() const
{
    return inet_ntoa(_socketAddress.sin_addr);
}

unsigned short SocketAddress::getPort() const
{
    return ntohs(_socketAddress.sin_port);
}
