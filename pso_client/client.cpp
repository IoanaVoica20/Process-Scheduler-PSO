#define _CRT_SECURE_NO_WARNINGS
#include "client.h"
#include <string.h>

int Conectare_Srv::nRet = 0;
int Conectare_Srv::ClientSocket = 0;
struct sockaddr_in Conectare_Srv::server_addr;

void Conectare_Srv::Connect()
{
	ClientSocket = socket(AF_INET, SOCK_STREAM, 0);

    //struct sockaddr_in addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("192.168.26.128");
	memset(&server_addr.sin_zero, 0, 8);
   // inet_aton(hostArgv, &(addr.sin_addr));

    int server_socket = connect(ClientSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)); //连接服务器

    printf("Connect result ==> %d\n", server_socket);
    if (server_socket < 0) {
        perror("Connect result");
        exit(1);
    }
	else
	{
		
		SendToServer("HELLO SERVER");
		std::cout<<Conectare_Srv::Recvs()<<std::endl;
	}
    
}

void Conectare_Srv::SendToServer(std::string msg)
{
	const char* m = msg.c_str();
	write(ClientSocket, m, strlen(m));
}

std::string Conectare_Srv::Recvs()
{
	char buff1[SIZE];
	int bufSize = read(ClientSocket, buff1, SIZE - 1);
	buff1[bufSize] = '\0';
	std::string a(buff1);

	return a;
}

