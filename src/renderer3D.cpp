#include "renderer3D.hpp"
#include <imgui.h>
#include <vector>
#include "OpenGLutils/object/object.hpp"
#include "OpenGLutils/object/texture.hpp"
#include "chessBoard.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"
#include "pieces/pieces.hpp"

void Renderer3D::render_board(ChessBoard& _chessboard)
{
    _chessboard.draw_board();
}

void Renderer3D::setup_shader()
{
    _shader.load_shader("../../src/openGL/shaders/pieces.vs.glsl", "../../src/openGL/shaders/pieces.fs.glsl");
    _shader.use();
}

void Renderer3D::render_skybox()
{
    this->_skybox.get_shader_skybox()->use();

    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);

    glm::mat4 projection = glm::perspective(glm::radians(70.f), 1.f, 0.1f, 100.f);
    glm::mat4 view       = glm::mat4(
        glm::mat3(glm::lookAt(glm::normalize(_trackballCamera.getPosition()), glm::vec3(0., 0., 0.), glm::vec3(0, 1, 0)))
    );

    this->_skybox.get_shader_skybox()->set_uniform_matrix_4fv("projection", projection);
    this->_skybox.get_shader_skybox()->set_uniform_matrix_4fv("view", view);
    this->_skybox.get_shader_skybox()->set_uniform_1i("textureSkybox", 0);

    glBindVertexArray(_skybox.get_VAO_skybox());
    glBindTexture(GL_TEXTURE_CUBE_MAP, _skybox.get_texture_skybox());
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}

void Renderer3D::setup_obj()
{
    this->listOfObjects = std::vector<Object>(8);
    listOfObjects[0].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/bishop/Bishop1.obj");
    listOfObjects[1].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/king/King1.obj");
    listOfObjects[2].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/knight/Knight1.obj");
    listOfObjects[3].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/pawn/Pawn1.obj");
    listOfObjects[4].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/queen/Queen1.obj");
    listOfObjects[5].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/rook/Rook1.obj");
    // listOfObjects[6].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/Pawn_lucas.obj");
    listOfObjects[6].obj_loader("../../assets/texture/tintin.png", "../../assets/obj/chessboard/Chessboard.obj");
}

void Renderer3D::draw_chessboard()
{
    this->_shader.use();

    float tailleCase = 4.5;

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 1.f, 0.1f, 100.f);

    glm::mat4 MVMatrix = glm::rotate(glm::mat4(1), glm::radians(90.f), glm::vec3(1, 0, 0));
    MVMatrix           = glm::translate(MVMatrix, glm::vec3(0, 0, 1));
    MVMatrix           = glm::scale(MVMatrix, glm::vec3(1, 1, 0.2));

    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 MVPMatrix    = ProjMatrix * this->_trackballCamera.getViewMatrix() * MVMatrix;
    glm::vec4 Color        = glm::vec4(0.5, 0.2, 0, 1);

    this->_shader.set_uniform_matrix_4fv("uMVMatrix", MVMatrix);
    this->_shader.set_uniform_matrix_4fv("uNormalMatrix", NormalMatrix);
    this->_shader.set_uniform_matrix_4fv("uMVPMatrix", MVPMatrix);
    this->_shader.set_uniform_vector_4f("uColor", Color);

    glBindVertexArray(listOfObjects[6].getVAO()->getGLuint());
    glDrawArrays(GL_TRIANGLES, 0, listOfObjects[6].getVAO()->getSize());
    glBindVertexArray(0);

    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 1.f, 0.1f, 100.f);

            glm::mat4 MVMatrix = glm::rotate(glm::mat4(1), glm::radians(90.f), glm::vec3(1, 0, 0));                                            // Rotation
            MVMatrix           = glm::translate(MVMatrix, glm::vec3(x * tailleCase - 3.5 * tailleCase, y * tailleCase - 3.5 * tailleCase, 0)); // Translation
            MVMatrix           = glm::scale(MVMatrix, glm::vec3(0.1, 0.1, 0.1));                                                               // Scale

            glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            glm::mat4 MVPMatrix    = ProjMatrix * this->_trackballCamera.getViewMatrix() * MVMatrix;

            glm::vec4 Color = ((x + y) % 2 != 0) ? glm::vec4(0.8, 0.4, 0, 1) : glm::vec4(1, 0.7, 0, 1);

            this->_shader.set_uniform_matrix_4fv("uMVMatrix", MVMatrix);
            this->_shader.set_uniform_matrix_4fv("uNormalMatrix", NormalMatrix);
            this->_shader.set_uniform_matrix_4fv("uMVPMatrix", MVPMatrix);
            this->_shader.set_uniform_vector_4f("uColor", Color);

            glBindVertexArray(listOfObjects[6].getVAO()->getGLuint());
            glDrawArrays(GL_TRIANGLES, 0, listOfObjects[6].getVAO()->getSize());
            glBindVertexArray(0);
        }
    }
}

