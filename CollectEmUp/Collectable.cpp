#include "Collectable.h"

Collectable::Collectable(vec3 position, vec3 scale)
{
	ModelImporter modelImporter;
	setModel(modelImporter.loadModel("Models/bolt.obj", "Models/Textures/nut-texture.png"));

	setPosition(position);
	setScale(scale);
	setFixed(true);

	setGameObjType("Collectable");
}

Collectable::~Collectable()
{
}

void Collectable::update(float dt)
{
	GameObject::update(dt);
}

void Collectable::draw(float dt)
{
	GameObject::draw(dt);
}