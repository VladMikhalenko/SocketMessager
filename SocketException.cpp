#include "SocketException.h"
#include <iostream>
SocketException::SocketException(const char * error_message)
{
    error_code=GetLastError();
    description=std::string(error_message);
}

void SocketException::Print() const
{
    std::cout<<"ERROR: '"<<description<<"'/tCode:"<<error_code<<std::endl;
}
