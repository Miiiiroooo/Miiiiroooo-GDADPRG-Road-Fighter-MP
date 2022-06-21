#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "Background.h"
#include "GameManager.h"
#include <iostream>

using namespace std;

GameScene::GameScene() : AScene(SceneManager::LEVEL_ONE_COURSE_ONE_NAME)
{
}

GameScene::~GameScene()
{
}

void GameScene::onLoadResources()
{
	AScene::onLoadResources();

}

void GameScene::onLoadObjects()
{
	cout << "Game Scene Loaded" << endl;

	GameManager* gameManager = new GameManager("GameManager");
	this->registerObject(gameManager);

	Background* background = new Background("Background");
	this->registerObject(background);

	Player* player = new Player("Player");
	this->registerObject(player);

	gameManager->setPlayer(player);

	AScene::onLoadObjects();

}

void GameScene::onUnloadResources()
{
	AScene::onUnloadResources();
}

void GameScene::onUnloadObjects()
{
	AScene::onUnloadObjects();
}
