#include "Camera.h"

//In the future, handle sensitivity in the input methods. Having dx and dy in turn be an accurate reflection of the degrees that will be turned is important.
const float& Camera::TURN_SENSITIVITY_Y = 1.0f;//0.025f;
const float& Camera::TURN_SENSITIVITY_X = 1.0f;// 0.025f;

Camera::Camera() :
    GameObject()
{
    _yaw = 0;
    _pitch = 0;
    setFixed( false );
}

Camera::~Camera()
{
}

void Camera::turn( float dx, float dy )
{
    float pi = glm::pi<float>();

    _yaw += dx * TURN_SENSITIVITY_X;
    _pitch += dy * TURN_SENSITIVITY_Y;

    // Clamp the pitch value to be from -PI/2 to PI/2
    _pitch = glm::clamp<float>( _pitch, -pi * 0.5f, pi * 0.5f );

    // Wrap the yaw value to be from -PI to PI
    while( _yaw > 2.0f * pi )
    {
        _yaw -= 2.0f * pi;
    }
    while( _yaw < 0 )
    {
        _yaw += 2.0f * pi;
    }
}

glm::vec3 Camera::getForward()
{
    glm::vec3 forward;
    forward.x = sin( _yaw ) * cos( _pitch );
    forward.y = sin( _pitch );
    forward.z = -cos( _yaw ) * cos( _pitch );
    return forward;
}

glm::vec3 Camera::getRight()
{
    glm::vec3 right = glm::cross<float, glm::highp>( getUp(), getForward() );
    return right;
}

glm::vec3 Camera::getUp()
{
    float pi = glm::pi<float>();

    glm::vec3 up;
    up.x = sin( _yaw ) * cos( _pitch + pi * 0.5f );
    up.y = sin( _pitch + pi * 0.5f );
    up.z = -cos( _yaw ) * cos( _pitch + pi * 0.5f );
    return up;
}

glm::vec3 Camera::getLookAt()
{
    glm::vec3 lookAt = getPosition() + getForward();
    return lookAt;
}