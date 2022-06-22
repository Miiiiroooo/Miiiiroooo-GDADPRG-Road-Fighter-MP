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
	miniRoad->getTransformable()->setPosition(150, 0);

	BasicUIObject* startFlag = new BasicUIObject("StartFlag", "flag_start.png", 0.6f);
	this->attachChild(startFlag);
	startFlag->getTransformable()->setPosition(135, 685);

	BasicUIObject* endFlag = new BasicUIObject("EndFlag", "flag_end.png", 0.6f);
	this->attachChild(endFlag);
	endFlag->getTransformable()->setPosition(135, 25);

	this->miniPlayer = new BasicUIObject("MiniPlayer", "player_car_hud.png", 0.55f);
	this->attachChild(miniPlayer);
	this->miniPlayer->getTransformable()->setPosition(160, 700);


	// RIGHT SIDE UI
	this->scoreText = new UIText("ScoreText");
	this->scoreText->getTransformable()->setPosition(1100, 75);
	this->attachChild(this->scoreText);
	this->scoreText->setSize(60);
	this->scoreText->setText("000000");

	this->speedText = new UIText("SpeedText");
	this->speedText->getTransformable()->setPosition(1100, 225);
	this->attachChild(this->speedText);
	this->speedText->setSize(45);
	this->speedText->setText("000");

	BasicUIObject* speedHUD = new BasicUIObject("SpeedHUD", "SpeedHUD", 0.5f);
	this->attachChild(speedHUD);
	speedHUD->getTransformable()->setPosition(1175, 235);

	BasicUIObject* fuelHUD = new BasicUIObject("FuelHUD", "FuelHUD", 0.8f);
	this->attachChild(fuelHUD);
	fuelHUD->getTransformable()->setPosition(1100, 375);

	this->fuelText = new UIText("FuelText");
	this->fuelText->getTransformable()->setPosition(1100, 400);
	this->attachChild(this->fuelText);
	this->fuelText->setSize(50);
	this->fuelText->setText("000");

	this->livesText = new UIText("LivesText");
	this->livesText->getTransformable()->setPosition(1100, 500);
	this->attachChild(this->livesText);
	this->livesText->setSize(50);
	updateLives();
}


void UIGameManager::update(sf::Time deltaTIme)
{
	updateMiniPlayer();
	updateScore();
	updateSpeed();
	updateFuel();
	updateLives();
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
	// miniplayer starts at 700
	// miniplayer should end at 50
	// overall, 650 pixels to travel

	float progress = gameManager->getDistance() / 36000.f; // get percentage from distanced travelled and max distance
	float newPos = 650.0f - (650.0f * progress); 

	this->miniPlayer->getTransformable()->setPosition(160.0f, newPos);
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


void UIGameManager::updateLives()
{
	int numLives = gameManager->getNumLives();
	std::string text = "Lives  ";
	text += std::to_string(numLives);

	this->livesText->setText(text);
}