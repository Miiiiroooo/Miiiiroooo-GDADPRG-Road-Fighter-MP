#include "stdafx.h"
#include "GameManager.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "GameScreen.h"
#include "UIText.h"

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
	if (crash)
	{
		speed = speed;
	}
	else if (playerInput->isW() && speed < MAX_SPEED)
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

	//FUEL
	fuelTicks += deltaTime.asSeconds();
	if (fuelTicks > FUEL_DRAIN_INTERVAL && !crash && speed != 0 && fuel > 0)
	{
		fuelTicks = 0.f;
		fuel -= FUEL_DRAIN;
	}
	else if (fuel <= 0)
	{
		fuel = 0;
	}

	//SCORE
	scoreTicks += deltaTime.asSeconds();
	if (scoreTicks > SCORE_INTERVAL && !crash && speed != 0)
	{
		scoreTicks = 0.f;
		score += SCORE_ADD;
	}

	// DISTANCE
	if (!this->crash)
	{
		travelledDistance += speed * deltaTime.asSeconds();
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

int GameManager::getDistance()
{
	return travelledDistance;
}

void GameManager::addFuel(int increase)
{
	this->fuel += increase;
}

void GameManager::addScore(int increase)
{
	this->score += increase;
}

bool GameManager::crashed()
{
	return this->crash;
}

void GameManager::setCrashState(bool value)
{
	this->crash = value;
}

bool GameManager::checkGameOver()
{
	return (fuel <= 0);
}

bool GameManager::checkGoal()
{
	return (this->player->hasReachedGoal());
}

void GameManager::setPlayer(Player* player)
{
	this->player = player;
}

void GameManager::resetPlayer()
{
	this->crash = false;
	this->speed = 0;

	this->fuel -= 10;
	if (this->fuel < 0)
		fuel = 0;

	this->score -= 500;
	if (this->score < 0)
		score = 0;

	player->setNormalTexture();
	player->getTransformable()->setPosition(Game::WINDOW_WIDTH / 2, player->getTransformable()->getPosition().y);
}
