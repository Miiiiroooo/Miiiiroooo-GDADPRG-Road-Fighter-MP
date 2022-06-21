#include "stdafx.h"
#include "AScene.h"
#include "GameObjectManager.h"


// constructor and destructor of the AScene Class
AScene::AScene(std::string sceneName)
{
	this->sceneName = sceneName;
}


AScene::~AScene()
{

}

// public methods of the AScene Class
void AScene::onUnloadObjects()
{
	GameObjectManager::getInstance()->deleteAllObjectsInScene();
}


std::string AScene::getSceneName()
{
	return this->sceneName;
}


// protected methods of the AScene Class
void AScene::registerObject(AGameObject* object)
{
	GameObjectManager::getInstance()->addObject(object);
}