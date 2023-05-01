//#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/time.h>
#include <time.h>

#define PORT 51717
#define MAX_CLIENTS 5
#define SIZE 1024

class Server
{
    static Server *instance;
    Server(){};
    Server(const Server &){};
    ~Server(){};

    sockaddr_in serv_addr;
    sockaddr_in cli_addr;
    socklen_t clilen;
    static struct pollfd pollfds[MAX_CLIENTS + 1];
    
    static int nrCl;
    static int shut_down;
    int sockfd;
    int ClientSocket;
    int newsockfd;

    
    
public:
    static int startTime;
    static Server &getInstance();
    static void destroyInstance();
    void StartServer();
    static void CloseServer(int);
    static void sendMessage(std:: string msg, int);
};