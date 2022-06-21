#pragma once

#include "AGameObject.h"

class BlackScreen : public AGameObject
{
public:
	BlackScreen(std::string name, std::string screenToTransition);
	~BlackScreen();

	void initialize();


private:
	sf::RectangleShape* blackScreen = NULL;
	std::string screenToTransition;
};

