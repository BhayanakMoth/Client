#include "Client.h"
bool Client::sendAll(char * data, int totalBytes)
{
    int bytesSent = 0;
    while(bytesSent<totalBytes)
    {
        int retnCheck = send(toServer,data+bytesSent,totalBytes-bytesSent,NULL);
        if(retnCheck==SOCKET_ERROR)
            return false;
        bytesSent+= retnCheck;
    }
    return true;
}
bool Client::recvAll(char * data, int totalBytes)
{
    int bytesRecvd = 0;
    while(bytesRecvd<totalBytes)
    {
        int retnCheck = recv(toServer,data+bytesRecvd,totalBytes-bytesRecvd,NULL);
        if(retnCheck==SOCKET_ERROR&&retnCheck == 0)
            return false;
        bytesRecvd+= retnCheck;
    }
    return true;
}
bool Client::sendInt(int32_t _int32_t)
{
    _int32_t = htonl(_int32_t);
   if(!sendAll((char*)&_int32_t,sizeof(int32_t)))
       return false;
   return true;
}

bool Client::recvInt(int32_t &_int32_t)
{

  //recv(toServer,(char*)&_int,sizeof(int),NULL);
   if(!recvAll((char*)&_int32_t,sizeof(int32_t)))
      return false;
   _int32_t = ntohl(_int32_t);
   return true;
}
bool Client::sendPacket(Packet packetType)
{
    if(!sendAll((char*)&packetType,sizeof(Packet)))
       return false;
    return true;
}
bool Client::recvPacket(Packet &packetType)
{
   // int retnCheck = recv(toServer,(char*)&packetType,sizeof(Packet),NULL);
    if(!recvAll((char*)&packetType,sizeof(Packet)))
        return false;
    return true;
}
bool Client::sendString(std::string str,bool isMessage)
{
    if(isMessage == true)
    {
    Packet _packet = P_ChatMessage;
    send(toServer,(char*)&_packet,sizeof(Packet),NULL);
    }
    int bufferLength = str.length();
    send(toServer,(char*)&bufferLength,sizeof(int),NULL);
    int retnCheck = send(toServer,str.c_str(),bufferLength,NULL);
    if(retnCheck == SOCKET_ERROR)
        return false;
    return true;
}
bool Client::recvString(std::string &str)
{
    int bufferLength =0;
    if(!recvInt(bufferLength))
        return false;
    char * buffer= new char[bufferLength+1];
    buffer[bufferLength]='\0';
    int retnCheck = recv(toServer,buffer,bufferLength,NULL);
    if(retnCheck == SOCKET_ERROR)
        return false;
    str = buffer;
    return true;
}
