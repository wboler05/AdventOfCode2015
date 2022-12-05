#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Args {
    std::string filename;
};

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

int determine_wrapper_paper_surface_area(const std::vector<int> & dimensions) {
    std::vector<int> surface_area_components(3);
    surface_area_components[0] = dimensions[0] * dimensions[1];
    surface_area_components[1] = dimensions[1] * dimensions[2];
    surface_area_components[2] = dimensions[2] * dimensions[0];

    int surface_area = 0;
    for (const auto & d : surface_area_components) {
        surface_area += 2*d;
    }

    int min_component = *std::min_element(surface_area_components.begin(), surface_area_components.end());
    surface_area += min_component;
    return surface_area;
}

std::vector<int> determine_wrapping_paper_surface_area_from_list (const std::vector<std::vector<int>> & dimension_list) {
    std::vector<int> surface_area_list;

    for (const auto & dimensions : dimension_list) {
        surface_area_list.push_back(determine_wrapper_paper_surface_area(dimensions));
    }
    return surface_area_list;

}

int main(int argc, char * argv[]) {

    Args args = get_args(argc, argv);
    std::vector<std::string> data = load_data(args.filename);
    std::vector<std::vector<int>> dimension_list = parse_dimensions(data);
    std::vector<int> surface_area_list = determine_wrapping_paper_surface_area_from_list(dimension_list);

    int total_wrapping_paper = 0;
    for (const auto & s : surface_area_list) {
        total_wrapping_paper += s;
    }
    
    std::cout << "Total Area: " << total_wrapping_paper << std::endl;

    return 0;
}