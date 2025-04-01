#include "utils.hpp"
#include <iostream>

void display_tab(const std::vector<std::pair<int, int>>& all_possible_move)
{
    for (const auto& move : all_possible_move)
    {
        std::cout << "(" << move.first << ", " << move.second << ")" << '\n';
    }
}

bool is_on_the_chessboard(int x, int y)
{
    return x < 8 && x >= 0 && y < 8 && y >= 0;
}