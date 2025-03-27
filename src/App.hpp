#pragma once

#include "chessBoard.hpp"
#include "renderer3D.hpp"

class App {
private:
    ChessBoard _chessboard{};
    Renderer3D _renderer{};

public:
    void        update();
    ChessBoard& get_chessboard() { return this->_chessboard; };
    Renderer3D& get_renderer() { return this->_renderer; };
};