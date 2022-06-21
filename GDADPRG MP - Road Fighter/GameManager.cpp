#include "stdafx.h"
#include "GameManager.h"
#include "GameObjectManager.h"
#include "Game.h"

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

bool GameManager::crashed()
{
	return this->crash;
}

void GameManager::setCrashState(bool value)
{
	this->crash = value;
}

void GameManager::setPlayer(Player* player)
{
	this->player = player;
}

void GameManager::resetPlayer()
{
	this->crash = false;
	player->setNormalTexture();
	player->getTransformable()->setPosition(Game::WINDOW_WIDTH / 2, player->getTransformable()->getPosition().y);
}
