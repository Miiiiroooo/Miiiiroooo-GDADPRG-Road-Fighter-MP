#pragma once
#include "AGameObject.h"
#include "stdafx.h"
#include "PlayerInput.h"

using namespace std;

class GameManager : public AGameObject
{
public:
	GameManager(string name);
	~GameManager();

	void initialize();
	void update(sf::Time deltaTime);

	int getSpeed();
	float getScore();
	float getFuel();

private:
	int fuel = 100;
	int speed = 0.f;
	float score = 0.f;

	float fuelTicks;
	float scoreTicks;

	const int SPEED_MULTIPLIER = 150;
	const int MAX_SPEED = 400;

	const int MAX_FUEL = 100;
	const int FUEL_DRAIN = 1;
	const float FUEL_DRAIN_INTERVAL = 1.5f;

	const float SCORE_INTERVAL = 2.5f;
	const int SCORE_ADD = 50;

	PlayerInput* playerInput = NULL;
};

