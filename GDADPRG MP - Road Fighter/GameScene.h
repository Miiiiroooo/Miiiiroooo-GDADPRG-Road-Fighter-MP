#pragma once
#include "AScene.h"
#include "SceneManager.h"

class GameScene : public AScene
{
public:
	GameScene();
	~GameScene();

	void onLoadResources();
	void onLoadObjects();
	void onUnloadResources();
	void onUnloadObjects();

private:

};

