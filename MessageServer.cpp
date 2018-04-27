#include "MessageServer.h"
#include <iostream>
MessageServer::MessageServer()
{

}
bool MessageServer::InitSocket()
{
    winSocketVersion=MAKEWORD(2,0);
    int initError=WSAStartup(winSocketVersion,&_socketData);
    if(initError!=0)
    {
        return false;
    }
    else
    {
        _socket=socket(PF_INET,SOCK_DGRAM,0);
        std::string error="";
        if(_socket==INVALID_SOCKET)
        {
            ProcessError(error);
            std::cout<<"Socket creation failed:"<<error<<std::endl;
            return false;
        }
        return true;
    }
}

void MessageServer::ProcessError(std::string &what)
{
    std::string errorMessage="";
    int wsError = WSAGetLastError();
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
    what=errorMessage;
}


bool MessageServer::CloseSocket()
{
    int socketCloseError=closesocket(_socket);
    std::string what="";
    if(socketCloseError == SOCKET_ERROR)
        ProcessError(what);
    socketCloseError = WSACleanup ();
    if (socketCloseError == SOCKET_ERROR)
        ProcessError(what);
}
