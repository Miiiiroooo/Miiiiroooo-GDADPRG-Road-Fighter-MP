#pragma once

#include "AGameObject.h"
#include "ApplicationManager.h"

class GameObjectManager : sf::NonCopyable
{
// methods
public:
	static GameObjectManager* getInstance();

	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* window);

	void addObject(AGameObject* gameObject);
	AGameObject* findObjectByName(std::string name);
	std::vector<AGameObject*> getAllObjects();
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);;
	int activeObjects();

	void deleteAllObjectsInScene();	


// attributes
private:
	GameObjectManager() {};
	static GameObjectManager* sharedInstance;

	std::unordered_map<std::string, AGameObject*> gameObjectMap;
	std::vector<AGameObject*> gameObjectList;
};