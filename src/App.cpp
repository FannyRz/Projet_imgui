#include "App.hpp"
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include "quick_imgui/quick_imgui.hpp"

void App::update()
{
    _renderer.render_board(_chessboard);
}