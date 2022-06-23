#pragma once
#include "AGameObject.h"
#include "stdafx.h"
#include "PlayerInput.h"
#include "Player.h"

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
	int getDistance();
	void addScore(int increase);
	void addFuel(int increase);

	bool crashed();
	void setCrashState(bool value);
	bool checkGameOver();

	bool checkGoal();

	void setPlayer(Player* player);
	void resetPlayer();

private:
	int fuel = 100;
	int speed = 0.f;
	float score = 0.f;

	float fuelTicks = 0.f;
	float scoreTicks = 0.f;

	const int SPEED_MULTIPLIER = 150;
	const int MAX_SPEED = 400;

	const int MAX_FUEL = 100;
	const int FUEL_DRAIN = 1;
	const float FUEL_DRAIN_INTERVAL = 1.5f;

	const float SCORE_INTERVAL = 2.5f;
	const int SCORE_ADD = 50;

	bool crash = false;

	int travelledDistance = 0;
	const int maxDistance = 36000;

	PlayerInput* playerInput = NULL;
	Player* player;
};

