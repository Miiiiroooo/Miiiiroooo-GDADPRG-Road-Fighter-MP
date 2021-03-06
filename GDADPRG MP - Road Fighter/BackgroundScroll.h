#pragma once
#include "AComponent.h"
#include "stdafx.h"
#include"AComponent.h"
#include"AGameObject.h"
#include"Game.h"
#include "GameManager.h"
#include "GameObjectManager.h"

using namespace std;

class BackgroundScroll : public AComponent
{
public:
	BackgroundScroll(string name);
	~BackgroundScroll();
	void perform();

private:
	float SPEED_MULTIPLIER = 0.f;
	GameManager* gameManager;
};