int Renderer3D::from_type_to_obj(PieceType type)
{
    switch (type)
    {
    case PieceType::BISHOP:
        return 0;
        break;
    case PieceType::KING:
        return 1;
        break;
    case PieceType::KNIGHT:
        return 2;
        break;
    case PieceType::PAWN:
        return 3;
        break;
    case PieceType::QUEEN:
        return 4;
        break;
    case PieceType::ROOK:
        return 5;
        break;
    default:
        std::cerr << "Erreur: from_type_to obj /n";
        return -1;
    }
}

void Renderer3D::draw_pieces(std::array<std::array<std::unique_ptr<Piece>, 8>, 8>* position_pieces)
{
    _trackballCamera.rotateLeft(0.1);

    float tailleCase = 4.5;

    for (int x{0}; x < 8; x++)
    {
        for (int y{0}; y < 8; y++)
        {
            if (position_pieces->at(x).at(y) != nullptr)
            {
                glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 1.f, 0.1f, 100.f);

                if (position_pieces->at(x).at(y)->get_color() == PieceColor::BLACK)
                {
                    // Rotation
                    glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(x * tailleCase - 3.5 * tailleCase, 0, y * tailleCase - 3.5 * tailleCase));
                    MVMatrix           = glm::scale(MVMatrix, glm::vec3(0.5, 0.5, 0.5));
                    MVMatrix           = glm::rotate(MVMatrix, glm::radians(-90.f), glm::vec3(0, 1, 0));

                    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
                    glm::mat4 MVPMatrix    = ProjMatrix * this->_trackballCamera.getViewMatrix() * MVMatrix;
                    glm::vec4 Color        = glm::vec4(1, 1, 1, 1);

                    this->_shader.set_uniform_matrix_4fv("uMVMatrix", MVMatrix);
                    this->_shader.set_uniform_matrix_4fv("uNormalMatrix", NormalMatrix);
                    this->_shader.set_uniform_matrix_4fv("uMVPMatrix", MVPMatrix);
                    this->_shader.set_uniform_vector_4f("uColor", Color);
                }
                else
                {
                    // Rotation
                    glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(x * tailleCase - 3.5 * tailleCase, 0, y * tailleCase - 3.5 * tailleCase));
                    MVMatrix           = glm::scale(MVMatrix, glm::vec3(0.5, 0.5, 0.5));
                    MVMatrix           = glm::rotate(MVMatrix, glm::radians(90.f), glm::vec3(0, 1, 0));

                    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
                    glm::mat4 MVPMatrix    = ProjMatrix * this->_trackballCamera.getViewMatrix() * MVMatrix;
                    glm::vec4 Color        = glm::vec4(0, 0, 0, 1);

                    this->_shader.set_uniform_matrix_4fv("uMVMatrix", MVMatrix);
                    this->_shader.set_uniform_matrix_4fv("uNormalMatrix", NormalMatrix);
                    this->_shader.set_uniform_matrix_4fv("uMVPMatrix", MVPMatrix);
                    this->_shader.set_uniform_vector_4f("uColor", Color);
                }

                int numberObj = from_type_to_obj(position_pieces->at(x).at(y)->get_type());
                glBindVertexArray(listOfObjects[numberObj].getVAO()->getGLuint());
                glDrawArrays(GL_TRIANGLES, 0, listOfObjects[numberObj].getVAO()->getSize());
                glBindVertexArray(0);
            }
        }
    }
}