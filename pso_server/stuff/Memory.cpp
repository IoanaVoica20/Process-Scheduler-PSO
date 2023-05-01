#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Memory.h"


Memory *Memory::instance = nullptr;
long int Memory::RAM =  -1; 
long int Memory::RAM_used = -1;
long int Memory::RAM_free = -1;

Memory &Memory::getInstance()
{
    if(!Memory::instance)
    {
        Memory::instance == new Memory();
    }
    return *Memory::instance;
}

void Memory::destroyInstance()
{
    if(Memory::instance)
    {
        delete Memory::instance;
        Memory::instance = nullptr;
    }
}

bool Memory::configMemory(std::vector<std::string> parameters)
{
    if(parameters.size() != 1)
        return false;
    
    RAM = std::stoi(parameters[0]);
    RAM_used = 0;
    RAM_free = std::stoi(parameters[0]);

    return true;

}

std::vector<std::string> Memory::getMemoryParameters()
{
    std::vector<std::string> v;
    
    if(RAM == -1)
        v.push_back("-");
    else
        v.push_back(std::to_string(RAM));
   
    if(RAM_used == -1)
        v.push_back("-");
    else
        v.push_back(std::to_string(RAM_used));

    if(RAM_free == -1)
        v.push_back("-");
    else
        v.push_back(std::to_string(RAM_free));

    return v;
}

void Memory::update_RAM_used(int value)
{
    RAM_used += value;
    RAM_free -= value;
}

void Memory::update_RAM_free(int value)
{
    RAM_free += value;
    RAM_used += value;
}

long int Memory::get_RAM_free()
{
    return RAM_free ;
}