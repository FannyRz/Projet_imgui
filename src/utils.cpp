#include "utils.hpp"
#include <iostream>

void displaytab(const std::vector<std::pair<int, int>>& all_possible_move)
{
    for (const auto& move : all_possible_move)
    {
        std::cout << "(" << move.first << ", " << move.second << ")" << '\n';
    }
}