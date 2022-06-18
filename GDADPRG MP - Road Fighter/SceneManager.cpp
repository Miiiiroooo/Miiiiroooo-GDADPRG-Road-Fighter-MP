#include "stdafx.h"
#include "SceneManager.h"


// static declarations of the SceneManager Class
std::string SceneManager::MAIN_MENU_SCREEN_NAME = "MainMenuScreen";

SceneManager* SceneManager::sharedInstance = NULL;

SceneManager* SceneManager::getInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new SceneManager();

	return sharedInstance;
}


// public methods of the SceneManager Class
void SceneManager::resgiterScene(AScene* scene)
{
	this->storedScenes[scene->getSceneName()] = scene;
}


void SceneManager::loadScene(std::string sceneName)
{
	this->isLoading = true;
	this->toLoadScene = sceneName;

	// loading screen
}


void SceneManager::unloadScene()
{
	if (this->activeScene != NULL)
	{
		this->activeScene->onUnloadObjects();
		this->activeScene->onUnloadResources();
	}
}


void SceneManager::checkLoadScene()
{
	if (this->isLoading)
	{
		this->unloadScene();
		this->activeScene = this->storedScenes[this->toLoadScene];
		this->activeScene->onLoadResources();
		this->activeScene->onLoadObjects();
		this->isLoading = false;
	}
}


bool SceneManager::isSceneLoaded(std::string sceneName)
{
	return this->activeScene->getSceneName() == sceneName;
}