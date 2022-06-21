#pragma once
#include "AComponent.h"

class PlayerMovement : public AComponent
{
public:
	PlayerMovement(std::string name);
	~PlayerMovement();

	void perform();

private:
	const float SPEED_MULTIPLIER = 400.0f;

};

