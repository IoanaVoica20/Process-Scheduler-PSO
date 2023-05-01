//#pragma once
#include <iostream>
#include <vector>

class interpreter
{
    private:
        interpreter(){};
        interpreter(const interpreter&){};
        ~interpreter(){};
    public:
	    static void interpret_msg(std::pair<int, std::vector<std::string>>,int);
};