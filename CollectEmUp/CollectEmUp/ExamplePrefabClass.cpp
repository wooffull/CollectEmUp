#include "ExamplePrefabClass.h"
#include "ModelImporter.h"
#include "ModelImportData.h"


ExamplePrefabClass::ExamplePrefabClass(const char* modelFilename) : GameObject()
{
	//Perhaps we should put this in GameObject? Having the ability to import and load a model just from its filename could be handy in the future.
	ModelImporter mImport;
	ModelImportData* miData = (ModelImportData*)(mImport.loadFromFile(modelFilename));
	setModel(new Model(miData->getVertices(), miData->getFaceVertexIndices()));
}

void ExamplePrefabClass::update(float dt)
{
	GameObject::update(dt);

	//Write prefab update code here.
	//Useful functions can be found in GameObject.h.
}

void ExamplePrefabClass::draw(float dt)
{
	GameObject::draw(dt);

	//Write prefab draw code here.
}

ExamplePrefabClass::~ExamplePrefabClass(void)
{
	GameObject::~GameObject();
}