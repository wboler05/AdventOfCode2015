#include "day3.hpp"

int main (int argc, char * argv[]) {

    Args args = get_args(argc, argv);
    auto data = load_data(args.filename);
    auto directions_list = parse_directions_from_data(data);
    auto positions = chain_positions_from_list(directions_list);
    auto unique_position_list = get_unique_positions(positions);
    auto house_counts = count_unique_houses(unique_position_list);

    /*
    for (size_t i = 0; i < directions_list.size(); ++i) {
        std::cout << "Row: " << i << std::endl;
        for (size_t j = 0; j < directions_list[i].size(); j++) {
            std::cout << " :: ";
            for (size_t k = 0; k < directions_list[i][j].size(); k++) {
                std::cout << directions_list[i][j][k] << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }*/

    /*
    for (size_t i = 0; i < positions.size(); ++i) {
        std::cout << "i: " << i << std::endl;
        for (size_t j = 0; j < positions[i].size(); ++j) {
            std::cout << " :: ( ";
            for (size_t k = 0; k < positions[i][j].size(); ++k) {
                std::cout << positions[i][j][k] << ", ";
            }
            std::cout << " )" << std::endl;
        }
    }*/

    /*
    for (size_t i = 0; i < unique_position_list.size(); ++i) {
        std::cout << "i: " << i << std::endl;
        for (const auto & [x, y_list] : unique_position_list[i]) {
            for (const auto & y : y_list) {
                std::cout << " : (" << x << ", " << y << ")" << std::endl;
            }
        }
        std::cout << std::endl;
    }*/

    for (size_t i = 0; i < house_counts.size(); ++i) {
        std::cout << i << ": " << house_counts[i] << std::endl;
    }

    return 0;
}