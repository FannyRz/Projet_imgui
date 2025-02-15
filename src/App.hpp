#pragma once

#include <imgui.h>
#include <cstddef>
#include <iostream>
#include "chessBoard.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include "renderer3D.hpp"

class App {
private:
    // ChessBoard _chessboard{};
    Renderer3D _renderer{};

public:
    void       update();
    ChessBoard _chessboard{};
};