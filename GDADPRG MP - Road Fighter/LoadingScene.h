#pragma once

#include "AScene.h"

class LoadingScene : public AScene
{
public:
	LoadingScene();
	~LoadingScene();

	void onLoadResources();
	void onLoadObjects();
	void onUnloadResources();
};

