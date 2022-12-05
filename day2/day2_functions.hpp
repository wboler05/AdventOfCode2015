#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Args {
    std::string filename;
};

Args get_args(int argc, char * argv[]);
std::vector<std::string> load_data(const std::string & filename);
std::vector<std::vector<int>> parse_dimensions(const std::vector<std::string> & data);