#include "stdafx.h"
#include "BackgroundScroll.h"
#include "GameManager.h"
#include <math.h>

BackgroundScroll::BackgroundScroll(string name) :AComponent(name, Script)
{

}

BackgroundScroll::~BackgroundScroll()
{
	
}

void BackgroundScroll::perform()
{
	GameManager* gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
	SPEED_MULTIPLIER = gameManager->getSpeed();
	float scrollSpeed;

	if (SPEED_MULTIPLIER < 0)
	{
		scrollSpeed = 0;
	}
	else
	{
		scrollSpeed = pow(SPEED_MULTIPLIER, 1.2);
	}
	 
	
	

	sf::Sprite* sprite = this->getOwner()->getSprite();
	sf::Vector2f offset(0.0f, 0.0f);
	offset.y += scrollSpeed;
	sprite->move(offset * deltaTime.asSeconds());

	sf::Vector2f localPos = sprite->getPosition();
	if (localPos.y * deltaTime.asSeconds() > 0)
	{
		sprite->setPosition(sprite->getPosition().x, -Game::WINDOW_HEIGHT * 7);
	}

	cout << "Scroll Speed: " << scrollSpeed << endl;
}
