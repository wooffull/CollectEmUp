#include "OctTreeNode.h"

OctTreeNode::OctTreeNode( glm::vec3 center, glm::vec3 halfWidths )
{
    _gameObject = new GameObject();
    _gameObject->setPosition( center );

    BoundingBox* nodeBox = _gameObject->getBoundingBox();
    nodeBox->setCenter( center );
    nodeBox->setHalfWidthX( halfWidths.x );
    nodeBox->setHalfWidthY( halfWidths.y );
    nodeBox->setHalfWidthZ( halfWidths.z );

    _containedChildren = std::vector<GameObject*>( CAPACITY );
    _nodes = std::vector<OctTreeNode*>( CAPACITY );

    _count = 0;
    _isLeaf = true;

    for( int i = 0; i < CAPACITY; i++ )
    {
        _containedChildren[i] = nullptr;
    }

    for( unsigned i = 0; i < _nodes.size(); i++ )
    {
        _nodes[i] = nullptr;
    }
}

OctTreeNode::~OctTreeNode()
{
    for( unsigned i = 0; i < _nodes.size(); i++ )
    {
        if( _nodes[i] != nullptr )
        {
            delete _nodes[i];
        }
    }

    delete _gameObject;
}

void OctTreeNode::print()
{
    std::cout << std::fixed << std::setprecision( 2 ) << "OctTreeNode: " << std::endl;
    std::cout << "Bounding Box:" << std::endl;
    _gameObject->getBoundingBox()->print();

    std::cout << std::endl;

    std::cout << "Colliders: " << _count << std::endl;

    for each( GameObject* child in _containedChildren )
    {
        if( child != nullptr )
        {
            child->getBoundingBox()->print();
        }
    }

    std::cout << std::endl;

    std::cout << "Nodes: " << std::endl;

    std::vector<std::string> nodeNames =
    {
        "Front Top Left Node",
        "Front Top Right Node",
        "Front Bottom Left Node",
        "Front Bottom Right Node",
        "Back Top Left Node",
        "Back Top Right Node",
        "Back Bottom Left Node",
        "Back Bottom Right Node"
    };

    for( unsigned i = 0; i < _nodes.size(); i++ )
    {
        OctTreeNode* child = _nodes[i];

        if( child == nullptr )
        {
            std::cout << nodeNames[i].c_str() << " = nullptr" << std::endl;
        }
        else
        {
            std::cout << nodeNames[i].c_str() << ":" << std::endl;
            child->print();
        }
    }

    std::cout << std::endl;
}

void OctTreeNode::draw()
{
    _gameObject->getBoundingBox()->draw();

    for each( GameObject* child in _containedChildren )
    {
        if( child != nullptr )
        {
            BoundingBox* childBox = child->getBoundingBox();

            childBox->draw();
        }
    }

    for each( OctTreeNode* child in _nodes )
    {
        if( child != nullptr )
        {
            child->draw();
        }
    }
}

bool OctTreeNode::collidesWith( GameObject* other )
{
    // Filter out colliders that don't hit the bounding box
    if( !_gameObject->collidesWith( other ) )
    {
        return false;
    }

    // Check collisions vs each collider (leaf)
    if( isLeaf() )
    {
        for each( GameObject* child in _containedChildren )
        {
            if( child != nullptr )
            {
                if( child->collidesWith( other ) )
                {
                    return true;
                }
            }
        }
    }

    // Check collisions with children (not a leaf)
    else
    {
        for( unsigned i = 0; i < _nodes.size(); i++ )
        {
            if( _nodes[i]->collidesWith( other ) )
            {
                return true;
            }
        }
    }

    return false;
}

void OctTreeNode::checkCollisions()
{
    if( isLeaf() )
    {
        for( unsigned int i = 0; i < _containedChildren.size(); i++ )
        {
            if( _containedChildren[i] == nullptr )
            {
                continue;
            }

            for( unsigned int j = i + 1; j < _containedChildren.size(); j++ )
            {
                if( _containedChildren[j] == nullptr )
                {
                    continue;
                }

                if( _containedChildren[i]->collidesWith( _containedChildren[j] ) )
                {
                    //Collision detected b/w i & j.
                    handleCollision( _containedChildren[i], _containedChildren[j] );
                    handleCollision( _containedChildren[j], _containedChildren[i] );
                }
            }
        }
    }
    else
    {
        for( unsigned int i = 0; i < _nodes.size(); i++ )
        {
            _nodes[i]->checkCollisions();
        }
    }
}

void OctTreeNode::checkCollisions( GameObject* other )
{
    if( isLeaf() )
    {
        for( unsigned int i = 0; i < _containedChildren.size(); i++ )
        {
            if( _containedChildren[i] == nullptr && _containedChildren[i] != other )
            {
                continue;
            }

            if( _containedChildren[i]->collidesWith( other ) )
            {
                handleCollision( _containedChildren[i], other );
                handleCollision( other, _containedChildren[i] );
            }
        }
    }
    else
    {
        for( unsigned int i = 0; i < _nodes.size(); i++ )
        {
            GameObject* nodeGameObject = _nodes[i]->getGameObject();

            if( nodeGameObject->collidesWith( other ) )
            {
                _nodes[i]->checkCollisions( other );
            }
        }
    }
}

