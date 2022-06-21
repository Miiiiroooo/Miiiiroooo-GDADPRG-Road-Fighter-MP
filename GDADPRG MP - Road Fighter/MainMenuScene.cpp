#include "stdafx.h"
#include "MainMenuScene.h"
#include "TitleScreen.h"
#include "GameObjectManager.h"

using namespace std;

MainMenuScene::MainMenuScene():AScene("MainMenuScene")
{
}

MainMenuScene::~MainMenuScene()
{
	AScene::~AScene();
}

void MainMenuScene::onLoadResources()
{

	
	AScene::onLoadResources();

}

void MainMenuScene::onLoadObjects()
{
	cout << "Main Menu Scene Loaded" << endl;
	std::cout << "Main Menu Scene Loaded" << endl;
	TitleScreen* titleScreen = new TitleScreen("TitleScreen");
	this->registerObject(titleScreen);

	AScene::onLoadObjects();
}

void MainMenuScene::onUnloadResources()
{
	AScene::onUnloadResources();
}

void MainMenuScene::onUnloadObjects()
{
	AScene::onUnloadObjects();
}
