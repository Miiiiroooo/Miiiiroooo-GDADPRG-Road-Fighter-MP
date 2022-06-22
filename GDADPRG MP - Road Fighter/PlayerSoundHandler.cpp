#include "stdafx.h"
#include "PlayerSoundHandler.h"
#include "GameManager.h"

#include <iostream>

using namespace std;


PlayerSoundHandler::PlayerSoundHandler(std::string name) :AComponent(name, Script)
{
}

PlayerSoundHandler::~PlayerSoundHandler()
{
}

void PlayerSoundHandler::perform()
{
	if (!soundEnabled)
	{
		engineSound->stop();
		crashSound->stop();
		return;
	}
	
	if (firstTime)
	{
		engineSound->setBuffer(*SFXManager::getInstance()->getAudio("PlayerEngine"));
		engineSound->setLoop(true);
		
		crashSound->setBuffer(*SFXManager::getInstance()->getAudio("PlayerDeath"));

		firstTime = false;
	}

	GameManager* gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
	Player* player = (Player*)this->getOwner();
	PlayerInput* inputController = (PlayerInput*)player->getComponentsOfType(AComponent::ComponentType::Input)[0];
	
	if (inputController->isW() && !gameManager->crashed())
	{
		if (pitchAdd < 0.5f)
		{
			pitchAdd += 0.1 * deltaTime.asSeconds();
			engineSound->setPitch(1 + pitchAdd);
		}
		
	}
	else if(!inputController->isW() || gameManager->crashed())
	{
		if (pitchAdd > 0.f)
		{
			pitchAdd -= 0.18 * deltaTime.asSeconds();
			engineSound->setPitch(1 + pitchAdd);
		}
	}

	if (inputController->isW() && engineSound->getStatus() == sf::Sound::Status::Stopped && !gameManager->crashed())
	{
		engineSound->play();
		
	}
	else if((!inputController->isW() || gameManager->crashed()) && pitchAdd <= 0.f || gameManager->getSpeed() <= 0)
	{
		engineSound->stop();
	}

	if (gameManager->crashed() && crashSound->getStatus() == sf::Sound::Status::Stopped)
	{
		crashSound->play();
		engineSound->setPitch(1.f);
		pitchAdd = 0;
	}


}

void PlayerSoundHandler::EnableSound(bool value)
{
	this->soundEnabled = value;
}

