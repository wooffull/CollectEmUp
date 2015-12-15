#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include "GameObject.h"
#include "BoundingBox.h"
#include "HandleCollision.h"

class OctTreeNode
{
public:
    const int& CAPACITY = 8;

    OctTreeNode( glm::vec3 center, glm::vec3 halfWidths );
    ~OctTreeNode();

    void print();
    void draw();
    bool collidesWith( GameObject* other );
    void add( GameObject* other );
    void branch();

	GameObject* getGameObject();
    int getCount();
    bool isLeaf();

    std::vector<GameObject*> getContainedChildren();

    OctTreeNode* getFrontTopLeftNode();
    void setFrontTopLeftNode( OctTreeNode* value );

    OctTreeNode* getFrontTopRightNode();
    void setFrontTopRightNode( OctTreeNode* value );

    OctTreeNode* getFrontBottomLeftNode();
    void setFrontBottomLeftNode( OctTreeNode* value );

    OctTreeNode* getFrontBottomRightNode();
    void setFrontBottomRightNode( OctTreeNode* value );

    OctTreeNode* getBackTopLeftNode();
    void setBackTopLeftNode( OctTreeNode* value );

    OctTreeNode* getBackTopRightNode();
    void setBackTopRightNode( OctTreeNode* value );

    OctTreeNode* getBackBottomLeftNode();
    void setBackBottomLeftNode( OctTreeNode* value );

    OctTreeNode* getBackBottomRightNode();
    void setBackBottomRightNode( OctTreeNode* value );

	void checkCollisions();
	void checkCollisions(GameObject* other);

private:
	GameObject* _gameObject;
    int _count; // How many colliders?
    std::vector<GameObject*> _containedChildren;
    bool _isLeaf;
    std::vector<OctTreeNode*> _nodes;
};

