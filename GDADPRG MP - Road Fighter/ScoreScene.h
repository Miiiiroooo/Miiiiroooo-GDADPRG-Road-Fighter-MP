#pragma once

#include "AScene.h"

class ScoreScene : public AScene
{
public:
	ScoreScene();
	~ScoreScene();

	void onLoadResources();
	void onLoadObjects();
	void onUnloadResources();
};

