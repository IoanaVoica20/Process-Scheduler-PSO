
//comenzi principale 
#define SAY_BYE 1
#define CONFIG_SERVER 2            //va transmite true pentru primul client
                                   // sau false pentru ceilalti clienti
#define ADD_PROCESS 7 
#define SHOW_PROCESSES_QUEUE 8
#define SHOW_STATISTICS 13
//.........


//comenzi de configurare a serverului
#define SHOW_ALGORITHMS_TO_CHOSE 3
#define CHOSE_ALGORITHM 4          //
#define CONFIG_MEMORY 5            //primeste ca parametru dimenisiunea ram-ului (momentan)
#define SHOW_MEMORY_PARAMETERS 6   //afiseaza setarile memoriei
//......

//
#define SHOW_WAITING_PROC 10
#define SHOW_RUNNING_PROC 11
#define SHOW_COMPLETED_PROC 12
//

//starile proceselor
#define WAITING 20
#define RUNNING 21
#define COMPLETED 22
///

//algoritmi de sortare
#define a_FCFS 30
#define a_SJF 31
//......

