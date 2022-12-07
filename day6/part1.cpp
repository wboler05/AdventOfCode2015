#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

enum COMMAND { TURN_ON=0, TURN_OFF=1, TOGGLE=2 };

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


std::vector<std::string> get_data(const std::string & filename) {
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

std::vector<int> tokenize_instruction(const int & command, const std::string & start, const std::string & end) {
    std::vector<std::string> buffer;
    std::string line;
    std::istringstream start_ss(start);
    while (std::getline(start_ss, line, ',')) {
        buffer.push_back(line);
    }
    int x = std::atoi(buffer[0].c_str());
    int y = std::atoi(buffer[1].c_str());
    
    buffer.clear();
    std::istringstream end_ss(end);
    while (std::getline(end_ss, line, ',')) {
        buffer.push_back(line);
    }
    int e_x = std::atoi(buffer[0].c_str());
    int e_y = std::atoi(buffer[1].c_str());

    return std::vector<int>({
        command, x, y, e_x, e_y
    });
}

std::vector<int> parse_instruction(const std::string & row) {
    std::vector<int> instruction_line;

    std::vector<std::string> split_by_space;
    std::string line;
    std::istringstream row_ss(row);
    while(std::getline(row_ss, line, ' ')) {
        split_by_space.push_back(line);
    }

    if (split_by_space[0] == "toggle") {
        return tokenize_instruction(TOGGLE, split_by_space[1], split_by_space[3]);
    } else if (split_by_space[0] == "turn") {
        if (split_by_space[1] == "on") {
            return tokenize_instruction(TURN_ON, split_by_space[2], split_by_space[4]);
        } else if (split_by_space[1] == "off") {
            return tokenize_instruction(TURN_OFF, split_by_space[2], split_by_space[4]);
        }
    }

    return instruction_line;
}

std::vector<std::vector<int>> parse_instructions(const std::vector<std::string> & data) {

    std::vector<std::vector<int>> instructions;
    for (const auto & row : data) {
        instructions.push_back(parse_instruction(row));
    }
    return instructions;
}


void turn_on(std::vector<std::vector<bool>> & grid, const std::vector<int> & instruction) {
    int start_x = instruction[1];
    int start_y = instruction[2];
    int end_x = instruction[3];
    int end_y = instruction[4];

    for (size_t i = start_x; i <= end_x && i < grid.size(); i++) {
        for (size_t j = start_y; j <= end_y && j < grid[i].size(); j++) {
            grid[i][j] = true;
        }
    }
}

void turn_off(std::vector<std::vector<bool>> & grid, const std::vector<int> & instruction) {
    int start_x = instruction[1];
    int start_y = instruction[2];
    int end_x = instruction[3];
    int end_y = instruction[4];

    for (size_t i = start_x; i <= end_x && i < grid.size(); i++) {
        for (size_t j = start_y; j <= end_y && j < grid[i].size(); j++) {
            grid[i][j] = false;
        }
    }
}

void toggle(std::vector<std::vector<bool>> & grid, const std::vector<int> & instruction) {
    int start_x = instruction[1];
    int start_y = instruction[2];
    int end_x = instruction[3];
    int end_y = instruction[4];

    for (size_t i = start_x; i <= end_x && i < grid.size(); i++) {
        for (size_t j = start_y; j <= end_y && j < grid[i].size(); j++) {
            grid[i][j] = !grid[i][j];
        }
    }
}


std::vector<std::vector<bool>> determine_christmas_lights(const std::vector<std::vector<int>> & instructions) {

    std::vector<std::vector<bool>> grid(1000, std::vector<bool>(1000, false));

    for (const auto & instruction : instructions) {

        switch (instruction[0]) {
            case TURN_ON:
                turn_on(grid, instruction);
                break;
            case TURN_OFF:
                turn_off(grid, instruction);
                break;
            case TOGGLE:
                toggle(grid, instruction);
                break;
            default:
                std::cerr << "Unrecognized instruction: " << instruction[0] << std::endl;
                exit(1);
        }
    }

    return grid;
}

int count_lights_on(const std::vector<std::vector<bool>> & grid) {
    int count = 0;
    for (const auto & x : grid) {
        for (const auto & y : x) {
            if (y) {
                count++;
            }
        }
    }
    return count;
}


int main(int argc, char * argv[]) {

    Args args = get_args(argc, argv);

    std::vector<std::string> data = get_data(args.filename);
    std::vector<std::vector<int>> instructions = parse_instructions(data);
    std::vector<std::vector<bool>> grid = determine_christmas_lights(instructions);
    int lights_on = count_lights_on(grid);

    std::cout << "Lights on: " << lights_on << std::endl;

    return 0;
}