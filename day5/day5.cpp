#include "day5.hpp"

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




bool check_if_nice_part2(const std::string & row) {

    std::cout << " :: " << row << std::endl;

    std::string vowels = "aeiou";

    // Check double repeats
    bool substr_found = false;
    for (size_t i = 0; i < row.size()-1; ++i) {
        std::string substr = row.substr(i, 2);
        //std::cout << substr << std::endl;
        if (row.find(substr, i+2) != std::string::npos) {
            std::cout << "Repeating substring found!" << std::endl;
            substr_found = true;
            break;
        }
    }
    if (!substr_found) {
        std::cout << "No repeating substrings found." << std::endl;
        return false;
    }

    // Check sandwich letters (i.e., xax)
    bool sandwich_found = false;
    for (size_t i = 0; i < row.size()-2; i++) {
        if (row[i] == row[i+2]) {
            std::cout << "Sandwich letter found!" << std::endl;
            sandwich_found = true;
            break;
        }
    }
    if (!sandwich_found) {
        std::cout << "Sandwich letter not found" << std::endl;
        return false;
    }


    std::cout << "Kid is nice, yo" << std::endl;

    return true;
}


std::vector<bool> check_if_nice_list_part2(const std::vector<std::string> & data) {

    std::vector<bool> nice_list;
    for (const auto & row : data) {
        nice_list.push_back(check_if_nice_part2(row));
    }
    return nice_list;
}