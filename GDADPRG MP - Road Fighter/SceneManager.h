#pragma once

#include "AScene.h"

typedef std::unordered_map<std::string, AScene*> SceneTable;
typedef std::vector<std::string> SceneList;

class SceneManager : sf::NonCopyable
{
// methods of the SceneManager Class
public:
	static SceneManager* getInstance();

	void resgiterScene(AScene* scene);
	void loadScene(std::string sceneName);
	void unloadScene();
	void checkLoadScene();
	bool isSceneLoaded(std::string sceneName);

private:
	SceneManager() {};


// attributes of the SceneManager Class
public:
	// scene names
	static std::string MAIN_MENU_SCREEN_NAME;
	static std::string LEVEL_ONE_COURSE_ONE_NAME;
	static std::string LEVEL_ONE_COURSE_TWO_NAME;
	static std::string LEVEL_TWO_COURSE_ONE_NAME;
	static std::string LEVEL_TWO_COURSE_TWO_NAME;
	
private:
	static SceneManager* sharedInstance;

	bool isLoading = false;
	std::string toLoadScene;

	SceneTable storedScenes;
	AScene* activeScene;
};

