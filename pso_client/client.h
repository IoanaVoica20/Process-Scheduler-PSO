#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <stdlib.h>


#define PORT 51717
#define SIZE 1024

class Conectare_Srv
{
	static int nRet;

	static struct sockaddr_in server_addr;
	//static int indexMeniu;

	Conectare_Srv() noexcept { ; }
	Conectare_Srv(Conectare_Srv& other) noexcept { ; }
	Conectare_Srv(Conectare_Srv&& other) noexcept { ; }
public:
	static int ClientSocket;
	static void Connect();
	static std::string Recvs();
	static void SendToServer(std::string msg);
	
};