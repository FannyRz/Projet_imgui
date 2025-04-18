#pragma once

#include <algorithm>
#include <unordered_set>
#include "glm/ext/matrix_float4x4.hpp"

class TrackballCamera {
private:
    float _fDistance;
    float _fAngleX;
    float _fAngleY;

    std::unordered_set<int> _keysDown;

public:
    TrackballCamera() = default;
    TrackballCamera(float distance, float angleX, float angleY)
        : _fDistance(distance), _fAngleX(angleX), _fAngleY(angleY) {};
    ~TrackballCamera() = default;

    void move_front(float delta);
    void rotate_left(float degrees);
    void rotate_up(float degrees);

    glm::mat4 get_viewMatrix() const;
    glm::vec3 get_position() const;

    void                     handle_camera_input();
    std::unordered_set<int>& get_keysDown()
    {
        return this->_keysDown;
    };
};