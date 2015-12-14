#include "OctTreeNode.h"

OctTreeNode::OctTreeNode( glm::vec3 center, glm::vec3 halfWidths )
{
    _boundingBox = new BoundingBox();
    _boundingBox->setCenter( center );
    _boundingBox->setHalfWidthX( halfWidths.x );
    _boundingBox->setHalfWidthY( halfWidths.y );
    _boundingBox->setHalfWidthZ( halfWidths.z );

    _containedBoundingBoxes = std::vector<BoundingBox*>( CAPACITY );
    _children = std::vector<OctTreeNode*>( CAPACITY );

    _count = 0;
    _isLeaf = true;

    for( int i = 0; i < CAPACITY; i++ )
    {
        _containedBoundingBoxes[i] = nullptr;
    }

    for( unsigned i = 0; i < _children.size(); i++ )
    {
        _children[i] = nullptr;
    }
}

OctTreeNode::~OctTreeNode()
{
    for( unsigned i = 0; i < _children.size(); i++ )
    {
        if( _children[i] != nullptr )
        {
            delete _children[i];
        }
    }
}

void OctTreeNode::print()
{
    std::cout << std::fixed << std::setprecision( 2 ) << "OctTreeNode: " << std::endl;
    std::cout << "Bounding Box:" << std::endl;
    _boundingBox->print();

    std::cout << std::endl;

    std::cout << "Colliders: " << _count << std::endl;

    for each( BoundingBox* boundingBox in _containedBoundingBoxes )
    {
        if( boundingBox != nullptr )
        {
            boundingBox->print();
        }
    }

    std::cout << std::endl;

    std::cout << "Children: " << std::endl;

    std::vector<std::string> nodeNames =
    {
        "Front Top Left Child",
        "Front Top Right Child",
        "Front Bottom Left Child",
        "Front Bottom Right Child",
        "Back Top Left Child",
        "Back Top Right Child",
        "Back Bottom Left Child",
        "Back Bottom Right Child"
    };

    for( unsigned i = 0; i < _children.size(); i++ )
    {
        OctTreeNode* child = _children[i];

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
    _boundingBox->draw();

    for each( BoundingBox* boundingBox in _containedBoundingBoxes )
    {
        if( boundingBox != nullptr )
        {
            boundingBox->draw();
        }
    }

    for each( OctTreeNode* child in _children )
    {
        if( child != nullptr )
        {
            child->draw();
        }
    }
}

bool OctTreeNode::collidesWith( BoundingBox* other )
{
    // Filter out colliders that don't hit the bounding box
    if( !_boundingBox->collidesWith( other ) )
    {
        return false;
    }

    // Check collisions vs each collider (leaf)
    if( isLeaf() )
    {
        for each( BoundingBox* boundingBox in _containedBoundingBoxes )
        {
            if( boundingBox != nullptr )
            {
                if( boundingBox->collidesWith( other ) )
                {
                    return true;
                }
            }
        }
    }

    // Check collisions with children (not a leaf)
    else
    {
        for( unsigned i = 0; i < _children.size(); i++ )
        {
            if( _children[i]->collidesWith( other ) )
            {
                return true;
            }
        }
    }

    return false;
}

void OctTreeNode::add( BoundingBox* other )
{
    // Filter out colliders that don't hit binary box
    if( !_boundingBox->collidesWith( other ) )
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
        _containedBoundingBoxes[_count] = other;
        _count++;
    }

    // Or add collider to its children (not a leaf)
    else
    {
        for( unsigned i = 0; i < _children.size(); i++ )
        {
            _children[i]->add( other );
        }
    }
}

