#pragma once

#include "chessBoard.hpp"
#include "renderer.hpp"

class App {
private:
    ChessBoard _chessboard{};
    Renderer _renderer{};

public:
    void init_renderer2D(ImGuiIO& io);
    void init_renderer3D();

    void update();
    void loop(ImFont* bigDefaultFont);

    void key_callback(int key, int action);
};