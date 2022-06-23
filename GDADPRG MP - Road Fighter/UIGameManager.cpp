#include "stdafx.h"
#include "UIGameManager.h"
#include "Game.h"
#include "MiniRoad.h"
#include "GoalLineMovement.h"


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
	miniRoad->setPosition(150, 0);

	BasicUIObject* startFlag = new BasicUIObject("StartFlag", "flag_start.png", 0.6f);
	this->attachChild(startFlag);
	startFlag->setPosition(135, 685);

	BasicUIObject* endFlag = new BasicUIObject("EndFlag", "flag_end.png", 0.6f);
	this->attachChild(endFlag);
	endFlag->setPosition(135, 25);

	this->miniPlayer = new BasicUIObject("MiniPlayer", "player_car_hud.png", 0.55f);
	this->attachChild(miniPlayer);
	this->miniPlayer->setPosition(160, 700);


	// RIGHT SIDE UI
	this->scoreText = new UIText("ScoreText");
	this->scoreText->setPosition(1100, 75);
	this->attachChild(this->scoreText);
	this->scoreText->setSize(60);
	this->scoreText->setText("000000");

	this->speedText = new UIText("SpeedText");
	this->speedText->setPosition(1100, 225);
	this->attachChild(this->speedText);
	this->speedText->setSize(45);
	this->speedText->setText("000");

	BasicUIObject* speedHUD = new BasicUIObject("SpeedHUD", "SpeedHUD", 0.5f);
	this->attachChild(speedHUD);
	speedHUD->setPosition(1175, 235);

	BasicUIObject* fuelHUD = new BasicUIObject("FuelHUD", "FuelHUD", 0.8f);
	this->attachChild(fuelHUD);
	fuelHUD->setPosition(1100, 375);

	this->fuelText = new UIText("FuelText");
	this->fuelText->setPosition(1100, 400);
	this->attachChild(this->fuelText);
	this->fuelText->setSize(50);
	this->fuelText->setText("000");


	// GOAL LINE
	this->goalLine = new BasicUIObject("GoalLine", "goal_line.png", 0.6f);
	GameObjectManager::getInstance()->addObject(goalLine);
	this->goalLine->setEnabled(false);

	GoalLineMovement* logicComponent = new GoalLineMovement("GoalLineMovement");
	this->goalLine->attachComponent(logicComponent);
	logicComponent->attachOwner(this->goalLine);
}


void UIGameManager::update(sf::Time deltaTIme)
{
	updateMiniPlayer();
	updateScore();
	updateSpeed();
	updateFuel();

	if (gameManager->getDistance() > 36000 && !isGoalLineEnabled)
		spawnGoalLine();
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


void UIGameManager::spawnGoalLine()
{
	this->goalLine->setPosition(Game::WINDOW_WIDTH / 2, -3950);
	this->goalLine->setEnabled(true);

	isGoalLineEnabled = true;
}


void UIGameManager::updateMiniPlayer()
{
	// miniplayer starts at  y = 700
	// miniplayer should end at y = 100
	// overall, 600 pixels to travel

	float progress = gameManager->getDistance() / 40000.f; // get percentage from distance travelled and max distance
	float newPos = 600.0f - (600.0f * progress); 

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