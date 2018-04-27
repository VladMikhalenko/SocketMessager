//#include "MainWindow.h"
//#include <QApplication>
#include "MessageServer.h"
#include "Socket.h"
int main(int argc, char *argv[])
{
    Socket::InitializeWINSockets();




    Socket::CleanUpWINSockets();

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
