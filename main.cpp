#include <QApplication>
#include "client.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client("127.0.0.1",1111);
    client.Connect();
    return a.exec();
}
