#pragma once

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct Args {
    std::string filename;
};

Args get_args(int argc, char * argv[]);
std::vector<std::string> load_data (const std::string & filename);

bool check_if_nice(const std::string & row);
std::vector<bool> check_if_nice_list(const std::vector<std::string> & data);

bool check_if_nice_part2(const std::string & row);
std::vector<bool> check_if_nice_list_part2(const std::vector<std::string> & data);

int count_nice(const std::vector<bool> & nice_list);