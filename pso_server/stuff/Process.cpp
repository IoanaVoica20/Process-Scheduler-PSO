#include <iostream>
#include <vector>
#include "Process.h"
#include "Memory.h"
#include "../server.h"
#include "../utile/Protocol.h"

int Process::pid_gen = 0;

Process::Process(std::vector<std::string> p)
{
    this->alg = std::stoi(p[0]);
    this->pid = ++pid_gen;
    this->p_size = std::stoi(p[1]);
    Memory::update_RAM_used(p_size);
    this->burst_time = std::stoi(p[2]);
    this->state = WAITING;
    time_t t = time(0);

    struct tm* tim = localtime(&t);
    int sec = tim->tm_sec;
    sec += tim->tm_min*60;
    sec += tim->tm_hour*3600;
    this->arrivalTime = sec - Server::startTime;

    this->turnAroundTime = 0;
    this->completion_time = 0; 
}

int Process::getPid()
{
    return this->pid;
}

int Process::getState()
{
    return this->state;
}

void Process::setState(int s)
{
    this->state = s;
}

long int Process::getSize()
{
    return this->p_size;
}