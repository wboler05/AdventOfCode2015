#include "day3.hpp"

Args get_args(int argc, char * argv[]) {

    if (argc <= 1) {
        std::cerr << "Error, missing filename" << std::endl;
        exit(1);
    }

    Args args;
    args.filename = argv[1];
    return args;
}

std::vector<std::string> load_data(const std::string & filename) {
    std::ifstream ifile(filename);

    if (!ifile.good()) {
        std::cerr << "Error, could not open file: " << filename << std::endl;
        exit(1);
    }

    std::vector<std::string> data;
    std::string line;
    while (std::getline(ifile, line)) {
        data.push_back(line);
    }

    return data;
}

std::vector<std::vector<std::vector<int>>> parse_directions_from_data(const std::vector<std::string> & data) {
    std::vector<std::vector<std::vector<int>>> directions;
    for (const std::string & s : data) {
        directions.push_back(parse_directions_from_string(s));
    }
    return directions;
}

std::vector<std::vector<int>> parse_directions_from_string(const std::string & data_row) {
    std::vector<std::vector<int>> directions;

    for (const auto & c : data_row) {
        directions.push_back(parse_direction(c));
    }
    return directions;
}

std::vector<int> parse_direction(const char & c) {
    std::vector<int> direction(2, 0);

    switch (c) {
        case '^':
            direction[1] = 1;
            break;
        case '>':
            direction[0] = 1;
            break;
        case 'v':
            direction[1] = -1;
            break;
        case '<':
            direction[0] = -1;
            break;
        default:
            std::cerr << "Error, unrecognized character: " << c << std::endl;
            exit(1);
    }
    return direction;
}

std::vector<std::vector<std::vector<int>>> chain_positions_from_list(const std::vector<std::vector<std::vector<int>>> & directions) {
    std::vector<std::vector<std::vector<int>>> positions;
    for (const auto & d : directions) {
        positions.push_back(chain_positions(d));
    }
    return positions;
}

std::vector<std::vector<int>> chain_positions(const std::vector<std::vector<int>> & directions) {
    std::vector<int> position(2, 0);
    std::vector<std::vector<int>> positions;
    positions.push_back(position);
    for (const auto & direction : directions) {
        for (size_t i = 0; i < direction.size(); ++i) {
            position[i] += direction[i];
        }
        positions.push_back(position);
    }
    return positions;
}

std::vector<std::unordered_map<int, std::unordered_set<int>>> get_unique_positions ( const std::vector<std::vector<std::vector<int>>> & positions_list) {
    std::vector<std::unordered_map<int, std::unordered_set<int>>> unique_position_list;
    for (const auto & p : positions_list) {
        unique_position_list.push_back(get_unique_positions(p));
    }
    return unique_position_list;
}

std::unordered_map<int, std::unordered_set<int>> get_unique_positions (const std::vector<std::vector<int>> & positions) {
    std::unordered_map<int, std::unordered_set<int>> unique_positions;
    for (const auto & p : positions) {
        if (unique_positions.count(p[0]) == 0) {
            unique_positions.emplace(p[0], std::unordered_set<int>());
        }
        unique_positions[p[0]].insert(p[1]);
    }
    return unique_positions;
}

std::vector<int> count_unique_houses(const std::vector<std::unordered_map<int, std::unordered_set<int>>> & unique_position_list) {
    std::vector<int> house_counts;
    for (const auto & p : unique_position_list) {
        house_counts.push_back(count_unique_houses(p));
    }
    return house_counts;
}

int count_unique_houses(const std::unordered_map<int, std::unordered_set<int>> & unique_positions) {
    int house_counts = 0;
    for (const auto & [x, y_list] : unique_positions) {
        for (const auto & y : y_list) {
            house_counts++;
        }
    }
    return house_counts;
}

/// Part 2

std::vector<std::vector<std::string>> split_directions_data(const std::vector<std::string> & data) {
    std::vector<std::vector<std::string>> data_split(2);

    for (size_t i = 0; i < data.size(); ++i) {
        std::string left, right;
        for (size_t j = 0; j < data[i].size(); j+=2) {
            left.push_back(data[i][j]);
            right.push_back(data[i][j+1]);
        }

        data_split[0].push_back(left);
        data_split[1].push_back(right);
    }

    return data_split;
}

std::unordered_map<int, std::unordered_set<int>> merge_maps(const std::unordered_map<int, std::unordered_set<int>> & left, const std::unordered_map<int, std::unordered_set<int>> & right) {
    std::unordered_map<int, std::unordered_set<int>> full_map(left);

    for (const auto & [x, y_set] : right) {
        if (full_map.count(x) == 0) {
            full_map[x] = y_set;
        } else {
            for (const auto & y : y_set) {
                full_map[x].insert(y);
            }
        }
    }

    return full_map;
}
