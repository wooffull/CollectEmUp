#pragma once

#include "GameObject.h"

class Camera :
    public GameObject
{
public:
    Camera();
    virtual ~Camera();

    void turn( float dx, float dy );

    glm::vec3 getForward();
    glm::vec3 getRight();
    glm::vec3 getUp();
    glm::vec3 getLookAt();

private:
    static const float& TURN_SENSITIVITY_X;
    static const float& TURN_SENSITIVITY_Y;

    float _yaw;
    float _pitch;
};

