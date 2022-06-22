#pragma once
#include "AScene.h"


class GameScene_2 : public AScene
{
public:
	GameScene_2();
	~GameScene_2();

	void onLoadResources();
	void onLoadObjects();
	void onUnloadResources();
};

