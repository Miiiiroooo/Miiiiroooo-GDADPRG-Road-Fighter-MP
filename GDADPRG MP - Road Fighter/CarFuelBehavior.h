#pragma once

#include "AComponent.h"
#include "GameManager.h"
#include "UIText.h"

class CarFuelBehavior : public AComponent
{
public:
	CarFuelBehavior(std::string name);
	~CarFuelBehavior();

	void perform();


private:
	GameManager* gameManager = NULL;
	const float speed = 350.0f;
};