void OctTreeNode::add( GameObject* other )
{
    // Filter out colliders that don't hit binary box
    if( !_gameObject->collidesWith( other ) )
    {
        return;
    }

    // Branch if needed
    if( _count + 1 > CAPACITY )
    {
        branch();
    }

    // Add collider to this node (leaf) and increment count
    if( isLeaf() )
    {
        _containedChildren[_count] = other;
        _count++;
    }

    // Or add collider to its children (not a leaf)
    else
    {
        for( unsigned i = 0; i < _nodes.size(); i++ )
        {
            _nodes[i]->add( other );
        }
    }
}

void OctTreeNode::branch()
{
    BoundingBox* nodeBox = _gameObject->getBoundingBox();

    // Set leaf = false
    _isLeaf = false;

    // Make child nodes
    float quarterWidthX = nodeBox->getHalfWidthX() * 0.5f;
    float quarterWidthY = nodeBox->getHalfWidthY() * 0.5f;
    float quarterWidthZ = nodeBox->getHalfWidthZ() * 0.5f;
    glm::vec3 center = nodeBox->getCenter();
    glm::vec3 quarterWidths = glm::vec3( quarterWidthX, quarterWidthY, quarterWidthZ );

    setFrontTopLeftNode( new OctTreeNode( center + glm::vec3( -quarterWidthX, quarterWidthY, quarterWidthZ ), quarterWidths ) );
    setFrontTopRightNode( new OctTreeNode( center + glm::vec3( quarterWidthX, quarterWidthY, quarterWidthZ ), quarterWidths ) );
    setFrontBottomLeftNode( new OctTreeNode( center + glm::vec3( -quarterWidthX, -quarterWidthY, quarterWidthZ ), quarterWidths ) );
    setFrontBottomRightNode( new OctTreeNode( center + glm::vec3( quarterWidthX, -quarterWidthY, quarterWidthZ ), quarterWidths ) );
    setBackTopLeftNode( new OctTreeNode( center + glm::vec3( -quarterWidthX, quarterWidthY, -quarterWidthZ ), quarterWidths ) );
    setBackTopRightNode( new OctTreeNode( center + glm::vec3( quarterWidthX, quarterWidthY, -quarterWidthZ ), quarterWidths ) );
    setBackBottomLeftNode( new OctTreeNode( center + glm::vec3( -quarterWidthX, -quarterWidthY, -quarterWidthZ ), quarterWidths ) );
    setBackBottomRightNode( new OctTreeNode( center + glm::vec3( quarterWidthX, -quarterWidthY, -quarterWidthZ ), quarterWidths ) );

    // Add this node's colliders to the children
    // Set this node's contained children to nullptr
    for( int i = 0; i < _count; i++ )
    {
        for( unsigned j = 0; j < _nodes.size(); j++ )
        {
            _nodes[j]->add( _containedChildren[i] );
        }
    }

    for( int i = 0; i < _count; i++ )
    {
        _containedChildren[i] = nullptr;
    }

    // Set count = 0
    _count = 0;
}

GameObject* OctTreeNode::getGameObject()
{
    return _gameObject;
}

int OctTreeNode::getCount()
{
    return _count;
}

bool OctTreeNode::isLeaf()
{
    return _isLeaf;
}

std::vector<GameObject*> OctTreeNode::getContainedChildren()
{
    return _containedChildren;
}

OctTreeNode* OctTreeNode::getFrontTopLeftNode()
{
    return _nodes[0];
}
void OctTreeNode::setFrontTopLeftNode( OctTreeNode* value )
{
    _nodes[0] = value;
}

OctTreeNode* OctTreeNode::getFrontTopRightNode()
{
    return _nodes[1];
}
void OctTreeNode::setFrontTopRightNode( OctTreeNode* value )
{
    _nodes[1] = value;
}

OctTreeNode* OctTreeNode::getFrontBottomLeftNode()
{
    return _nodes[2];
}
void OctTreeNode::setFrontBottomLeftNode( OctTreeNode* value )
{
    _nodes[2] = value;
}

OctTreeNode* OctTreeNode::getFrontBottomRightNode()
{
    return _nodes[3];
}
void OctTreeNode::setFrontBottomRightNode( OctTreeNode* value )
{
    _nodes[3] = value;
}

OctTreeNode* OctTreeNode::getBackTopLeftNode()
{
    return _nodes[4];
}
void OctTreeNode::setBackTopLeftNode( OctTreeNode* value )
{
    _nodes[4] = value;
}

OctTreeNode* OctTreeNode::getBackTopRightNode()
{
    return _nodes[5];
}
void OctTreeNode::setBackTopRightNode( OctTreeNode* value )
{
    _nodes[5] = value;
}

OctTreeNode* OctTreeNode::getBackBottomLeftNode()
{
    return _nodes[6];
}
void OctTreeNode::setBackBottomLeftNode( OctTreeNode* value )
{
    _nodes[6] = value;
}

OctTreeNode* OctTreeNode::getBackBottomRightNode()
{
    return _nodes[7];
}
void OctTreeNode::setBackBottomRightNode( OctTreeNode* value )
{
    _nodes[7] = value;
}
