#pragma once

#include <unordered_set>
#include "glm/ext/matrix_float4x4.hpp"
#include <algorithm>

class TrackballCamera {
private:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

    std::unordered_set<int> keysDown;

public:
    TrackballCamera() = default;
    TrackballCamera(float distance, float angleX, float angleY)
        : m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY) {};
    ~TrackballCamera() = default;

    void moveFront(float delta)
    {
        m_fDistance += delta;
        m_fDistance = std::clamp(m_fDistance, 20.f, 70.f);
    }
    void rotateLeft(float degrees) { m_fAngleY += degrees; }
    void rotateUp(float degrees)
    {
        m_fAngleX += degrees;
        m_fAngleX = std::clamp(m_fAngleX, 5.f, 60.f);
    }

    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const;

    void                     HandleCameraInput();
    std::unordered_set<int>& get_keysDown() { return this->keysDown; };
};