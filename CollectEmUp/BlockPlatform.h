#pragma once

#include "GameObject.h"
#include "ModelImporter.h"
#include "ModelImportData.h"

class BlockPlatform :
	public GameObject
{
private:
public:
	BlockPlatform(vec3 position, vec3 scale);
	~BlockPlatform();

	virtual void update( float dt );
	virtual void draw(float dt);
};

