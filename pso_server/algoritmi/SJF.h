#include <iostream>
#include <vector>
//#include "../stuff/Process.h"
#include "FCFS.h"

class SJF
{
private:
    static SJF *instance;
    SJF(){};
    SJF(const SJF&){};
    ~SJF(){};
    static std::vector<Process> p_queue;

public:
    static int state;
    static SJF &getInstance();
    static void destroyInstance();
    static void addProcess(Process);
    static void sortByBurstTime();
    static void waitingTimeCalc();
    static void completionTimeCalc();
    static void turnAroundTime();
    static float avgWaitingTime();
    static float avgTurnAroundTime();
    static void sort();
    static std::vector<std::string> showWaitingProcesses();
    static std::string showRunningProcess();
    static std::vector<std::string> showCompletedProcesses();

};