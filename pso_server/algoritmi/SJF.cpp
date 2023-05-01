#include <iostream>
#include <vector>
#include "SJF.h"
#include <time.h>
#include "../server.h"
#include <string>
#include "../utile/Protocol.h"
#include "../stuff/Memory.h"

SJF *SJF::instance = nullptr;
int SJF::state = 0;
std::vector<Process> SJF::p_queue = {};

SJF &SJF::getInstance()
{
    if(!SJF::instance)
    {
        SJF::instance = new SJF();
    }
    return *SJF::instance;
}


void SJF::destroyInstance()
{
    if(SJF::instance)
    {
        delete SJF::instance;
        SJF::instance = nullptr;
    }
}

void SJF::addProcess(Process p)
{
    p_queue.push_back(p);
}

void SJF::sortByBurstTime()
{

    for(int i = 0 ; i < p_queue.size(); i++)
        for(int j = i + 1; j < p_queue.size(); j++)
        {
            if(p_queue[j].burst_time < 
                p_queue[i].burst_time)
                {
                    Process p1 = p_queue[i];
                    p_queue[i] = p_queue[j];
                    p_queue[j] = p1;
                }
        }
}

void SJF::waitingTimeCalc()
{
    for(int i = 0; i < p_queue.size();i++)
    {
        int time = p_queue[i].turnAroundTime- 
            p_queue[i].burst_time;
        if(time >=0)
            p_queue[i].waitingTime = time;
        else   
            p_queue[i].waitingTime = 0;
    }
}

void SJF::turnAroundTime()
{
    for(int i = 0; i < p_queue.size(); i++)
        p_queue[i].turnAroundTime = p_queue[i].completion_time - 
                                    p_queue[i].arrivalTime;
    
}

void SJF::completionTimeCalc()
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

void SJF::sort()
{
    sortByBurstTime();
    completionTimeCalc();
    turnAroundTime();
    waitingTimeCalc();
}

std::vector<std::string> SJF::showWaitingProcesses()
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

std::string SJF::showRunningProcess()
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

std::vector<std::string> SJF::showCompletedProcesses()
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

float SJF::avgWaitingTime()
{
    float totalWaitingTime = 0;
    

    for(int i = 0; i < p_queue.size(); i++)
    {
        totalWaitingTime += p_queue[i].waitingTime;
    }

    float avgWaiting = (float)totalWaitingTime/(float)p_queue.size();
    
    return avgWaiting;
}

float SJF::avgTurnAroundTime()
{
    int totalTurnAroundTime = 0;
    for(int i = 0; i < p_queue.size(); i++)
    {
        totalTurnAroundTime += p_queue[i].turnAroundTime;
    }
    int avgTurnAround = (float)totalTurnAroundTime / (float)p_queue.size();
    return avgTurnAround;
}

