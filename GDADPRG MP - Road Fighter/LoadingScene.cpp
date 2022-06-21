#include "stdafx.h"
#include "LoadingScene.h"
#include "LoadingScreen.h"


// constructor and destructor of the LoadingScene Class
LoadingScene::LoadingScene() : AScene("LoadingScene")
{

}


LoadingScene::~LoadingScene()
{

}


// public methods of the LoadingScene Class
void LoadingScene::onLoadResources()
{

}


void LoadingScene::onLoadObjects()
{
	LoadingScreen* loadingScreen = new LoadingScreen("LoadingScreen");
	this->registerObject(loadingScreen);
}


void LoadingScene::onUnloadResources()
{

}