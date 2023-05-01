#include <iostream>
#include <vector>

class Scheduler
{
private:
    static Scheduler *instance;
    Scheduler(){};
    Scheduler(const Scheduler &){};
    ~Scheduler(){};

    static std::vector<int> algoritms;
    static int chosed_algorithm;
public:

    static std::vector<std::string> showAlgoritms();
    static bool turnOnAlgorithm(int alg_no);
    static Scheduler &getInstance();
    static void destroyInstance();
    static int getAlg();
};