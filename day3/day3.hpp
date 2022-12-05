#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

struct Args {
    std::string filename;
};

Args get_args(int argc, char * argv[]);
std::vector<std::string> load_data(const std::string & filename);
std::vector<std::vector<std::vector<int>>> parse_directions_from_data(const std::vector<std::string> & data);
std::vector<std::vector<int>> parse_directions_from_string(const std::string & data_row);
std::vector<int> parse_direction(const char & c);

std::vector<std::vector<std::vector<int>>> chain_positions_from_list(const std::vector<std::vector<std::vector<int>>> & directions_list);
std::vector<std::vector<int>> chain_positions(const std::vector<std::vector<int>> & directions);

std::vector<std::unordered_map<int, std::unordered_set<int>>> get_unique_positions ( const std::vector<std::vector<std::vector<int>>> & positions_list);
std::unordered_map<int, std::unordered_set<int>> get_unique_positions (const std::vector<std::vector<int>> & positions);

std::vector<int> count_unique_houses(const std::vector<std::unordered_map<int, std::unordered_set<int>>> & );
int count_unique_houses(const std::unordered_map<int, std::unordered_set<int>> & );