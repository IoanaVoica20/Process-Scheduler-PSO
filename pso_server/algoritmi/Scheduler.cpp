#include <iostream>
#include "Scheduler.h"
#include "../utile/Protocol.h"


Scheduler *Scheduler::instance = nullptr;
std::vector<int> Scheduler::algoritms = {a_FCFS,a_SJF};
int Scheduler::chosed_algorithm = 0;

Scheduler &Scheduler::getInstance()
{
    if(!Scheduler::instance)
    {
        Scheduler::instance = new Scheduler();
    }
    return *Scheduler::instance;
}

void Scheduler::destroyInstance()
{
    if(Scheduler::instance)
    {
        delete Scheduler::instance;
        Scheduler::instance = nullptr;
    }
}

std::vector<std::string> Scheduler::showAlgoritms()
{
    std::vector<std::string> l;
    for(auto a : algoritms)
    {
        if(a == a_FCFS)
            l.push_back("First In First Out");
        else if(a == a_SJF)
            l.push_back("Shortest Job First");
        
    }
    return l;
}

bool Scheduler::turnOnAlgorithm(int alg_no)
{
    
    chosed_algorithm = alg_no+29;
    return true;

}

int Scheduler::getAlg()
{
    return chosed_algorithm;
}
