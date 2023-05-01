#include <iostream>
#include <vector>
#include <sstream>
#include "lib_parce.h"
#include "interpreter.h"
#include "Protocol.h"

#include "../server.h"
#include "../stuff/Memory.h"
#include "../algoritmi/Scheduler.h"
//#include "../algoritmi/FCFS.h"
#include "../algoritmi/SJF.h" 

void interpreter::interpret_msg(std::pair<int, std::vector<std::string>> msg,int clSok)
{
	//serverul, in general, trimite true sau false in functie de raspunsul cererii + date necesare
	switch (msg.first) //vezi protocol
	{
	case(SAY_BYE):{
        //std::cout<<"Client lost\n";
		Server::sendMessage("TRUE",clSok);
		Server::CloseServer(clSok);
        break;
    }
	case(CONFIG_SERVER):{
		
		Server::sendMessage(generate_msg(true),clSok);
		break;
	}
	case(SHOW_ALGORITHMS_TO_CHOSE):{
		Server::sendMessage(generate_msg(true,Scheduler::showAlgoritms()),clSok);
		break;
	}
	case(CHOSE_ALGORITHM):{

		int alg_no = stoi(msg.second[0]);
		Server::sendMessage(generate_msg(Scheduler::turnOnAlgorithm(alg_no)),clSok);
		break;
	}
	case(CONFIG_MEMORY):{
		if(Memory::configMemory(msg.second) == true)
			Server::sendMessage(generate_msg(true),clSok);
		else 
			Server::sendMessage(generate_msg(false),clSok);
		break;
	}
	case(SHOW_MEMORY_PARAMETERS):{
		Server::sendMessage(generate_msg(true,
							Memory::getMemoryParameters()),clSok);
		break;
	}
	case(ADD_PROCESS):{
		int a = stoi(msg.second[0]) + 29;
		

		int value = std::atoi(msg.second[2].c_str());
		if(value >= Memory::get_RAM_free())
		{
			Server::sendMessage(generate_msg(false,{"Memorie indisponibila."}),clSok);
			break;
		}
		switch(a)
		{
		case(a_FCFS):{
			FCFS::addProcess(Process(msg.second));
			Server::sendMessage(generate_msg(true),clSok);
			break;
		}
		case(a_SJF):{
			SJF::addProcess(Process(msg.second));
			Server::sendMessage(generate_msg(true),clSok);
			break;
		}
		default: break;
		}
	}
	case(SHOW_PROCESSES_QUEUE):{
		//std::vector<std::string> g = Processes_Queue::show_queue();
		Server::sendMessage(generate_msg(true),clSok);
		break;
	}
	case(SHOW_WAITING_PROC):{
		std::vector<std::string> pr = {};
		if(Scheduler::getAlg() == a_FCFS)
			pr = FCFS::showWaitingProcesses();
		else if(Scheduler::getAlg() == a_SJF)
			pr = SJF::showWaitingProcesses();

		if(pr.size() != 0)
			Server::sendMessage(generate_msg(true,pr),clSok);
		else
			Server::sendMessage(generate_msg(false),clSok);
		break;
	}
	case(SHOW_RUNNING_PROC):{
		std::string pr;
		if(Scheduler::getAlg() == a_FCFS)
			pr = FCFS::showRunningProcess();
		else if(Scheduler::getAlg() == a_SJF)
			pr = SJF::showRunningProcess();	

		if(pr.length() > 1)
			Server::sendMessage(generate_msg(true,{pr}),clSok);
		else
			Server::sendMessage(generate_msg(false),clSok);
		break;
	}
	case(SHOW_COMPLETED_PROC):{
		std::vector<std::string> pr;
		if(Scheduler::getAlg() == a_FCFS)
			pr = FCFS::showCompletedProcesses();
		else if(Scheduler::getAlg() == a_SJF)
			pr = SJF::showCompletedProcesses();

		if(pr.size() != 0)
			Server::sendMessage(generate_msg(true,pr),clSok);
		else
			Server::sendMessage(generate_msg(false),clSok);
		break;
	}
	case(SHOW_STATISTICS):{

		std::string waiting_t,burst_t;
		float v1,v2;
		if(Scheduler::getAlg() == a_FCFS)
		{
			v1 = FCFS::avgWaitingTime();
			v2 = FCFS::avgTurnAroundTime();
		}
		else if(Scheduler::getAlg() == a_SJF)
		{
			v1 = SJF::avgWaitingTime();
			v2 = SJF::avgTurnAroundTime();
		}
		waiting_t = std::to_string(v1);
		burst_t = std::to_string(v2);
		Server::sendMessage(generate_msg(true,{waiting_t,burst_t}),clSok);

	}
	default: break;
	}
}
