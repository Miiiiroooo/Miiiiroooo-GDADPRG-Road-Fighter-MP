#include "stdafx.h"
#include "GameObjectManager.h"
#include "SceneManager.h"


// static declarations of the GameObjectManager Class
GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new GameObjectManager();

	return sharedInstance;
}


// public methods of the GameObjectManager Class
void GameObjectManager::processInput(sf::Event event)
{
	if (ApplicationManager::getInstance()->isPaused())
	{
		if (SceneManager::getInstance()->isSceneLoaded(SceneManager::MAIN_MENU_SCREEN_NAME))
		{
			//findObjectByName("QuitMenu")->processInputs(event);
		}
	}
	else
	{
		for (size_t i = 0; i < gameObjectList.size(); i++)
			if (gameObjectList[i]->getName() != "PauseMenuScreen" && gameObjectList[i]->getName() != "QuitMenu")
				gameObjectList[i]->processInputs(event);
	}
}


void GameObjectManager::update(sf::Time deltaTime)
{
	if (ApplicationManager::getInstance()->isPaused())
	{
		if (SceneManager::getInstance()->isSceneLoaded(SceneManager::MAIN_MENU_SCREEN_NAME))
		{
			//findObjectByName("QuitMenu")->update(deltaTime);
		}
	}
	else
	{
		for (size_t i = 0; i < gameObjectList.size(); i++)
			if (gameObjectList[i]->getName() != "PauseMenuScreen" && gameObjectList[i]->getName() != "QuitMenu")
				gameObjectList[i]->update(deltaTime);
	}
}


void GameObjectManager::draw(sf::RenderWindow* window)
{
	for (size_t i = 0; i < gameObjectList.size(); i++)
		if (gameObjectList[i]->getName() != "PauseMenuScreen" && gameObjectList[i]->getName() != "QuitMenu")
			gameObjectList[i]->draw(window, sf::RenderStates::Default);


	if (ApplicationManager::getInstance()->isPaused())
	{
		if (SceneManager::getInstance()->isSceneLoaded(SceneManager::MAIN_MENU_SCREEN_NAME))
		{
			//findObjectByName("QuitMenu")->draw(window, sf::RenderStates::Default);
		}
	}
}


void GameObjectManager::addObject(AGameObject* gameObject)
{
	gameObjectMap[gameObject->getName()] = gameObject;
	gameObjectList.push_back(gameObject);
	gameObject->initialize();
}


AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (gameObjectMap[name] != NULL)
		return gameObjectMap[name];
	else
	{
		std::cout << "Object " << name << " not found!" << std::endl;
		return NULL;
	}
}


std::vector<AGameObject*> GameObjectManager::getAllObjects()
{
	return gameObjectList;
}


void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	std::string key = gameObject->getName();
	delete gameObject;
	gameObjectMap.erase(key);
	gameObjectList.erase(std::remove(gameObjectList.begin(), gameObjectList.end(), gameObject));
	gameObjectList.shrink_to_fit();
}


void GameObjectManager::deleteObjectByName(std::string name)
{
	AGameObject* object = findObjectByName(name);

	if (object != NULL)
		deleteObject(object);
}


int GameObjectManager::activeObjects()
{
	return (int)gameObjectList.size();
}


void GameObjectManager::deleteAllObjectsInScene()
{
	for (size_t i = 0; i < this->gameObjectList.size(); i++)
	{
		delete this->gameObjectList[i];
	}

	this->gameObjectList.clear();
	this->gameObjectList.shrink_to_fit();
	this->gameObjectMap.clear();
}