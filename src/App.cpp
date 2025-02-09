#include "App.hpp"
#include <imgui.h>

void App::update()
{
    _renderer.render_board(_chessboard);
}
