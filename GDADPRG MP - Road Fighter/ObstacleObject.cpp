#include "stdafx.h"
#include "ObstacleObject.h"
#include "ObstacleBehavior.h"
#include "PhysicsManager.h"


// constructor and destructor of the ObstacleObject Class
ObstacleObject::ObstacleObject(std::string name) : APoolable(name)
{

}


ObstacleObject::~ObstacleObject()
{

}


// public methods of the ObstacleObject Class
void ObstacleObject::initialize()
{
	initTexture();

	// randomly assign a texture from the vector
	int index = rand() % obstacleTextureList.size();
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*obstacleTextureList[index]);
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin((float)textureSize.x / 2, (float)textureSize.y / 2);
	this->sprite->setScale(0.6f, 0.6f);


	// init components
	Renderer* renderer = new Renderer("Obstacle");
	this->attachComponent(renderer);
	renderer->attachOwner(this);
	renderer->assignDrawable(sprite);

	ObstacleBehavior* logicComponent = new ObstacleBehavior("ObstacleBehavior");
	this->attachComponent(logicComponent);
	logicComponent->attachOwner(this);

	this->collider = new Collider("ObstacleCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(collider);
}


void ObstacleObject::initTexture()
{
	// init all appropriate textures for the obstacles
	std::vector<std::string> textureKeyList = {
		"obstacle_manhole.png",
		"barrel_cyan.png",
		"barrel_red.png",
		"barrel_yellow.png"
	};

	for (int i = 0; i < 4; i++)
		this->obstacleTextureList.push_back(TextureManager::getInstance()->getTexture(textureKeyList[i]));
}


void ObstacleObject::onRelease()
{
	// set new texture AND update size before object gets activated
	int index = rand() % 4;
	this->sprite->setTexture(*obstacleTextureList[index]);

	sf::Vector2u textureSize = obstacleTextureList[index]->getSize();
	this->sprite->setTextureRect(sf::IntRect(0,0,textureSize.x, textureSize.y));
	this->sprite->setOrigin((float)textureSize.x / 2, (float)textureSize.y / 2);


	// update physics managers
	PhysicsManager::getInstance()->untrackObject(this->collider);
}


void ObstacleObject::onActivate()
{
	
}


APoolable* ObstacleObject::clone()
{
	APoolable* copyObj = new ObstacleObject(this->name);
	return copyObj;
}


bool ObstacleObject::hasBeenCrashed()
{
	return this->crashed;
}


void ObstacleObject::onCollisionEnter(AGameObject* contact)
{
	if (contact->getName().find("Player") != std::string::npos && !crashed)
	{
		crashed = true;
	}
	else if (contact->getName().find("CarFuel") != std::string::npos || contact->getName().find("EnemyCar") != std::string::npos)
	{
		this->collider->setAlreadyCollided(false);
	}
}


void ObstacleObject::onCollisionExit(AGameObject* gameObject)
{
	crashed = false;

}