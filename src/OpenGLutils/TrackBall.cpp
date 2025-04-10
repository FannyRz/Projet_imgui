#include "TrackBall.hpp"
#include <glad/glad.h>
#include <glfw/src/internal.h>
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"

glm::mat4 TrackballCamera::get_viewMatrix() const
{
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -m_fDistance));
    viewMatrix           = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    viewMatrix           = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));
    return viewMatrix;
}

glm::vec3 TrackballCamera::get_position() const
{
    glm::vec4 position = glm::inverse(get_viewMatrix()) * glm::vec4(0, 0, 0, 1);
    return glm::vec3(position);
}

void TrackballCamera::move_front(float delta)
{
    m_fDistance += delta;
    m_fDistance = std::clamp(m_fDistance, 20.f, 70.f);
}

void TrackballCamera::rotate_up(float degrees)
{
    m_fAngleX += degrees;
    m_fAngleX = std::clamp(m_fAngleX, 5.f, 60.f);
}

void TrackballCamera::rotate_left(float degrees)
{
    m_fAngleY += degrees;
}

void TrackballCamera::handle_camera_input()
{
    static float lastFrame    = glfwGetTime();
    float        currentFrame = glfwGetTime();
    float        deltaTime    = currentFrame - lastFrame; // Temps écoulé entre deux frames
    lastFrame                 = currentFrame;

    // Variables pour la vitesse de déplacement et rotation
    float moveSpeed   = 50.0f * deltaTime;
    float rotateSpeed = 60.0f * deltaTime;

    // Déplacer la caméra en fonction des touches pressées
    if (keysDown.contains(GLFW_KEY_UP))
    {
        rotate_up(rotateSpeed); // Haut
    }
    if (keysDown.contains(GLFW_KEY_DOWN))
    {
        rotate_up(-rotateSpeed); // Bas
    }
    if (keysDown.contains(GLFW_KEY_LEFT))
    {
        rotate_left(-rotateSpeed); // Gauche
    }
    if (keysDown.contains(GLFW_KEY_RIGHT))
    {
        rotate_left(rotateSpeed); // Droite
    }
    if (keysDown.contains(GLFW_KEY_W))
    {
        move_front(-moveSpeed); // Avancer
    }
    if (keysDown.contains(GLFW_KEY_S))
    {
        move_front(moveSpeed); // Reculer
    }
}