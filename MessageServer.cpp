#include "MessageServer.h"
#include <iostream>


MessageServer::MessageServer():_socket(),_address()
{

}
void MessageServer::InitSocket()
{
    winSocketVersion=MAKEWORD(2,0);
    int initError=WSAStartup(winSocketVersion,&_socketData);
    if(initError!=0)
    {
        return;
    }
    else
    {
        _socket=socket(PF_INET,SOCK_DGRAM,0);
        if(_socket==INVALID_SOCKET)
        {
            ProcessError(INIT);
        }
    }
}

void MessageServer::ProcessError(ErrorTypeGroup type)
{
    std::string errorMessage="";
    int wsError = WSAGetLastError();
    switch(type)
    {
        case CLOSE:
        case INIT:
            {
                switch (wsError)
                {
                    case WSANOTINITIALISED: ///перед вызовом socket() надо успешно завершить вызов WSAStartup(), бороться с этим можно только одним способом: лечим склероз
                        errorMessage="WSA not initialised error occur\n";
                        break;
                    case WSAENETDOWN:       //- ошибка в сетевой подсистеме: проверяем, правильно ли настроено оборудование и функционирует ли оно
                        errorMessage="WSA enet down error occur\n";
                        break;
                    case WSAEAFNOSUPPORT:  // указанный домен не поддерживается (куда деваться? сидим и ждем)
                        errorMessage="WSA eaf nosupport  error occur\n";
                        break;
                    case WSAEINPROGRESS:  //выполняется блокирующий вызов winsock 1.1 (мы коснемся этой темы позже)
                        errorMessage="WSA in progress error occur\n";
                        break;
                    case WSAEMFILE:      //нет свободных дескрипторов сокетов, боремся так же как и в *nix
                        errorMessage="WSA emfile error occur\n";
                        break;
                    case WSAENOBUFS:    //нет памяти для размещения буферов, те же рекомендации
                        errorMessage="WSA enobufs error occur\n";
                        break;
                    case WSAEPROTONOSUPPORT:// указанный протокол не поддерживается, ждем известий о реализации поддержки...
                        errorMessage="WSA eprotoNoSupport error occur\n";
                        break;
                    case WSAEPROTOTYPE: //- указан протокол, не соответствующий типу сокета: перечитываем это руководство 20 раз
                        errorMessage="WSA enet down error occur\n";
                        break;
                    case WSAESOCKTNOSUPPORT: //данный тип сокета не поддерживается в указанном домене, ждем...
                        errorMessage="WSA esocket not support error occur\n";
                        break;
                    default:
                        break;
                }
            }
            break;
        case CLEANUP:
        case BIND:
            {
                switch (wsError)
                {
                    case WSANOTINITIALISED: ///перед вызовом socket() надо успешно завершить вызов WSAStartup(), бороться с этим можно только одним способом: лечим склероз
                        errorMessage="WSA not initialised error occur\n";
                        break;
                    case WSAENETDOWN:       //- ошибка в сетевой подсистеме: проверяем, правильно ли настроено оборудование и функционирует ли оно
                        errorMessage="WSA enet down error occur\n";
                        break;
                    case WSAEACCES:  // указанный домен не поддерживается (куда деваться? сидим и ждем)
                        errorMessage="WSA eaccess error occur\n";
                        break;
                    case WSAEADDRINUSE:  //выполняется блокирующий вызов winsock 1.1 (мы коснемся этой темы позже)
                        errorMessage="WSA addr in use error occur\n";
                        break;
                    case WSAEADDRNOTAVAIL:      //нет свободных дескрипторов сокетов, боремся так же как и в *nix
                        errorMessage="WSA addr not valid error occur\n";
                        break;
                    case WSAEFAULT:    //нет памяти для размещения буферов, те же рекомендации
                        errorMessage="WSA ea fault error occur\n";
                        break;
                    case WSAEINPROGRESS:// указанный протокол не поддерживается, ждем известий о реализации поддержки...
                        errorMessage="WSA einprogress error occur\n";
                        break;
                    case WSAEINVAL: //- указан протокол, не соответствующий типу сокета: перечитываем это руководство 20 раз
                        errorMessage="WSA einval error occur\n";
                        break;
                    case WSAENOBUFS: //данный тип сокета не поддерживается в указанном домене, ждем...
                        errorMessage="WSA enobufs error occur\n";
                        break;
                    case WSAENOTSOCK: //данный тип сокета не поддерживается в указанном домене, ждем...
                        errorMessage="WSA enotsock error occur\n";
                        break;
                    default:
                        break;
                }
            }
            break;
    }

    std::cout<<(
          (type==INIT)?  "Init ":
          (type==CLOSE)?"Close ":
          (type==BIND)?  "Bind ":
          (type==CLEANUP)?"Cleanup ":"Invalid")<<"error:"<<errorMessage<<std::endl;
}

void MessageServer::CloseSocket()
{
    int socketCloseError=closesocket(_socket);
    if(socketCloseError == SOCKET_ERROR)
        ProcessError(CLOSE);
}

void MessageServer::SetSocketAddress(unsigned char family, unsigned short port, const char * ip)
{
    memset(&_address,0,sizeof(sockaddr_in));//обнуление для обеспечения переносимости
    _address.sin_family=family;
    _address.sin_port=htons(port);
    _address.sin_addr.s_addr=inet_addr(ip);
}
