#pragma once

#include "AComponent.h"
#include "GameManager.h"

class ObstacleBehavior : public AComponent
{
public:
	ObstacleBehavior(std::string name);
	~ObstacleBehavior();

	void perform();

private:
	GameManager* gameManager = NULL;
	float crashDuration;
};

