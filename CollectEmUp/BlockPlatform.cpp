#include "BlockPlatform.h"

BlockPlatform::BlockPlatform(vec3 position, vec3 scale)
{
	ModelImporter modelImporter;
	setModel(modelImporter.loadModel("Models/cube.obj", "Models/cube-texture.png"));

	setPosition(position);
	setColor(0.5f, 0.3f, 0.5f);
	setScale(scale);
	setFixed(true);
}

BlockPlatform::~BlockPlatform()
{
}

void BlockPlatform::update(float dt)
{
	GameObject::update(dt);
}

void BlockPlatform::draw(float dt)
{
	GameObject::draw(dt);
}