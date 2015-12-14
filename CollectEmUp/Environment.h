#pragma once

#include "GameObject.h"
#include "Random.h"
#include "ModelImporter.h"
#include "DisplayEvent.h"
#include "Camera.h"
#include "KeyboardMovableGO.h"
#include "OctTree.h"
#include "ExamplePrefabClass.h"
#include "BlockPlatform.h"
#include "Level1.h"

class Environment :
    public GameObject
{
public:
    Environment();
    virtual ~Environment();

    virtual void update( float dt );
    virtual void draw( float dt );

    virtual void addChild( GameObject* child );

    void turnCamera( float dx, float dy );
    void moveCamera( float dx, float dy, float dz );

    void movePlayer( glm::vec3 delta );

    void applyGravity();
    void applyDrag();

    void onRemoved( Event e );
    void onAdded( Event e );

private:
    static const glm::vec3& GRAVITY;
    static const float& DRAG;
    static const float& FRICTION;
    static const float& DEFLECT_PERCENTAGE;

	Level1* _lvl1;
    glm::mat4 _worldMatrix;
    Camera _camera;
    OctTree* _octTree;
    KeyboardMovableGO* _player;

    // Should be handled by something like a FollowingCamera
    float _turnAmount;
};

