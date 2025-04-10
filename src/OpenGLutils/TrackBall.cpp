#include "TrackBall.hpp"
#include <glad/glad.h>
#include <glfw/src/internal.h>
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"

glm::mat4 TrackballCamera::getViewMatrix() const
{
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -m_fDistance));
    viewMatrix           = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    viewMatrix           = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));
    return viewMatrix;
}

glm::vec3 TrackballCamera::getPosition() const
{
    glm::vec4 position = glm::inverse(getViewMatrix()) * glm::vec4(0, 0, 0, 1);
    return glm::vec3(position);
}

void TrackballCamera::HandleCameraInput()
{
    static float lastFrame    = glfwGetTime();
    float        currentFrame = glfwGetTime();
    float        deltaTime    = currentFrame - lastFrame; // Temps écoulé entre deux frames
    lastFrame                 = currentFrame;

    // Variables pour la vitesse de déplacement et rotation
    float moveSpeed     = 50.0f * deltaTime;
    float rotateSpeed   = 60.0f * deltaTime;

    // Déplacer la caméra en fonction des touches pressées
    if (keysDown.contains(GLFW_KEY_UP))
    {
        rotateUp(rotateSpeed); // Haut
    }
    if (keysDown.contains(GLFW_KEY_DOWN))
    {
        rotateUp(-rotateSpeed); // Bas
    }
    if (keysDown.contains(GLFW_KEY_LEFT))
    {
        rotateLeft(-rotateSpeed); // Gauche
    }
    if (keysDown.contains(GLFW_KEY_RIGHT))
    {
        rotateLeft(rotateSpeed); // Droite
    }
    if (keysDown.contains(GLFW_KEY_W))
    {
        moveFront(-moveSpeed); // Avancer
    }
    if (keysDown.contains(GLFW_KEY_S))
    {
        moveFront(moveSpeed); // Reculer
    }
}