#pragma once

#include "AComponent.h"
#include "GameManager.h"

class EnemyCarBehavior : public AComponent
{
public:
	EnemyCarBehavior(std::string name);
	~EnemyCarBehavior();

	void perform();


private:
	GameManager* gameManager = NULL;
	const float SPEED_MULTIPLIER = 400.0f;
	float crashDuration;
};

