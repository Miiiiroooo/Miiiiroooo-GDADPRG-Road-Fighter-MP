#include "stdafx.h"
#include "MainMenuScene.h"
#include "TitleScreen.h"

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
	std::cout << "Main Menu Scene Loaded" << endl;
	TitleScreen* titleScreen = new TitleScreen("TitleScreen");
	this->registerObject(titleScreen);

}

void MainMenuScene::onUnloadResources()
{
}

void MainMenuScene::onUnloadObjects()
{
}
