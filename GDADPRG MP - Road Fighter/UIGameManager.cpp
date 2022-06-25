#include "stdafx.h"
#include "UIGameManager.h"
#include "Game.h"
#include "MiniRoad.h"


// constructor and destructor of the UIGameManager Class
UIGameManager::UIGameManager(std::string name) : AGameObject(name)
{
	this->gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
}


UIGameManager::~UIGameManager()
{

}


// public methods of the UIGameManager Class
void UIGameManager::initialize()
{
	// LEFT SIDE UI
	MiniRoad* miniRoad = new MiniRoad("MiniRoad");
	this->attachChild(miniRoad);
	miniRoad->setPosition(200.0f, 0);

	BasicUIObject* startFlag = new BasicUIObject("StartFlag", "flag_start.png", 0.85f);
	this->attachChild(startFlag);
	startFlag->setPosition(180.0f, 1030.0f);

	BasicUIObject* endFlag = new BasicUIObject("EndFlag", "flag_end.png", 0.85f);
	this->attachChild(endFlag);
	endFlag->setPosition(180.0f, 40.0f);

	this->miniPlayer = new BasicUIObject("MiniPlayer", "player_car_hud.png", 0.70f);
	this->attachChild(miniPlayer);
	this->miniPlayer->setPosition(225.0f, 1050.0f);


	// RIGHT SIDE UI
	this->scoreText = new UIText("ScoreText");
	this->scoreText->setPosition(Game::WINDOW_WIDTH / 2 + 600.0f, 150.0f);
	this->attachChild(this->scoreText);
	this->scoreText->setSize(120);
	this->scoreText->setText("000000");

	this->speedText = new UIText("SpeedText");
	this->speedText->setPosition(Game::WINDOW_WIDTH / 2 + 575.0f, 375.0f);
	this->attachChild(this->speedText);
	this->speedText->setSize(85);
	this->speedText->setText("000");

	BasicUIObject* speedHUD = new BasicUIObject("SpeedHUD", "SpeedHUD", 1.2f);
	this->attachChild(speedHUD);
	speedHUD->setPosition(Game::WINDOW_WIDTH / 2 + 710.f, 400.0f);

	BasicUIObject* fuelHUD = new BasicUIObject("FuelHUD", "FuelHUD", 1.5f);
	this->attachChild(fuelHUD);
	fuelHUD->setPosition(Game::WINDOW_WIDTH / 2 + 600.0f, 650.0f);

	this->fuelText = new UIText("FuelText");
	this->fuelText->setPosition(Game::WINDOW_WIDTH / 2 + 600.0f, 700.0f);
	this->attachChild(this->fuelText);
	this->fuelText->setSize(90);
	this->fuelText->setText("000");
}


void UIGameManager::update(sf::Time deltaTIme)
{
	if (!gameManager->checkGoal() && !gameManager->checkGameOver())
	{
		updateMiniPlayer();
		updateScore();
	}

	updateSpeed();
	updateFuel();
}


int UIGameManager::getDigits(int num)
{
	int digits = 0;

	while (num / 10 > 0) 
	{
		num /= 10;
		digits++;
	}

	return digits;
}


void UIGameManager::updateMiniPlayer()
{
	// miniplayer starts at  y = 1030
	// miniplayer should end at y = 40
	// overall, 990 pixels to travel

	float progress = gameManager->getDistance() / 40000.f; // get percentage from distance travelled and max distance
	float newPos = 1030.0f - (990.0f * progress);

	this->miniPlayer->getTransformable()->setPosition(225.0f, newPos);
}


void UIGameManager::updateScore()
{
	int score = gameManager->getScore();
	std::string text;

	for (int i = 0; i < 5 - getDigits(score); i++)
		text += "0";

	text += std::to_string(score);

	this->scoreText->setText(text);
}


void UIGameManager::updateSpeed()
{
	int speed = gameManager->getSpeed();
	std::string text;

	for (int i = 0; i < 2 - getDigits(speed); i++)
		text += "0";

	text += std::to_string(speed);

	this->speedText->setText(text);
}


void UIGameManager::updateFuel()
{
	int fuel = gameManager->getFuel();
	std::string text;

	for (int i = 0; i < 2 - getDigits(fuel); i++)
		text += "0";

	text += std::to_string(fuel);

	this->fuelText->setText(text);
}