#include "day5.hpp"


int main(int argc, char * argv[]) {
    
    Args args = get_args(argc, argv);

    std::vector<std::string> data = load_data(args.filename);
    std::vector<bool> nice_list = check_if_nice_list_part2(data);
    int nice_count = count_nice(nice_list);

    std::cout << "Nice Count: " << nice_count << std::endl;

    return 0;
}