#pragma once
#include "AComponent.h"
#include "stdafx.h"
#include"AComponent.h"
#include"AGameObject.h"
#include"Game.h"
#include "GameManager.h"
#include "GameObjectManager.h"


using namespace std;

class CrashComponent : public AComponent
{
public:
	CrashComponent(string name);
	~CrashComponent();
	void perform();

private:
	GameManager* gameManager;
	float ticks;
};

