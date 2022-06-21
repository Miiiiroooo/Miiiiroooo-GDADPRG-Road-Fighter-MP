#pragma once

#include "AComponent.h"
#include "BlackScreen.h"

class ScreenTransitionBehavior : public AComponent
{
public:
	ScreenTransitionBehavior(std::string name, std::string screenToTransition);
	~ScreenTransitionBehavior();

	void perform();


private:
	BlackScreen* blackScreen = NULL;
	std::string screenToTransition;
	const float SPEED_MULTIPLIER = 1280;
};

