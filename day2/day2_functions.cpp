#include "day2_functions.hpp"

Args get_args(int argc, char * argv[]) {
    Args args;

    if (argc <= 1) {
        std::cerr << "Error, missing filename" << std::endl;
        exit(1);
    } else {
        args.filename = argv[1];
        std::cout << "Filename: " << args.filename << std::endl;
    }

    return args;
}

std::vector<std::string> load_data(const std::string & filename) {

    std::vector<std::string> data;
    std::ifstream ifile(filename);

    if (!ifile.good()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(1);
    }

    std::string line; 
    while (std::getline(ifile, line)) {
        data.push_back(line);
    }

    return data;
}


std::vector<std::vector<int>> parse_dimensions(const std::vector<std::string> & data) {

    std::vector<std::vector<int>> dimension_list; 

    for (const auto & row : data) {

        std::vector<int> dimensions;

        std::istringstream row_stream(row);
        std::string element_string;
        int element; 
        while (std::getline(row_stream, element_string, 'x')) {

            std::stringstream ss;
            ss << element_string;
            ss >> element;

            dimensions.push_back(element);
        }
        dimension_list.push_back(dimensions);
    }

    return dimension_list;
}