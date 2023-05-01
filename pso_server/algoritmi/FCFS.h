#include <iostream>
#include <vector>
#include "../stuff/Process.h"


class FCFS
{
private:
    static FCFS *instance;
    FCFS(){};
    FCFS(const FCFS &){};
    ~FCFS(){};
    static std::vector<Process> p_queue;
    
public:
    static int state;
    static FCFS &getInstance();
    static void destroyInstance();
    static void addProcess(Process);
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
