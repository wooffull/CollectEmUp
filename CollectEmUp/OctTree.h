#pragma once

#include <iostream>
#include "OctTreeNode.h"
#include "GameObject.h"

class OctTree
{
public:
    OctTree( glm::vec3 center, glm::vec3 halfWidths );
    ~OctTree();

    void print();
    void draw();
    bool collidesWith( GameObject* otherColliderPtr );
	void checkCollisions();
    void add( GameObject* otherColliderPtr );

    OctTreeNode* getRoot();

private:
    OctTreeNode* _root;
};

