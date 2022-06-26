#include "stdafx.h"
#include "ScoreScene.h"
#include "ScoreScreen.h"

// constructor and destructor of the ScoreScene Class
ScoreScene::ScoreScene() : AScene("ScoreScene")
{

}


ScoreScene::~ScoreScene()
{

}


// public methods of the ScoreScene Class
void ScoreScene::onLoadResources()
{

}


void ScoreScene::onLoadObjects()
{
	ScoreScreen* scoreScreen = new ScoreScreen("ScoreScreen");
	this->registerObject(scoreScreen);
}


void ScoreScene::onUnloadResources()
{

}