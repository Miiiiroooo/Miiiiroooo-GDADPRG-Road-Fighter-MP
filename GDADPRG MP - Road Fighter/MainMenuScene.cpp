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
	
}

void MainMenuScene::onLoadResources()
{

}

void MainMenuScene::onLoadObjects()
{
	TitleScreen* titleScreen = new TitleScreen("TitleScreen");
	this->registerObject(titleScreen);
}

void MainMenuScene::onUnloadResources()
{
	
}
