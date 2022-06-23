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
	float crashDuration;  // gets incremented for each deltatime
};

