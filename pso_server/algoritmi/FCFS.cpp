#include <iostream>
#include <vector>
#include "FCFS.h"
#include <time.h>
#include "../server.h"
#include <string>
#include "../utile/Protocol.h"
#include "../stuff/Memory.h"

FCFS *FCFS::instance = nullptr;
int FCFS::state = 0;
std::vector<Process> FCFS::p_queue = {};

FCFS &FCFS::getInstance()
{
    if(!FCFS::instance)
    {
        FCFS::instance = new FCFS();
    }
    return *FCFS::instance;
}

void FCFS::destroyInstance()
{
    if(FCFS::instance)
    {
        delete FCFS::instance;
        FCFS::instance = nullptr;
    }
}

void FCFS::addProcess(Process p)
{
    p_queue.push_back(p);
}

void FCFS::waitingTimeCalc()
{
    for(int i = 1; i < p_queue.size(); i++)
    {
        p_queue[i].waitingTime = p_queue[i].turnAroundTime - 
            p_queue[i].burst_time;
    }    
}

void FCFS::completionTimeCalc()
{
    time_t t = time(0);
    struct tm* tim = localtime(&t);
    int sec = tim->tm_sec;
    sec += tim->tm_min*60;
    sec += tim->tm_hour*3600;

    sec -= Server::startTime;
    p_queue[0].completion_time = p_queue[0].burst_time;
    int tt = sec - p_queue[0].arrivalTime;
    int ok = 0;
    if(p_queue[0].completion_time < tt)
    {
        p_queue[0].setState(COMPLETED);
        Memory::update_RAM_free(p_queue[0].getSize());
    }    
    else 
    {
        p_queue[0].setState(RUNNING);
        ok = 1;
    }    
    
    for(int i = 1; i < p_queue.size(); i++)
    {
        tt = sec - p_queue[i].arrivalTime;

        p_queue[i].completion_time = p_queue[i-1].completion_time +
            p_queue[i].burst_time;

        if(p_queue[i].completion_time < tt)
        {
            p_queue[i].setState(COMPLETED);
            Memory::update_RAM_free(p_queue[i].getSize());
        }    
        else if(ok == 0){
            p_queue[i].setState(RUNNING);
            ok++;
        }
        else p_queue[i].setState(WAITING);
    }
}

void FCFS::turnAroundTime()
{
    
    for(int i = 0; i < p_queue.size(); i++)
    {      
        p_queue[i].turnAroundTime = p_queue[i].completion_time - 
            p_queue[i].arrivalTime;
    }    

}

float FCFS::avgWaitingTime()
{
    float totalWaitingTime = 0;
    
    for(int i = 0; i < p_queue.size(); i++)
    {
        totalWaitingTime += p_queue[i].waitingTime;
    }

    float avgWaiting = (float)totalWaitingTime/(float)p_queue.size();
    
    return avgWaiting;
}

float FCFS::avgTurnAroundTime()
{
    float totalTurnAroundTime = 0;
    for(int i = 0; i < p_queue.size(); i++)
    {
        totalTurnAroundTime += p_queue[i].turnAroundTime;
    }
    float avgTurnAround = (float)totalTurnAroundTime / (float)p_queue.size();
    return avgTurnAround;
}

void FCFS::sort()
{
    completionTimeCalc();
    turnAroundTime();
    waitingTimeCalc();
}

std::vector<std::string> FCFS::showWaitingProcesses()
{
    sort();

    std::vector<std::string> procese = {};
    
    for(int i = 0 ; i < p_queue.size(); i++)
    {
        if(p_queue[i].getState() == WAITING)
        {
            std::string _proc = "P";
            _proc += std::to_string(p_queue[i].getPid());
        
            procese.push_back(_proc);
        }
        
    }
    return procese;
}

std::string FCFS::showRunningProcess()
{
    sort();

    std::string proces = "";
    
    for(int i = 0 ; i < p_queue.size(); i++)
    {
        if(p_queue[i].getState() == RUNNING)
        {
            proces = "P";
            proces += std::to_string(p_queue[i].getPid());
            return proces;
        }
        
    }
    return proces;
}
std::vector<std::string> FCFS::showCompletedProcesses()
{
    sort();

    std::vector<std::string> procese = {};
    
    for(int i = 0 ; i < p_queue.size(); i++)
    {
        if(p_queue[i].getState() == COMPLETED)
        {
            std::string _proc = "P";
            _proc += std::to_string(p_queue[i].getPid());
        
            procese.push_back(_proc);
        }
        
    }
    return procese;
}

