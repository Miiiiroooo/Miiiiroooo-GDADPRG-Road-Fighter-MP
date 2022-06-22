#include "stdafx.h"
#include "EnemyCarObject.h"
#include "EnemyCarBehavior.h"
#include "PhysicsManager.h"


// constructor and destructor of the ObstacleObject Class
EnemyCarObject::EnemyCarObject(std::string name) : APoolable(name)
{

}


EnemyCarObject::~EnemyCarObject()
{

}


// public methods of the ObstacleObject Class
void EnemyCarObject::initialize()
{
	// init all appropriate textures for the obstacles
	std::vector<std::string> textureKeyList = {
		"enemy_cyan_0.png",
		"enemy_cyan_1.png",
		"enemy_cyan_2.png",
		"enemy_cyan_3.png",
		"enemy_red_0.png",
		"enemy_red_1.png",
		"enemy_red_2.png",
		"enemy_red_3.png",
		"enemy_yellow_0.png",
		"enemy_yellow_1.png",
		"enemy_yellow_2.png",
		"enemy_yellow_3.png",
	};

	for (int i = 0; i < textureKeyList.size(); i++)
		this->enemyCarsTextureList.push_back(TextureManager::getInstance()->getTexture(textureKeyList[i]));


	// randomly assign a texture from the vector
	int index = rand() % textureKeyList.size();
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*enemyCarsTextureList[index]);
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
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

}


void EnemyCarObject::onRelease()
{
	// set new texture AND update size before object gets activated
	int index = rand() % 4;
	this->sprite->setTexture(*enemyCarsTextureList[index]);

	sf::Vector2u textureSize = enemyCarsTextureList[index]->getSize();
	this->sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);


	// update physics managers
	PhysicsManager::getInstance()->untrackObject((Collider*)this->findComponentByName("ObstacleCollider"));
}


void EnemyCarObject::onActivate()
{
	// init position from 525 until 775
	int randX = rand() % (775 - 525) + 525;
	this->setPosition(randX, 0);
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
	if (contact->getName().find("Player") != std::string::npos && !crashed)
	{
		crashed = true;
	}
}


void EnemyCarObject::onCollisionExit(AGameObject* gameObject)
{
	crashed = false;

}
