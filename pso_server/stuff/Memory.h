#include <iostream>
#include <vector>

class Memory
{
private:
    static Memory *instance;
    Memory(){};
    Memory(const Memory&){};
    ~Memory(){};

    static long int RAM; //capacitatea RAMului in octeti
 //nr hardiskuri disponibile;
    static long int RAM_used;
    static long int RAM_free;
    //to do vector de procese in memorie
    
    //to do vector de spatii libere in memorie
    
    
public:
    static Memory &getInstance();
    static void destroyInstance();
    static bool configMemory(std::vector<std::string>);
    static std::vector<std::string> getMemoryParameters();
    static void update_RAM_used(int value);
    static void update_RAM_free(int value);
    static long int get_RAM_free();

};