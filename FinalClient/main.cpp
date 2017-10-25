#include <QCoreApplication>
#include "client.h"
int main()
{
   std::string ip = "127.0.0.1";
   int port = 1111;

   Client chatter(ip,port);


   if(!chatter.Connect())
   {
       std::cout<<"Chatter is DEAD!"<<std::endl;
       return -1;
   }

   std::string buffer="";
   while(true)
   {
     std::getline(std::cin,buffer);
     chatter.sendString(buffer,true);
  }
  return 0;
}


