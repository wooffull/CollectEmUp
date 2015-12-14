#pragma once

#include <iostream>
#include "OctTreeNode.h"
#include "BoundingBox.h"

class OctTree
{
public:
    OctTree( glm::vec3 center, glm::vec3 halfWidths );
    ~OctTree();

    void print();
    void draw();
    bool collidesWith( BoundingBox* otherColliderPtr );
    void add( BoundingBox* otherColliderPtr );

    OctTreeNode* getRoot();

private:
    OctTreeNode* _root;
};

