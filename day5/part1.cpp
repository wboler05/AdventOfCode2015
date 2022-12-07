#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct Args {
    std::string filename;
};


Args get_args(int argc, char * argv[]) {

    if (argc <= 1) {
        std::cerr << "Error, missing filename" << std::endl;
        exit(1);
    }

    Args args;
    args.filename = argv[1];
    return args;
}

std::vector<std::string> load_data (const std::string & filename) {
    std::ifstream ifile(filename);
    if (!ifile.good()) {
        std::cerr << "Error, cannot open file: " << filename << std::endl;
        exit(1);
    }

    std::vector<std::string> data;
    std::string line;
    while (std::getline(ifile, line)) {
        data.push_back(line);
        std::cout << line << std::endl;
    }

    return data;
}

bool check_if_nice(const std::string & row) {

    std::cout << row << std::endl;

    std::string vowels = "aeiou";

    // Check for vowels
    int vowel_count = 0;
    for (const auto & c : row) {
        for (const auto & v : vowels) {
            if (c == v) {
                vowel_count++;
            }
        }
    }
    if (vowel_count < 3) {
        std::cout << "Does not contain 3 vowels" << std::endl;
        return false;
    }

    bool double_found = false;
    for (size_t i = 1; i < row.size(); ++i) {
        if (row[i] == row[i-1]) {
            double_found = true;
            break;
        }
    }

    if (!double_found) {
        std::cout << "No double letter found." << std::endl;
        return false;
    }

    std::vector<std::string> select_substrings = { "ab", "cd", "pq", "xy"};
    for (const auto & s : select_substrings) {
        if (row.find(s) != std::string::npos) {
            std::cout << "Naughty substring found!" << std::endl;
            return false;
        }
    }

    std::cout << "Kid is nice, yo" << std::endl;

    return true;
}


std::vector<bool> check_if_nice_list(const std::vector<std::string> & data) {

    std::vector<bool> nice_list;
    for (const auto & row : data) {
        nice_list.push_back(check_if_nice(row));
    }
    return nice_list;
}

int count_nice(const std::vector<bool> & nice_list) {
    int nice_count = 0;
    for (const auto & nice : nice_list) {
        if (nice) {
            nice_count++;
        }
    }
    return nice_count;
}


int main(int argc, char * argv[]) {
    
    Args args = get_args(argc, argv);

    std::vector<std::string> data = load_data(args.filename);
    std::vector<bool> nice_list = check_if_nice_list(data);
    int nice_count = count_nice(nice_list);

    std::cout << "Nice Count: " << nice_count << std::endl;

    return 0;
}