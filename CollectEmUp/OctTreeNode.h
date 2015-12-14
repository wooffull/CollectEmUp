#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include "BoundingBox.h"

class OctTreeNode
{
public:
    const int& CAPACITY = 8;

    OctTreeNode( glm::vec3 center, glm::vec3 halfWidths );
    ~OctTreeNode();

    void print();
    void draw();
    bool collidesWith( BoundingBox* other );
    void add( BoundingBox* other );
    void branch();

    BoundingBox* getBoundingBox();
    int getCount();
    bool isLeaf();

    std::vector<BoundingBox*> getContainedBoundingBoxes();

    OctTreeNode* getFrontTopLeftChild();
    void setFrontTopLeftChild( OctTreeNode* value );

    OctTreeNode* getFrontTopRightChild();
    void setFrontTopRightChild( OctTreeNode* value );

    OctTreeNode* getFrontBottomLeftChild();
    void setFrontBottomLeftChild( OctTreeNode* value );

    OctTreeNode* getFrontBottomRightChild();
    void setFrontBottomRightChild( OctTreeNode* value );

    OctTreeNode* getBackTopLeftChild();
    void setBackTopLeftChild( OctTreeNode* value );

    OctTreeNode* getBackTopRightChild();
    void setBackTopRightChild( OctTreeNode* value );

    OctTreeNode* getBackBottomLeftChild();
    void setBackBottomLeftChild( OctTreeNode* value );

    OctTreeNode* getBackBottomRightChild();
    void setBackBottomRightChild( OctTreeNode* value );

private:
    BoundingBox* _boundingBox;
    int _count; // How many colliders?
    std::vector<BoundingBox*> _containedBoundingBoxes;
    bool _isLeaf;
    std::vector<OctTreeNode*> _children;
};

