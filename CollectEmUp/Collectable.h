#pragma once

#include "GameObject.h"
#include "ModelImporter.h"
#include "ModelImportData.h"

class Collectable :
	public GameObject
{
public:
	Collectable(vec3 position, vec3 scale);
	~Collectable();

	virtual void update(float dt);
	virtual void draw(float dt);
};

