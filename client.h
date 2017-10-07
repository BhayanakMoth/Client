#ifndef CLIENT_H
#define CLIENT_H
#include<winsock2.h>
#include<iostream>
#include<string>
#include<ws2tcpip.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class Client
{
private:
    enum Packet
    {
        P_ChatMessage,
        P_Ping,
    };
public:
  Client(std::string ip, int PORT);
  bool Connect();
  void bindWindow(MainWindow *window);
private:
  static void ClientInputThread();
  bool ProcessPacket(Packet packetType);
private:
  SOCKET toServer;
  SOCKADDR_IN addr;
  MainWindow * window;
};

#endif // CLIENT_H
