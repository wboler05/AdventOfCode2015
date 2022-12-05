#include <iostream>

#include "day2_functions.hpp"

int determine_ribbon_length(const std::vector<int> & dimensions) {
    int max_dimension = 0;
    size_t max_dimension_idx = 0;
    for (size_t i = 0; i < dimensions.size(); ++i) {
        if (max_dimension < dimensions[i]) {
            max_dimension = dimensions[i];
            max_dimension_idx = i;
        }
    }

    int total_ribbon_length = 0;
    int total_bow_length = 1;
    for (size_t i = 0; i < dimensions.size(); ++i) {
        total_bow_length *= dimensions[i];
        if (i == max_dimension_idx) {
            continue;
        }
        total_ribbon_length += 2 * dimensions[i];
    }

    return total_ribbon_length + total_bow_length;
}

std::vector<int> determine_ribbon_lengths(const std::vector<std::vector<int>> & dimension_list) {
    std::vector<int> ribbon_length_list;
    for (const auto & d : dimension_list) {
        ribbon_length_list.push_back(determine_ribbon_length(d));
    }
    return ribbon_length_list;
}

int main (int argc, char * argv[]) {
    Args args = get_args(argc, argv);
    std::vector<std::string> data = load_data(args.filename);
    std::vector<std::vector<int>> dimension_list = parse_dimensions(data);

    std::vector<int> ribbon_length_list = determine_ribbon_lengths(dimension_list);

    int total_ribbon_length = 0;
    for (const auto & r : ribbon_length_list) {
        total_ribbon_length += r;
    }

    std::cout << "Total Ribbon Length: " << total_ribbon_length << std::endl;

    return 0;
}