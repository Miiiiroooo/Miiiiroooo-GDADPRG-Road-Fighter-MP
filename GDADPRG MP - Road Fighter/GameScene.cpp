#include "stdafx.h"
#include "GameScene.h"
#include "GameScreen.h"

using namespace std;

GameScene::GameScene() : AScene(SceneManager::COURSE_ONE_NAME)
{
}

GameScene::~GameScene()
{
}

void GameScene::onLoadResources()
{

}

void GameScene::onLoadObjects()
{
	//cout << "Game Scene Loaded" << endl;

	GameScreen* gameScreen = new GameScreen("GameScreen");
	this->registerObject(gameScreen);
}

void GameScene::onUnloadResources()
{
	
}
