#pragma once

#include "AGameObject.h"

class LoadingScreen : public AGameObject
{
public:
	LoadingScreen(std::string name);
	~LoadingScreen();

	void initialize();


private:
	sf::RectangleShape* blackBox;
};

