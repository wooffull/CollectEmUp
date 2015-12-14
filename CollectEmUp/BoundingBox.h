#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glew.h>
#include <climits>
#include <iostream>

#include "Model.h"

class BoundingBox
{
public:
    BoundingBox();
    ~BoundingBox();

    void draw();

    glm::vec3 getCenter();
    void setCenter( glm::vec3 value );

    glm::vec3 getScale();
    void setScale( glm::vec3 value );

    void setRotation( float rotation, glm::vec3 rotationAxis = glm::vec3( 1, 0, 0 ) );
    void rotate( float rotation, glm::vec3 rotationAxis );

    void createFromModel( Model* model );

    bool collidesWith( BoundingBox* other );

    // x-, y-, and z- axis relative to the object's rotation in the world
    glm::vec3 getRelativeAxisX();
    glm::vec3 getRelativeAxisY();
    glm::vec3 getRelativeAxisZ();

    float getHalfWidthX();
    void setHalfWidthX( float value );
    float getHalfWidthY();
    void setHalfWidthY( float value );
    float getHalfWidthZ();
    void setHalfWidthZ( float value );

    void print();

private:
    glm::vec3 _center;
    glm::vec3 _scale;

    glm::vec3 _relativeAxisX;
    glm::vec3 _relativeAxisY;
    glm::vec3 _relativeAxisZ;

    float _halfWidthX;
    float _halfWidthY;
    float _halfWidthZ;
};

