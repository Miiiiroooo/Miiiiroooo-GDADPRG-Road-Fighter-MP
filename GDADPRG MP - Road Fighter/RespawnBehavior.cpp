#include "stdafx.h"
#include "RespawnBehavior.h"
#include "Player.h"
#include "PhysicsManager.h"


// constructor and destructor of the RespawnBehavior Class
RespawnBehavior::RespawnBehavior(std::string name) : AComponent(name, Script)
{
	this->gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
}


RespawnBehavior::~RespawnBehavior()
{

}


// public methods of the RespawnBehavior Class
void RespawnBehavior::perform()
{
	Player* player = (Player*)this->getOwner();

	if (elapsedIframes < iframeDuration && !gameManager->crashed()) // check iframes duration
	{
		elapsedIframes += deltaTime.asSeconds();

		if (isBlinkingIn) // if it should appear on screen
		{
			if (elapsedBlinkIn < blinkInDuration)
			{
				elapsedBlinkIn += deltaTime.asSeconds();

				player->attachRenderer();
			}
			else
			{
				elapsedBlinkIn = 0.0f;
				isBlinkingIn = false;
			}
		}
		else if (!isBlinkingIn) // if it should disappear off screen
		{
			if (elapsedBlinkOut < blinkOutDuration)
			{
				elapsedBlinkOut += deltaTime.asSeconds();

				player->removeRenderer();
			}
			else
			{
				elapsedBlinkOut = 0.0f;
				isBlinkingIn = true;
			}
		}
	}
	else
	{
		player->detachComponent(this);

		Collider* collider = (Collider*)player->findComponentByName("PlayerCollider");
		PhysicsManager::getInstance()->trackObject(collider);
	}
}


void RespawnBehavior::reset()
{
	this->elapsedIframes = 0.0f;
	this->elapsedBlinkIn = 0.0f;
	this->elapsedBlinkOut = 0.0f;
	this->isBlinkingIn = false;
}