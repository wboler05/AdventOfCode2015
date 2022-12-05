#include "day3.hpp"

int main (int argc, char * argv[]) {

    Args args = get_args(argc, argv);
    auto data = load_data(args.filename);
    auto data_splits = split_directions_data(data);

    std::vector<std::vector<std::unordered_map<int, std::unordered_set<int>>>> split_maps;
    for (const auto & data_split : data_splits) {
        auto directions_list = parse_directions_from_data(data_split);
        auto positions = chain_positions_from_list(directions_list);
        auto unique_positions_list = get_unique_positions(positions);
        split_maps.push_back(unique_positions_list);
    }

    std::vector<std::unordered_map<int, std::unordered_set<int>>> combined_maps;
    for (size_t i = 0; i < split_maps[0].size(); ++i) {
        combined_maps.push_back(merge_maps(split_maps[0][i], split_maps[1][i]));
    }

    auto house_counts = count_unique_houses(combined_maps);

    for (size_t i = 0; i < house_counts.size(); ++i) {
        std::cout << i << ": " << house_counts[i] << std::endl;
    }

    return 0;
}