#include "stdafx.h"
#include "GameScene_2.h"
#include "GameScreen_2.h"
#include "SceneManager.h"

using namespace std;

GameScene_2::GameScene_2() : AScene(SceneManager::COURSE_TWO_NAME)
{
}

GameScene_2::~GameScene_2()
{
}

void GameScene_2::onLoadResources()
{

}

void GameScene_2::onLoadObjects()
{
	//cout << "Game Scene Loaded" << endl;
	GameScreen_2* gameScreen = new GameScreen_2("GameScreen");
	this->registerObject(gameScreen);
}

void GameScene_2::onUnloadResources()
{

}
