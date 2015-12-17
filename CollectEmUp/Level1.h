#pragma once

#include "BlockPlatform.h"
#include "Collectable.h"
#include "ExamplePrefabClass.h"

class Level1
{
public:
	Level1();
	~Level1();
	std::vector<GameObject*> getLevelObjects();

private:
	std::vector<GameObject*> _levelObjects;
};