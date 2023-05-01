#include <iostream>
#include <vector>
#include <time.h>

class Process
{
private:
    int alg;
    int pid;
    long int p_size;  //dimensiunea in bytes a procesului
    int state;   
    
public:
    int arrivalTime;
    int completion_time;
    int burst_time; //cat timp ii ia sa se execute
    int turnAroundTime;//cat timp a stat in total
    int waitingTime;
    static int pid_gen;
    Process(std::vector<std::string>);
    ~Process(){};
    int getPid();
    int getState();
    void setState(int);
    long int getSize();
};