#pragma once
#include <vector>
#include "glad/glad.h"

void display_tab(const std::vector<std::pair<int, int>>& all_possible_move);
bool is_on_the_chessboard(int x, int y);