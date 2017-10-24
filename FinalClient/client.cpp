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

}

bool Client::Connect()
{
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
       QString buffer = "";
       int bufferLength = 0;
       recv(toServer,(char*)&bufferLength,sizeof(int),NULL);
       char * _buffer = new char[bufferLength+1];
       _buffer[bufferLength] = '\0';
       recv(toServer,_buffer,bufferLength,NULL);
       buffer = _buffer;
       window->writeToServerArea("Message Recvd: ");
       window->writeToServerArea(buffer);
	   CreateThread(NULL,NULL,NULL,(LP_THREAD_ROUTINE)ClientInputThread,NULL,NULL);
    }
    return true;
}

void Client::bindWindow(MainWindow *window)
{
    this->window = window;
}
void Client::Input()
{
	while(true)
	{
		//Take Input from UI and store it in std::string message;
		
		std::string message;
		int len = message.length();
		send(toServer,(char*)&len,4,NULL);
		send(toServer,message.c_str(),len,0);
		
	}
}
void Client::ClientInputThread()
{
	int len = 0;
	while(true)
    {
	   	int recvCheck = recv(toServer,(char*)&len,4,NULL);
		if(recvCheck != SOCKET_ERROR&&recvCheck!=0)
		{
			char * message = new char[len+1];
			message[len] = '\0';
			recvCheck = recv(toServer,message,len,NULLL);
			window->writeToServerArea(message);
			delete [] message;
		}
	}
}