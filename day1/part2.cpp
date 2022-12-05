#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Args {
    std::string filename;
};

Args get_args(int argc, char * argv[]) {
    Args args;

    if (argc <= 1) {
        std::cerr << "Error, provide a filename!" << std::endl;
        exit(1);
    } else {
        args.filename = std::string(argv[1]);

        std::ifstream ifile(args.filename);
        if (!ifile.good()) {
            std::cerr << "Error, file not found: " << args.filename << std::endl;
            exit(1);
        }
    }
    return args;
}

std::vector<std::string> load_data(const std::string & filename) {
    std::vector<std::string> data;

    std::ifstream ifile(filename);
    if (!ifile.good()) {
        std::cerr << "Error, file not found: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(ifile, line)) {
        data.push_back(line);
        std::cout << line << std::endl;
    }

    return data;
}

std::vector<size_t> determine_basement_command(const std::vector<std::string> & data) {
    std::vector<size_t> floors;

    for (size_t i = 0; i < data.size(); ++i) {
        const std::string & row = data[i];
        int floor_count = 0;
        for (size_t j = 0; j < row.size(); ++j) {
            if (row[j] == '(') {
                floor_count++;
            } else if (row[j] == ')') {
                floor_count--;
            }

            if (floor_count == -1) {
                floors.push_back(j);
                break;
            }
        }
        std::cout << "Line: " << row << "\tFloor Count: " << floor_count << std::endl;
    }

    return floors;
}


int main (int argc, char * argv[]) {
    
    Args args = get_args(argc, argv);

    std::vector<std::string> data = load_data(args.filename);
    std::vector<size_t> floor_counts = determine_basement_command(data);

    for (size_t i = 0; i < floor_counts.size(); ++i) {
        std::cout << floor_counts[i] + 1 << std::endl;
    }

    return 0;
}