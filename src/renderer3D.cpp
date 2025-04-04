#include "renderer3D.hpp"
#include <imgui.h>
#include <vector>
#include "OpenGLutils/object/object.hpp"
#include "chessBoard.hpp"

void Renderer3D::render_board(ChessBoard& _chessboard)
{
    _chessboard.draw_board();
}

// void Renderer3D::render_skybox()
// {
//     skybox.setup_skybox();
//     skybox.load_cubemap();
//     // skybox.draw_skybox(projection, view);
// }

void Renderer3D::setup_obj()
{
    this->listOfObjects = std::vector<Object>(7);
    listOfObjects[0].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/bishop/Bishop.obj");
    listOfObjects[1].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/king/King.obj");
    listOfObjects[2].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/knight/Knight.obj");
    listOfObjects[3].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/pawn/Pawn.obj");
    listOfObjects[4].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/queen/Queen.obj");
    listOfObjects[5].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/rook/Rook.obj");
    listOfObjects[6].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/Pawn_lucas.obj");
}

void Renderer3D::draw_obj()
{
    glBindVertexArray(listOfObjects[6].getVAO()->getGLuint());
    // glDrawArrays(GL_TRIANGLES, 0, listOfObjects[6].getVAO()->getSize());
    glBindVertexArray(0);
}