#pragma once
#include "AGameObject.h"
class Player : public AGameObject
{
public:
	Player(std::string name);
	void initialize();

	sf::Event event;
private:
	const float SPEED_MULTIPLIER = 100.0f;
	bool moveDown = false;
	bool moveLeft = false;
};

