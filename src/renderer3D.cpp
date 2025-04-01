#include "renderer3D.hpp"
#include <imgui.h>
#include <vector>
#include "OpenGLutils/object/object.hpp"
#include "chessBoard.hpp"

void Renderer3D::render_board(ChessBoard& _chessboard)
{
    _chessboard.draw_board();
}

void Renderer3D::setup_obj()
{
    this->listOfObjects = std::vector<Object>(1);
    listOfObjects[0].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/Pawn.obj");
}

void Renderer3D::draw_obj()
{
    glBindVertexArray(listOfObjects[0].getVAO()->getGLuint());
    glDrawArrays(GL_TRIANGLES, 0, listOfObjects[0].getVAO()->getSize());
    glBindVertexArray(0);
}