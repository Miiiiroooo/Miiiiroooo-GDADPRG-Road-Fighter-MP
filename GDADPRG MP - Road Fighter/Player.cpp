#include "stdafx.h"
#include "Player.h"

#include "Game.h"
#include "PlayerInput.h"
#include "PlayerMovement.h"
#include "PlayerSoundHandler.h"
#include "CrashComponent.h"
#include "RespawnBehavior.h"


using namespace std;

Player::Player(std::string name) : AGameObject(name), CollisionListener()
{
	
}

void Player::initialize()
{
	this->normalTexture = TextureManager::getInstance()->getTexture("player_car_0.png");
	this->crashedTexture = TextureManager::getInstance()->getTexture("player_death_0.png");
	
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*normalTexture);

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->sprite->setScale(0.5f, 0.5f);
	this->transformable.setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 + 300);

	
	PlayerInput* playerInput = new PlayerInput("input_control");
	this->attachComponent(playerInput);

	PlayerMovement* playerMovement = new PlayerMovement("player_movement");
	this->attachComponent(playerMovement);

	CrashComponent* crashComponent = new CrashComponent("CrashComponent");
	//crashComponent->setRoadEdges(500, 790);
	this->attachComponent(crashComponent);
	
	this->renderComponent = new Renderer("PlayerRenderer");
	renderComponent->assignDrawable(this->sprite);
	attachRenderer();

	this->collider = new Collider("PlayerCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(collider);

	PlayerSoundHandler* playerSound = new PlayerSoundHandler("SoundHandler");
	this->attachComponent(playerSound);

}

void Player::setNormalTexture()
{
	this->sprite->setTexture(*normalTexture);
}

void Player::setCrashedTexture()
{
	this->sprite->setTexture(*crashedTexture);
}


void Player::removeRenderer()
{
	if (hasRenderer)
	{
		int index = -1;

		for (size_t i = 0; i < this->componentList.size(); i++)
		{
			if (this->componentList[i]->getName() == "PlayerRenderer")
			{
				index = (int)i;
				break;
			}
		}

		if (index != -1)
		{
			this->componentList.erase(this->componentList.begin() + index);
		}

		hasRenderer = false;
	}
}


void Player::attachRenderer()
{
	if (!hasRenderer)
	{
		this->attachComponent(this->renderComponent);
		hasRenderer = true;
	}
}


void Player::onCollisionEnter(AGameObject* contact)
{
	GameManager* gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");

	if ((contact->getName().find("EnemyCar") != std::string::npos ||
		contact->getName().find("Obstacle") != std::string::npos) &&
		!gameManager->crashed())
	{
		gameManager->setCrashState(true);
	}
	else if (contact->getName().find("CarFuel") != std::string::npos)
	{
		this->collider->setAlreadyCollided(false);
	}
}


void Player::onCollisionExit(AGameObject* gameObject)
{
	// if player died more than once consecutively, reset the old respawn component instead of initialize a new one
	if (this->findComponentByName("RespawnComponent") != NULL)
	{
		RespawnBehavior* respawnComponent = (RespawnBehavior*)this->findComponentByName("RespawnComponent");
		respawnComponent->reset();
	}
	else
	{
		RespawnBehavior* respawnComponent = new RespawnBehavior("RespawnComponent");
		this->attachComponent(respawnComponent);
		respawnComponent->attachOwner(this);
	}
}
