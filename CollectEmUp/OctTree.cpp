#include "OctTree.h"

OctTree::OctTree( glm::vec3 center, glm::vec3 halfWidths )
{
    _root = new OctTreeNode( center, halfWidths );
}

OctTree::~OctTree()
{
    if( _root != nullptr )
    {
        delete _root;
    }
}

void OctTree::print()
{
    std::cout << "Collider Binary Tree: " << std::endl;
    _root->print();
}

void OctTree::draw()
{
    if( _root != nullptr )
    {
        _root->draw();
    }
}

bool OctTree::collidesWith( GameObject* other )
{
    if( _root == nullptr )
    {
        return false;
    }

    return _root->collidesWith( other );
}

void OctTree::add( GameObject* other )
{
    _root->add( other );
}

OctTreeNode* OctTree::getRoot()
{
    return _root;
}

void OctTree::checkCollisions()
{
	_root->checkCollisions();
}
void OctTree::checkCollisions(GameObject* other)
{
	_root->checkCollisions(other);
}