#pragma once

#include "AComponent.h"
#include "GameManager.h"

class GoalLineMovement : public AComponent
{
public:
	GoalLineMovement(std::string name);
	~GoalLineMovement();

	void perform();


private:
	GameManager* gameManager = NULL;
};