void OctTreeNode::branch()
{
    // Set leaf = false
    _isLeaf = false;

    // Make child nodes
    float quarterWidthX = _boundingBox->getHalfWidthX() * 0.5f;
    float quarterWidthY = _boundingBox->getHalfWidthY() * 0.5f;
    float quarterWidthZ = _boundingBox->getHalfWidthZ() * 0.5f;
    glm::vec3 center = _boundingBox->getCenter();
    glm::vec3 quarterWidths = glm::vec3( quarterWidthX, quarterWidthY, quarterWidthZ );

    setFrontTopLeftChild( new OctTreeNode( center + glm::vec3( -quarterWidthX, quarterWidthY, quarterWidthZ ), quarterWidths ) );
    setFrontTopRightChild( new OctTreeNode( center + glm::vec3( quarterWidthX, quarterWidthY, quarterWidthZ ), quarterWidths ) );
    setFrontBottomLeftChild( new OctTreeNode( center + glm::vec3( -quarterWidthX, -quarterWidthY, quarterWidthZ ), quarterWidths ) );
    setFrontBottomRightChild( new OctTreeNode( center + glm::vec3( quarterWidthX, -quarterWidthY, quarterWidthZ ), quarterWidths ) );
    setBackTopLeftChild( new OctTreeNode( center + glm::vec3( -quarterWidthX, quarterWidthY, -quarterWidthZ ), quarterWidths ) );
    setBackTopRightChild( new OctTreeNode( center + glm::vec3( quarterWidthX, quarterWidthY, -quarterWidthZ ), quarterWidths ) );
    setBackBottomLeftChild( new OctTreeNode( center + glm::vec3( -quarterWidthX, -quarterWidthY, -quarterWidthZ ), quarterWidths ) );
    setBackBottomRightChild( new OctTreeNode( center + glm::vec3( quarterWidthX, -quarterWidthY, -quarterWidthZ ), quarterWidths ) );

    // Add this node's colliders to the children
    // Set this node's contained children to nullptr
    for( int i = 0; i < _count; i++ )
    {
        for( unsigned j = 0; j < _children.size(); j++ )
        {
            _children[j]->add( _containedBoundingBoxes[i] );
        }
    }

    for( int i = 0; i < _count; i++ )
    {
        _containedBoundingBoxes[i] = nullptr;
    }

    // Set count = 0
    _count = 0;
}

BoundingBox* OctTreeNode::getBoundingBox()
{
    return _boundingBox;
}

int OctTreeNode::getCount()
{
    return _count;
}

bool OctTreeNode::isLeaf()
{
    return _isLeaf;
}

std::vector<BoundingBox*> OctTreeNode::getContainedBoundingBoxes()
{
    return _containedBoundingBoxes;
}

OctTreeNode* OctTreeNode::getFrontTopLeftChild()
{
    return _children[0];
}
void OctTreeNode::setFrontTopLeftChild( OctTreeNode* value )
{
    _children[0] = value;
}

OctTreeNode* OctTreeNode::getFrontTopRightChild()
{
    return _children[1];
}
void OctTreeNode::setFrontTopRightChild( OctTreeNode* value )
{
    _children[1] = value;
}

OctTreeNode* OctTreeNode::getFrontBottomLeftChild()
{
    return _children[2];
}
void OctTreeNode::setFrontBottomLeftChild( OctTreeNode* value )
{
    _children[2] = value;
}

OctTreeNode* OctTreeNode::getFrontBottomRightChild()
{
    return _children[3];
}
void OctTreeNode::setFrontBottomRightChild( OctTreeNode* value )
{
    _children[3] = value;
}

OctTreeNode* OctTreeNode::getBackTopLeftChild()
{
    return _children[4];
}
void OctTreeNode::setBackTopLeftChild( OctTreeNode* value )
{
    _children[4] = value;
}

OctTreeNode* OctTreeNode::getBackTopRightChild()
{
    return _children[5];
}
void OctTreeNode::setBackTopRightChild( OctTreeNode* value )
{
    _children[5] = value;
}

OctTreeNode* OctTreeNode::getBackBottomLeftChild()
{
    return _children[6];
}
void OctTreeNode::setBackBottomLeftChild( OctTreeNode* value )
{
    _children[6] = value;
}

OctTreeNode* OctTreeNode::getBackBottomRightChild()
{
    return _children[7];
}
void OctTreeNode::setBackBottomRightChild( OctTreeNode* value )
{
    _children[7] = value;
}
