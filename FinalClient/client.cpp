#include "Client.h"
Client::Client(std::string ip, int PORT)
{
  WSAData wsad;
  WORD ver = MAKEWORD(2,2);
  int WsOk = WSAStartup(ver,&wsad);

  int sizeofaddr = sizeof(addr);
  addr.sin_addr.s_addr = inet_addr(ip.c_str());
  addr.sin_port = htons(PORT);
  addr.sin_family = AF_INET;
  clientPtr = this;

}
void Client::ClientInputThread()
{
    //int retncheck;
    while(true)
    {
      Packet packetType;
      //retncheck = recv(clientPtr->toServer,(char*)&packetType,sizeof(Packet),NULL);
       if(clientPtr->recvPacket(packetType)) clientPtr->ProcessPacket(packetType);
     //if(retncheck!=0&&retncheck!=INVALID_SOCKET) clientPtr->ProcessPacket(packetType);
    }

}

bool Client::Connect()
{
    std::string username = " ";
    std::cout<<"Enter a username: ";
    std::cin>>username;
    toServer = socket(AF_INET,SOCK_STREAM,NULL);
    std::string test;
    int sizeofaddr = sizeof(addr);
    if(connect(toServer,(sockaddr*)&addr,sizeofaddr)!=0)
    {
        std::cout<<"Error connecting to the server\n";
        std::cout<<"Enter any key to continue.";
        std::cin>>test;
        return false;
    }

    if(toServer!=INVALID_SOCKET)
    {
        int len = username.length();
        send(toServer,(char*)&len,4,NULL);
        send(toServer,username.c_str(),username.length(),NULL);
        CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ClientInputThread,NULL,NULL,NULL);
    }
    return true;
}
bool Client::ProcessPacket(Packet packetType)
{

    switch(packetType)
   {
     case P_ChatMessage:
     {
        std::string buffer = "";
        recvString(buffer);
        std::cout<<buffer<<"\n";

       break;
      }
     case P_FileTransferRequestFile:
     {
        int32_t buffersize;
        if(!recvInt(buffersize))
            return false;
        if(!recvAll(file.buffer,buffersize))
            return false;
        file.outFileStream.write(file.buffer,buffersize);
        file.bytesWritten += buffersize;
        sendPacket(P_FileTransferRequestFile);
       break;
     }
     case P_FileTransferByteBuffer:
    {
        int32_t buffersize=0;
        recvInt(buffersize);
        recvAll(file.buffer,buffersize);
        file.outFileStream.write(file.buffer,buffersize);
        file.bytesWritten += buffersize;
        std::cout<<"Byte buffer recieved of size: "<<buffersize<<std::endl;
        sendPacket(P_FileTransferByteBuffer);
        break;
    }
     case P_FileTransferEndOfFile:
    {
        std::cout<<"File transfer completed. File received."<<std::endl;
        std::cout<<"File Name: "<< file.fileName <<std::endl;
        std::cout<<"File Size(bytes)"<<file.bytesWritten<<std::endl;
        file.bytesWritten = 0;
        file.outFileStream.close();
        break;
    }
     default:
     std::cout<<"An unknown packet has been recieved.\n";
     break;
   }
     return true;
}
bool Client::requestFile(std::string fileName)
{
    file.outFileStream.open(fileName,std::ios::binary|std::ios::ate);
    file.fileName = fileName;
    if(!file.outFileStream.is_open())
        std::cout<<"Error: Unable to open file."<<std::endl;
    if(!sendPacket(P_FileTransferRequestFile))
        return false;
    if(!sendString(fileName,false))
        return true;
}
