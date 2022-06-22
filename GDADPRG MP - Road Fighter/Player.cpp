#include "stdafx.h"
#include "Player.h"

#include "Game.h"
#include "PlayerInput.h"
#include "PlayerMovement.h"
#include "CrashComponent.h"


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
	this->transformable.setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 + 200);

	
	PlayerInput* playerInput = new PlayerInput("input_control");
	this->attachComponent(playerInput);

	PlayerMovement* playerMovement = new PlayerMovement("player_movement");
	this->attachComponent(playerMovement);

	CrashComponent* crashComponent = new CrashComponent("CrashComponent");
	this->attachComponent(crashComponent);
	
	Renderer* renderComponent = new Renderer("BGSprite");
	renderComponent->assignDrawable(sprite);
	this->attachComponent(renderComponent);

	this->collider = new Collider("PlayerCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(collider);
	this->collider->attachOwner(this);
}

void Player::setNormalTexture()
{
	this->sprite->setTexture(*normalTexture);
}

void Player::setCrashedTexture()
{
	this->sprite->setTexture(*crashedTexture);
}


bool Player::hasCarCrashed()
{
	return this->carCrash;
}


void Player::onCollisionEnter(AGameObject* contact)
{
	if ((contact->getName().find("EnemyCar") != std::string::npos || contact->getName().find("Obstacle") != std::string::npos) && !carCrash)
	{
		carCrash = true;

		Collider* playerCollider = (Collider*)this->findComponentByName("PlayerCollider");
		PhysicsManager::getInstance()->untrackObject(playerCollider);
	}
}


void Player::onCollisionExit(AGameObject* gameObject)
{
	if (carCrash)
	{
		Collider* playerCollider = (Collider*)this->findComponentByName("PlayerCollider");
		PhysicsManager::getInstance()->trackObject(playerCollider);
	}

	carCrash = false;
}