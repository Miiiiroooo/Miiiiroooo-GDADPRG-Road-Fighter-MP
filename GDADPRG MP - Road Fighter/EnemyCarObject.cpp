#include "stdafx.h"
#include "EnemyCarObject.h"
#include "EnemyCarBehavior.h"
#include "PhysicsManager.h"
#include "ObjectPoolHolder.h"


// constructor and destructor of the ObstacleObject Class
EnemyCarObject::EnemyCarObject(std::string name) : APoolable(name)
{
	this->carSpeedList = {
		125.0f,
		200.0f,
		300.0f,
		400.0f,
		500.0f,
	};
}


EnemyCarObject::~EnemyCarObject()
{

}


// public methods of the ObstacleObject Class
void EnemyCarObject::initialize()
{
	initTexture();

	// randomly assign a texture from the vector
	int randIndex = rand() % enemyCarsTextureList.size();
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*enemyCarsTextureList[randIndex]);
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin((float)textureSize.x / 2, (float)textureSize.y / 2);
	this->sprite->setScale(0.6f, 0.6f);


	// init components
	Renderer* renderer = new Renderer("EnemyCar");
	this->attachComponent(renderer);
	renderer->attachOwner(this);
	renderer->assignDrawable(sprite);

	EnemyCarBehavior* logicComponent = new EnemyCarBehavior("EnemyCarBehavior");
	this->attachComponent(logicComponent);
	logicComponent->attachOwner(this);

	this->collider = new Collider("EnemyCarCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(collider);
}


void EnemyCarObject::initTexture()
{
	// init all appropriate textures for the obstacles
	std::vector<std::string> textureKeyList = {
		"enemy_cyan_0.png",
		"enemy_cyan_1.png",
		"enemy_red_0.png",
		"enemy_red_1.png",
		"enemy_yellow_0.png",
		"enemy_yellow_1.png",
	};

	for (int i = 0; i < textureKeyList.size(); i++)
		this->enemyCarsTextureList.push_back(TextureManager::getInstance()->getTexture(textureKeyList[i]));
}


float EnemyCarObject::getCarSpeed()
{
	return this->carSpeed;
}


void EnemyCarObject::onRelease()
{
	// set new texture AND update size before object gets activated
	int index = rand() % enemyCarsTextureList.size();
	this->sprite->setTexture(*enemyCarsTextureList[index]);

	sf::Vector2u textureSize = enemyCarsTextureList[index]->getSize();
	this->sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
	this->sprite->setOrigin((float)textureSize.x / 2, (float)textureSize.y / 2);


	// set new car speed
	index = rand() % carSpeedList.size();
	this->carSpeed = carSpeedList[index];


	// update physics managers
	PhysicsManager::getInstance()->untrackObject(this->collider);
}


void EnemyCarObject::onActivate()
{
	
}


APoolable* EnemyCarObject::clone()
{
	APoolable* copyObj = new EnemyCarObject(this->name);
	return copyObj;
}


bool EnemyCarObject::hasBeenCrashed()
{
	return this->crashed;
}


void EnemyCarObject::onCollisionEnter(AGameObject* contact)
{
	// if crashed onto player, do default car-crash updates
	if (contact->getName().find("Player") != std::string::npos && !crashed)
	{
		crashed = true;
	}

	// else if the car crashed onto other poolable objects, make self be released from pool
	else if ((contact->getName().find("EnemyCar") != std::string::npos && contact->isEnabled()) || 
		      contact->getName().find("Obstacle") != std::string::npos)
	{
		GameObjectPool* enemyCarPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG);
		enemyCarPool->releasePoolable((APoolable*)this);
	}

	// else reset collider settings if contact is already disabled OR contact is a car fuel
	else if ((contact->getName().find("EnemyCar") != std::string::npos && !contact->isEnabled()) || 
			  contact->getName().find("CarFuel") != std::string::npos)
	{
		this->collider->setAlreadyCollided(false);
	}
}


void EnemyCarObject::onCollisionExit(AGameObject* gameObject)
{
	crashed = false;
}
