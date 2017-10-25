#ifndef CLIENT_H
#define CLIENT_H
#include<winsock2.h>
#include<iostream>
#include<string>
#include<ws2tcpip.h>
#include "filetransferdata.h"
class Client
{
private:
    enum Packet
    {
        P_ChatMessage,
        P_Ping,
        P_FileTransferRequestFile,
        P_FileTransferEndOfFile,
        P_FileTransferByteBuffer,
        P_FileTransferRequestNextBuffer
    };
public:
  Client(std::string ip, int PORT);
  bool Connect();
  bool sendString(std::string _str,bool isMessage = false);
  bool requestFile(std::string fileName);
private:
  bool sendInt(int32_t _int32_t);
  bool sendPacket(Packet _packetType);
  bool sendAll(char* data, int sizeofdata);
  bool recvAll(char* data, int sizeofdata);
  bool recvInt(int32_t & _int32_t);
  bool recvPacket(Packet &packetType);
  bool recvString(std::string& _str);
  static void ClientInputThread();
  bool ProcessPacket(Packet packetType);
private:

  FileTransferData file;
  SOCKET toServer;
  int port = 1111;
  std::string ip = "127.0.0.1";
  SOCKADDR_IN addr;
};
static Client * clientPtr;
#endif // CLIENT_H
