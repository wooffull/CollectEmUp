#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
    _scale = glm::vec3( 1, 1, 1 );
    _relativeAxisX = glm::vec3( 1, 0, 0 );
    _relativeAxisY = glm::vec3( 0, 1, 0 );
    _relativeAxisZ = glm::vec3( 0, 0, 1 );
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::draw()
{
    std::vector<glm::vec3> vertices;
    vertices.push_back( _center - _relativeAxisX * getHalfWidthX() + _relativeAxisY * getHalfWidthY() + _relativeAxisZ * getHalfWidthZ() );
    vertices.push_back( _center - _relativeAxisX * getHalfWidthX() + _relativeAxisY * getHalfWidthY() - _relativeAxisZ * getHalfWidthZ() );
    vertices.push_back( _center - _relativeAxisX * getHalfWidthX() - _relativeAxisY * getHalfWidthY() - _relativeAxisZ * getHalfWidthZ() );
    vertices.push_back( _center - _relativeAxisX * getHalfWidthX() - _relativeAxisY * getHalfWidthY() + _relativeAxisZ * getHalfWidthZ() );
    vertices.push_back( _center + _relativeAxisX * getHalfWidthX() + _relativeAxisY * getHalfWidthY() + _relativeAxisZ * getHalfWidthZ() );
    vertices.push_back( _center + _relativeAxisX * getHalfWidthX() + _relativeAxisY * getHalfWidthY() - _relativeAxisZ * getHalfWidthZ() );
    vertices.push_back( _center + _relativeAxisX * getHalfWidthX() - _relativeAxisY * getHalfWidthY() - _relativeAxisZ * getHalfWidthZ() );
    vertices.push_back( _center + _relativeAxisX * getHalfWidthX() - _relativeAxisY * getHalfWidthY() + _relativeAxisZ * getHalfWidthZ() );

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glBegin( GL_QUADS );
    glColor3f( 0.0, 1.0, 1.0 );

    glVertex3f( vertices[0].x, vertices[0].y, vertices[0].z );
    glVertex3f( vertices[1].x, vertices[1].y, vertices[1].z );
    glVertex3f( vertices[2].x, vertices[2].y, vertices[2].z );
    glVertex3f( vertices[3].x, vertices[3].y, vertices[3].z );

    glVertex3f( vertices[4].x, vertices[4].y, vertices[4].z );
    glVertex3f( vertices[5].x, vertices[5].y, vertices[5].z );
    glVertex3f( vertices[6].x, vertices[6].y, vertices[6].z );
    glVertex3f( vertices[7].x, vertices[7].y, vertices[7].z );

    glVertex3f( vertices[0].x, vertices[0].y, vertices[0].z );
    glVertex3f( vertices[3].x, vertices[3].y, vertices[3].z );
    glVertex3f( vertices[7].x, vertices[7].y, vertices[7].z );
    glVertex3f( vertices[4].x, vertices[4].y, vertices[4].z );

    glVertex3f( vertices[1].x, vertices[1].y, vertices[1].z );
    glVertex3f( vertices[2].x, vertices[2].y, vertices[2].z );
    glVertex3f( vertices[6].x, vertices[6].y, vertices[6].z );
    glVertex3f( vertices[5].x, vertices[5].y, vertices[5].z );

    glVertex3f( vertices[0].x, vertices[0].y, vertices[0].z );
    glVertex3f( vertices[1].x, vertices[1].y, vertices[1].z );
    glVertex3f( vertices[5].x, vertices[5].y, vertices[5].z );
    glVertex3f( vertices[4].x, vertices[4].y, vertices[4].z );

    glVertex3f( vertices[2].x, vertices[2].y, vertices[2].z );
    glVertex3f( vertices[3].x, vertices[3].y, vertices[3].z );
    glVertex3f( vertices[7].x, vertices[7].y, vertices[7].z );
    glVertex3f( vertices[6].x, vertices[6].y, vertices[6].z );

    glEnd();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

glm::vec3 BoundingBox::getCenter()
{
    return _center;
}
void BoundingBox::setCenter( glm::vec3 value )
{
    _center.x = value.x;
    _center.y = value.y;
    _center.z = value.z;
}

glm::vec3 BoundingBox::getScale()
{
    return _scale;
}
void BoundingBox::setScale( glm::vec3 value )
{
    _scale.x = value.x;
    _scale.y = value.y;
    _scale.z = value.z;
}

void BoundingBox::setRotation( float rotation, glm::vec3 rotationAxis )
{
    glm::quat rotationQuaternion = glm::angleAxis( rotation, rotationAxis );
    rotationQuaternion = glm::normalize( rotationQuaternion );

    _relativeAxisX = rotationQuaternion * glm::vec3( 1, 0, 0 );
    _relativeAxisY = rotationQuaternion * glm::vec3( 0, 1, 0 );
    _relativeAxisZ = rotationQuaternion * glm::vec3( 0, 0, 1 );

    _relativeAxisX = glm::normalize( _relativeAxisX );
    _relativeAxisY = glm::normalize( _relativeAxisY );
    _relativeAxisZ = glm::normalize( _relativeAxisZ );
}

void BoundingBox::rotate( float rotation, glm::vec3 rotationAxis )
{
    glm::quat rotationQuaternion = glm::angleAxis( rotation, rotationAxis );
    rotationQuaternion = glm::normalize( rotationQuaternion );

    _relativeAxisX = rotationQuaternion * _relativeAxisX;
    _relativeAxisY = rotationQuaternion * _relativeAxisY;
    _relativeAxisZ = rotationQuaternion * _relativeAxisZ;

    _relativeAxisX = glm::normalize( _relativeAxisX );
    _relativeAxisY = glm::normalize( _relativeAxisY );
    _relativeAxisZ = glm::normalize( _relativeAxisZ );
}

void BoundingBox::createFromModel( Model* model )
{
    glm::vec3 min;
    glm::vec3 max;

    min.x = model->getVertexBufferData()[0];
    min.y = model->getVertexBufferData()[1];
    min.z = model->getVertexBufferData()[2];
    max.x = model->getVertexBufferData()[0];
    max.y = model->getVertexBufferData()[1];
    max.z = model->getVertexBufferData()[2];

    for( GLuint i = 8; i < model->getVertexBufferData().size(); i += 8 )
    {
        // Calculate whether the current X is greater than maxX or less than minX
        GLfloat tempX = model->getVertexBufferData()[i];
        if( tempX > max.x )
        {
            max.x = tempX;
        }
        else if( tempX < min.x )
        {
            min.x = tempX;
        }

        // Calculate whether the current Y is greater than maxY or less than minY
        GLfloat tempY = model->getVertexBufferData()[i + 1];
        if( tempY > max.y )
        {
            max.y = tempY;
        }
        else if( tempY < min.y )
        {
            min.y = tempY;
        }

        // Calculate whether the current Z is greater than maxZ or less than minZ
        GLfloat tempZ = model->getVertexBufferData()[i + 2];
        if( tempZ > max.z )
        {
            max.z = tempZ;
        }
        else if( tempZ < min.z )
        {
            min.z = tempZ;
        }
    }

    _halfWidthX = 0.5f * ( max.x - min.x );
    _halfWidthY = 0.5f * ( max.y - min.y );
    _halfWidthZ = 0.5f * ( max.z - min.z );
}

bool BoundingBox::collidesWith( BoundingBox* other )
{
    // 3 directional vectors for this bounding box
    glm::vec3 au1 = getRelativeAxisX();
    glm::vec3 au2 = getRelativeAxisY();
    glm::vec3 au3 = getRelativeAxisZ();

    // 3 directional vectors for the other bounding box
    glm::vec3 bu1 = other->getRelativeAxisX();
    glm::vec3 bu2 = other->getRelativeAxisY();
    glm::vec3 bu3 = other->getRelativeAxisZ();

    // t = center displacement
    glm::vec3 t = other->getCenter() - this->getCenter();

    // Get the 15 axes for testing
    std::vector<glm::vec3> axes = std::vector<glm::vec3>( 15 );
    axes.push_back( au1 );
    axes.push_back( au2 );
    axes.push_back( au3 );
    axes.push_back( bu1 );
    axes.push_back( bu2 );
    axes.push_back( bu3 );
    axes.push_back( glm::cross( au1, bu1 ) );
    axes.push_back( glm::cross( au1, bu2 ) );
    axes.push_back( glm::cross( au1, bu3 ) );
    axes.push_back( glm::cross( au2, bu1 ) );
    axes.push_back( glm::cross( au2, bu2 ) );
    axes.push_back( glm::cross( au2, bu3 ) );
    axes.push_back( glm::cross( au3, bu1 ) );
    axes.push_back( glm::cross( au3, bu2 ) );
    axes.push_back( glm::cross( au3, bu3 ) );

    // 4 possible radii displacements for this bounding box
    glm::vec3 ar1 = getHalfWidthX() * getRelativeAxisX() + getHalfWidthY() * getRelativeAxisY() + getHalfWidthZ() * getRelativeAxisZ();
    glm::vec3 ar2 = getHalfWidthX() * getRelativeAxisX() + getHalfWidthY() * getRelativeAxisY() - getHalfWidthZ() * getRelativeAxisZ();
    glm::vec3 ar3 = getHalfWidthX() * getRelativeAxisX() - getHalfWidthY() * getRelativeAxisY() + getHalfWidthZ() * getRelativeAxisZ();
    glm::vec3 ar4 = getHalfWidthX() * getRelativeAxisX() - getHalfWidthY() * getRelativeAxisY() - getHalfWidthZ() * getRelativeAxisZ();

    // 4 possible radii displacements for the other bounding box
    glm::vec3 br1 = other->getHalfWidthX() * other->getRelativeAxisX() + other->getHalfWidthY() * other->getRelativeAxisY() + other->getHalfWidthZ() * other->getRelativeAxisZ();
    glm::vec3 br2 = other->getHalfWidthX() * other->getRelativeAxisX() + other->getHalfWidthY() * other->getRelativeAxisY() - other->getHalfWidthZ() * other->getRelativeAxisZ();
    glm::vec3 br3 = other->getHalfWidthX() * other->getRelativeAxisX() - other->getHalfWidthY() * other->getRelativeAxisY() + other->getHalfWidthZ() * other->getRelativeAxisZ();
    glm::vec3 br4 = other->getHalfWidthX() * other->getRelativeAxisX() - other->getHalfWidthY() * other->getRelativeAxisY() - other->getHalfWidthZ() * other->getRelativeAxisZ();

    using namespace glm;

    for( unsigned int i = 0; i < axes.size(); i++ )
    {
        vec3 l = axes[i];

        // Get max dot( ar, l )
        float dotA = fabsf( dot( ar1, l ) );
        dotA = fmaxf( dotA, fabsf( dot( ar2, l ) ) );
        dotA = fmaxf( dotA, fabsf( dot( ar3, l ) ) );
        dotA = fmaxf( dotA, fabsf( dot( ar4, l ) ) );

        // Get max dot( br, l )
        float dotB = fabsf( dot( br1, l ) );
        dotB = fmaxf( dotB, fabsf( dot( br2, l ) ) );
        dotB = fmaxf( dotB, fabsf( dot( br3, l ) ) );
        dotB = fmaxf( dotB, fabsf( dot( br4, l ) ) );

        float left = fabsf( dot( t, l ) );
        float right = dotA + dotB;

        if( left > right )
        {
            return false;
        }
    }

    return true;
}

glm::vec3 BoundingBox::getRelativeAxisX()
{
    return _relativeAxisX;
}
glm::vec3 BoundingBox::getRelativeAxisY()
{
    return _relativeAxisY;
}
glm::vec3 BoundingBox::getRelativeAxisZ()
{
    return _relativeAxisZ;
}

float BoundingBox::getHalfWidthX()
{
    return _halfWidthX * _scale.x;
}
void BoundingBox::setHalfWidthX( float value )
{
    _halfWidthX = value;
}

float BoundingBox::getHalfWidthY()
{
    return _halfWidthY * _scale.y;
}
void BoundingBox::setHalfWidthY( float value )
{
    _halfWidthY = value;
}

float BoundingBox::getHalfWidthZ()
{
    return _halfWidthZ * _scale.z;
}
void BoundingBox::setHalfWidthZ( float value )
{
    _halfWidthZ = value;
}

void BoundingBox::print()
{
    glm::vec3 u0 = getRelativeAxisX();
    glm::vec3 u1 = getRelativeAxisY();
    glm::vec3 u2 = getRelativeAxisZ();
    glm::vec3 halfWidth = glm::vec3( getHalfWidthX(), getHalfWidthY(), getHalfWidthZ() );

    std::cout << "Center:\t\t\t" << "(" << _center.x << ", " << _center.y << ", " << _center.z << ")" << std::endl;
    std::cout << "Axis u0:\t\t" << "(" << u0.x << ", " << u0.y << ", " << u0.z << ")" << std::endl;
    std::cout << "Axis u1:\t\t" << "(" << u1.x << ", " << u1.y << ", " << u1.z << ")" << std::endl;
    std::cout << "Axis u2:\t\t" << "(" << u2.x << ", " << u2.y << ", " << u2.z << ")" << std::endl;
    std::cout << "Half Widths:\t\t" << "(" << halfWidth.x << ", " << halfWidth.y << ", " << halfWidth.z << ")" << std::endl;
    std::cout << std::endl;
}
