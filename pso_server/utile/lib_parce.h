#ifndef LIB_PARCE_H
#define LIB_PARCE_H
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <utility>

std::pair<int, std::vector<std::string>> parce_msg(std::string msg);
std::string generate_msg(int code, std::vector<std::string> msg = {""});

#endif
