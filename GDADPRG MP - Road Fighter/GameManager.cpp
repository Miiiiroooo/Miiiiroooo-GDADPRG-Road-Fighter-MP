#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager(string name) :AGameObject(name)
{

}

GameManager::~GameManager()
{
	AGameObject::~AGameObject();
}

void GameManager::initialize()
{
	playerInput = new PlayerInput("PlayerInput");
	this->attachComponent(playerInput);

}

void GameManager::update(sf::Time deltaTime)
{
	
	//Speed
	if (playerInput->isW() && speed < MAX_SPEED)
	{
		speed += SPEED_MULTIPLIER * deltaTime.asSeconds();
	}
	else if (playerInput->isW() && speed > MAX_SPEED)
	{
		speed = MAX_SPEED;
	}
	else if (!playerInput->isW() && speed > 0)
	{
		speed -= (SPEED_MULTIPLIER) * deltaTime.asSeconds();
	}
	else if(speed < 0)
	{
		speed = 0;
	}

	//cout << "speed: " << speed << endl;

	//FUEL
	fuelTicks += deltaTime.asSeconds();
	if (fuelTicks > FUEL_DRAIN_INTERVAL)
	{
		fuelTicks = 0.f;
		fuel -= FUEL_DRAIN;
	}

	scoreTicks += deltaTime.asSeconds();
	if (scoreTicks > SCORE_INTERVAL)
	{
		scoreTicks = 0.f;
		score += SCORE_ADD;
	}

}

int GameManager::getSpeed()
{
	return this->speed;
}

float GameManager::getScore()
{
	return score;
}

float GameManager::getFuel()
{
	return fuel;
}
