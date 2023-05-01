#include <iostream>
#include "Menu.h"
#include "lib_parce.h"
#include "client.h"
#include "Protocol.h"

std::string Alg = "";

void displayStartMenu()
{
    std::cout<<"\nAlege una din urmatoarele optiuni:\n";
    std::cout<<"1)  Configureaza server\n";
    std::cout<<"2)  Adauga procese\n";
    std::cout<<"3)  Vezi procesele in starea waiting\n";
    std::cout<<"4)  Vezi procesul in starea running\n";
    std::cout<<"5)  Vezi procesele in starea completed\n";
    //std::cout<<"6)  Vezi statistici\n";
    std::cout<<"7)  Deconectare\n";

    std::string o;
    std::pair<int, std::vector<std::string>> resp;

    
    std::getline(std::cin,o);
    
    if(o=="1")
    {
        Conectare_Srv::SendToServer(generate_msg(CONFIG_SERVER));
        resp = parce_msg(Conectare_Srv::Recvs());
        if(resp.first == true)
        {
            displayConfigMenu();
        }
        else 
        {
            std::cout<<"ERROR: nu aveti drept de acces in acest mode\n";
        }
        
    }
    else if( o == "2")
    {
        if(Alg == "")
        {
            std::cout<<"Alegeti un algoritm de sortare din optiunea Configureaza server";
            displayConfigMenu();
        }
        std::cout<<"Cate procese doriti sa adaugati?\n";
        std::string nr;
        std::getline(std::cin, nr);

        for(int i = 1; i <= std::stoi(nr); i++)
        {
            std::cout<<"Procesul "<<i<<":\n"; 
            std::string size, burst_time;
            std::cout<<"Dimensiune in bytes:    ";
            std::getline(std::cin, size);
            std::cout<<"Timp de executie:   ";
            std::getline(std::cin,burst_time);
            

            Conectare_Srv::SendToServer(generate_msg(ADD_PROCESS,{Alg,size, burst_time}));
            resp = parce_msg(Conectare_Srv::Recvs());
            if(resp.first == false)
                std::cout<<"ERROR: "<<resp.second[0]<<"\n";
            else if(resp.first == true)
                std::cout <<"Proces adaugat cu suces\n";

        }
    }
    else if(o == "3")
    {
        Conectare_Srv::SendToServer(generate_msg(SHOW_WAITING_PROC));
        resp = parce_msg(Conectare_Srv::Recvs());
        if(resp.first == false)
            std::cout<<"Nu se afla procese in starea waiting.\n";
        else 
        {
            std::cout<<"Waiting queue:\n";
            for(int i =0; i < resp.second.size(); i++)
            {
                std::cout<<resp.second[i]<<" ";
            }
            std::cout<<"\n";
        }
        
    }
    else if(o == "4")
    {
        Conectare_Srv::SendToServer(generate_msg(SHOW_RUNNING_PROC));
        resp = parce_msg(Conectare_Srv::Recvs());
        if(resp.first == false)
            std::cout<<"Niciun proces nu se afla in starea running\n";
        else
            std::cout<<"Procesul care se executa este: "<<resp.second[0]<<"\n";
    }
    else if(o == "5")
    {
        Conectare_Srv::SendToServer(generate_msg(SHOW_COMPLETED_PROC));
        resp = parce_msg(Conectare_Srv::Recvs());
        if(resp.first == false)
            std::cout<<"Nu exista procese terminate.\n";
        else 
        {
            std::cout<<"Completed list:\n";
            for(int i =0; i < resp.second.size(); i++)
            {
                std::cout<<resp.second[i]<<" ";
            }
            std::cout<<"\n";
        }
    }
    else if( o == "6")
    {
        Conectare_Srv::SendToServer(generate_msg(SHOW_STATISTICS));
        resp = parce_msg(Conectare_Srv::Recvs());
        std::cout<<"Timpul mediu de asteptare:  "<<resp.second[0]<<"\n";
        std::cout<<"Timpul mediu de executie:   "<<resp.second[1]<<"\n";
    }
    else if(o == "7")
    {
        Conectare_Srv::SendToServer(generate_msg(SAY_BYE));
        exit(-1);
    }
    else {
        std::cout<<"Aigurati-va ca introduceti o optiune valida in meniu: \n";
    }
    displayStartMenu();
    
}

void displayConfigMenu()
{
    std::cout<<"\n\n***Va aflati in modul de configurare al serverului\n";
    std::cout<<"Alegeti una din urmatoarele optiuni:\n";
    std::cout<<"1)  Vizualizare parametri\n";
    std::cout<<"2)  Setare algoritm de sortare al proceselor\n";
    std::cout<<"3)  Configurare memorie\n";
    std::cout<<"4)  Inapoi la meniul principal\n";
    std::cout<<"5)  Deconectare\n";

    std::string o;
    std::pair<int, std::vector<std::string>> resp;
    
    std::getline(std::cin,o);
    if(o == "1")
    {
        std::cout<<"\nAlgoritm de sortare:  -   \n";
        Conectare_Srv::SendToServer(generate_msg(SHOW_MEMORY_PARAMETERS));
        resp = parce_msg(Conectare_Srv::Recvs());
        if(resp.first == true)
        {
            std::cout<<"RAM size:   "<<resp.second[0]<<"\t\n";
            std::cout<<"RAM used:   "<<resp.second[1]<<"\t\n";
            std::cout<<"RAM free:   "<<resp.second[2]<<"\t\n";
        }
    }
    else if(o == "2")
    {
        Conectare_Srv::SendToServer(generate_msg(SHOW_ALGORITHMS_TO_CHOSE));
        resp = parce_msg(Conectare_Srv::Recvs());
        std::cout<<std::endl;
        std::cout<<"Algoritmii disponibili:\n";
        int nr = 0;
        for(auto a : resp.second)
        {
            nr++;
            std::cout<<nr<<")   "<<a<<std::endl;
        } 

        int ok=0;
        while(ok != 1){
            std::cout<<"Introduceti numarul algoritmului dorit:\n";
            std::string alg;
            std::getline(std::cin,alg);
            Conectare_Srv::SendToServer(generate_msg(CHOSE_ALGORITHM,{alg}));
            resp = parce_msg(Conectare_Srv::Recvs());
            if(resp.first == true)
            {
                std::cout<<"Algoritm ales cu succes!\n\n";
                Alg = alg;
                ok = 1;
            }
            else{
                std::cout<<"Algoritmul este deja in functiune\n";
            }
        }
        
    }
    else if (o == "3")
    {
        std::cout<<"Valoarea RAM in bytes:  ";
        std::string ram;
        std::getline(std::cin,ram);
        Conectare_Srv::SendToServer(generate_msg(CONFIG_MEMORY,{ram}));
        resp = parce_msg(Conectare_Srv::Recvs());
        if(resp.first == false)
        {
            std::cout<<"ERROR:  memoria nu a fost setata\n";
            displayConfigMenu();
        }    
    }
    else if (o == "4")
    {
        displayStartMenu();
    }
    else if (o == "5")
    {
        Conectare_Srv::SendToServer(generate_msg(SAY_BYE));
        exit(-1);
    }
    else {
        std::cout<<"Aigurati-va ca introduceti o optiune valida in meniu: \n";
    }
    
    std::cout<<"introduceti o optiune din meniu:\n";
    displayConfigMenu();
    
}