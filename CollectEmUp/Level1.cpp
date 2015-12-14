#include "Level1.h"

Level1::Level1()
{
	//objects for level 1
	#pragma region All Game Objects
	#pragma region Platforms
	//INTRO
	_levelObjects.push_back(new BlockPlatform(vec3(0.00, 0.00, 0.00), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(0.00, 1.50, 4.00), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(0.00, 3.00, 8.00), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(0.00, 4.50, 12.00), vec3(15.00, 0.30, 3.50)));
	//LEFTWARD LONG JUMPING AREA
	_levelObjects.push_back(new BlockPlatform(vec3(5.00, 4.50, 17.50), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(12.00, 4.50, 17.50), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(12.00, 4.50, 24.50), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(19.00, 4.50, 24.50), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(19.00, 4.50, 31.50), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(26.00, 4.50, 31.50), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(26.00, 4.50, 38.50), vec3(5.00, 0.30, 3.50)));
	//RIGHTWARD HIGH JUMPING AREA
	_levelObjects.push_back(new BlockPlatform(vec3(-5.00, 7.00, 16.00), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(-5.00, 9.50, 20.00), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(-5.00, 12.00, 24.00), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(-5.00, 14.50, 28.00), vec3(5.00, 0.30, 3.50)));
	_levelObjects.push_back(new BlockPlatform(vec3(-5.00, 17.00, 32.00), vec3(5.00, 0.30, 3.50)));
	#pragma endregion
	#pragma region Collectables
	_levelObjects.push_back(new Collectable(vec3(0.00, 5.50, 12.00), vec3(0.2,0.2,0.2))); // first collectable
	_levelObjects.push_back(new Collectable(vec3(26.00, 5.50, 38.50), vec3(0.2, 0.2, 0.2))); // left collectable
	_levelObjects.push_back(new Collectable(vec3(-5.00, 18.00, 32.00), vec3(0.2, 0.2, 0.2))); // right collectable
#pragma endregion
	#pragma endregion
}

Level1::~Level1()
{
	for (size_t i = 0; i < _levelObjects.size(); ++i)
	{
		delete _levelObjects[i];
	}
}

std::vector<GameObject*> Level1::getLevelObjects()
{
	return _levelObjects;
}
