#include "server.h"
#include "utile/interpreter.h"
#include "utile/lib_parce.h"

Server *Server::instance = nullptr;
int Server::nrCl = 0;
pollfd Server::pollfds[MAX_CLIENTS +1] = {0}; 
int Server::shut_down = 0;
int Server::startTime = 0;

Server &Server::getInstance()
{
    if (!Server::instance)
    {
        Server::instance = new Server();
    }
    return *Server::instance;
}

void Server::destroyInstance()
{
    if (Server::instance)
    {
        delete Server::instance;
        Server::instance = nullptr;
    }
}

void Server::sendMessage(std:: string msg, int clSock)
{
    write(clSock, msg.c_str(), msg.size());
} 

void Server::StartServer()
{
    time_t t = time(0);
    struct tm *sTime = localtime(&t);
    std::cout<<"Server start time "<<sTime->tm_min<<":"<<sTime->tm_sec<<"\n";
    startTime = sTime->tm_sec;
    startTime += sTime->tm_min*60;
    startTime += sTime->tm_hour*3600;

    int nRet = 0, pid;
    Server::shut_down = 0;
    std::cout << "***********Server ON***********\n\n";
    // initializare soket

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        perror("ERROR opening socket");
    // else
    //	std::cout << "Deschis cu succes..\n";

    // initialize the enviroment for sockarddr structure

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // colecteaza adresa ip => nu trebuie sa o introducem


    // Bind the socket to the local port
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        perror("ERROR on binding");
    else
        std::cout << "Successfully to bind to local port\n";

    // Listen the request from client (queques the request)
    nRet = listen(sockfd, 5);
    if (nRet < 0)
    {
        std::cout << "Fail to start listen to local port";
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "Started listening to local port\n";
    
    pollfds[0].fd = sockfd;
    pollfds[0].events = POLLIN | POLLPRI;
    //int useClient = 0;

    nrCl = 0;
    while (Server::shut_down == 0)
    {
        int pollResult = poll(pollfds, nrCl + 1, 5000);
        if(pollResult > 0)
        {
            if(pollfds[0].revents & POLLIN)
            {
                clilen = sizeof(cli_addr);
                ClientSocket = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
                //printf("accept success %s\n", inet_ntoa(cli_addr.sin_addr));
                
                printf("accept succes\n");
                sendMessage("Hello client!",ClientSocket);
                for (int i = 1; i < MAX_CLIENTS; i++)
                {
                    if (pollfds[i].fd == 0)
                    {

                        pollfds[i].fd = ClientSocket;
                        pollfds[i].events = POLLIN | POLLPRI;
                        nrCl++;
                        break;
                    }
                }
            }
            for (int i = 1; i < MAX_CLIENTS; i++)
            {
                if (pollfds[i].fd > 0 && pollfds[i].revents & POLLIN)
                {
                    char buf[SIZE];
                    int bufSize = read(pollfds[i].fd, buf, SIZE - 1);
                    if (bufSize == -1)
                    {
                        pollfds[i].fd = 0;
                        pollfds[i].events = 0;
                        pollfds[i].revents = 0;
                        nrCl--;
                    }
                    else if (bufSize == 0)
                    {
                        pollfds[i].fd = 0;
                        pollfds[i].events = 0;
                        pollfds[i].revents = 0;
                        nrCl--;
                    }
                    else
                    {

                        buf[bufSize] = '\0';
                        if(strcmp(buf,"HELLO SERVER")!= 0)
                            interpreter::interpret_msg(parce_msg(buf),pollfds[i].fd);
                        
                    }
                }
            }
        }
    }
}

void Server::CloseServer(int clSock)
{
    for (int i = 1; i < MAX_CLIENTS; i++)
        if(pollfds[i].fd == clSock)
        {
            pollfds[i].fd = 0;
            pollfds[i].events = 0;
            pollfds[i].revents = 0;
            std::cout<<"***********Client "<<i<<" lost***********\n";
        }
   
    nrCl--;
       
        
}