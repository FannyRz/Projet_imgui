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

void Renderer3D::render_board(ChessBoard& _chessboard)
{
    _chessboard.draw_board();
}

// void Renderer3D::button_action()
// {
//     if (glfwGetKey(manager.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
//     this->_trackballCamera.rotateLeft(0.8);

//   if (glfwGetKey(manager.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
//     this->_trackballCamera.rotateLeft(-0.8);

//   if (glfwGetKey(manager.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
//     this->_trackballCamera.rotateUp(-0.8);

//   if (glfwGetKey(manager.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
//     this->_trackballCamera.rotateUp(0.8);

//   if (glfwGetKey(manager.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
//     this->_trackballCamera.moveFront(-0.5);

//   if (glfwGetKey(manager.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
//     this->_trackballCamera.moveFront(0.5);
// }

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

    glm::mat4 MVMatrix = glm::rotate(glm::mat4(1), glm::radians(90.f), glm::vec3(1, 0, 0)); // Rotation
    MVMatrix           = glm::translate(MVMatrix, glm::vec3(0, 0, 1.3));                      // Translation
    MVMatrix           = glm::scale(MVMatrix, glm::vec3(1, 1, 0.2));                        // Scale

    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 MVPMatrix    = ProjMatrix * this->_trackballCamera.getViewMatrix() * MVMatrix;
    glm::vec4 Color        = glm::vec4(1, 0, 0, 1);

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

            glm::mat4 MVMatrix = glm::rotate(glm::mat4(1), glm::radians(90.f), glm::vec3(1, 0, 0));                                        // Rotation
            MVMatrix           = glm::translate(MVMatrix, glm::vec3(x * tailleCase - 3.5 * tailleCase, y * tailleCase - 3.5 * tailleCase, 0)); // Translation
            MVMatrix           = glm::scale(MVMatrix, glm::vec3(0.1, 0.1, 0.1));                                                           // Scale

            glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            glm::mat4 MVPMatrix    = ProjMatrix * this->_trackballCamera.getViewMatrix() * MVMatrix;
            glm::vec4 Color        = glm::vec4(1, 0, 0, 1);

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

void Renderer3D::draw_pieces(int x, int y)
{
    _trackballCamera.rotateLeft(0.1);
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 1.f, 0.1f, 100.f);

    // glm::mat4 MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, -5)); // Translation
    // glm::mat4 MVMatrix          = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); // Rotation
    glm::mat4 MVMatrix = glm::scale(glm::mat4(1), glm::vec3(0.5, 0.5, 0.5)); // Scale

    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 MVPMatrix    = ProjMatrix * this->_trackballCamera.getViewMatrix() * MVMatrix;
    glm::vec4 Color        = glm::vec4(1, 0, 0, 1);

    this->_shader.set_uniform_matrix_4fv("uMVMatrix", MVMatrix);
    this->_shader.set_uniform_matrix_4fv("uNormalMatrix", NormalMatrix);
    this->_shader.set_uniform_matrix_4fv("uMVPMatrix", MVPMatrix);
    this->_shader.set_uniform_vector_4f("uColor", Color);

    glBindVertexArray(listOfObjects[1].getVAO()->getGLuint());
    glDrawArrays(GL_TRIANGLES, 0, listOfObjects[1].getVAO()->getSize());
    glBindVertexArray(0);
}