#pragma once

#include"AComponent.h"
#include "GameManager.h"
#include "GameObjectManager.h"


using namespace std;

class CrashComponent : public AComponent
{
public:
	CrashComponent(string name);
	~CrashComponent();
	void perform();

	void setRoadEdges(int left, int right);

private:
	GameManager* gameManager;
	float ticks;

	bool hasUntracked = false;

	int leftEdge = 0;
	int rightEdge = 0;
};

