#include "stdafx.h"
#include "CarFuelObject.h"
#include "CarFuelBehavior.h"
#include "SFXManager.h"
#include "PhysicsManager.h"
#include "ObjectPoolHolder.h"


// constructor and destructor of the CarFuelObject Class
CarFuelObject::CarFuelObject(std::string name) : APoolable(name)
{

}


CarFuelObject::~CarFuelObject()
{
	if (this->scoreTune != NULL)
	{
		delete this->scoreTune;
		this->scoreTune = NULL;
	}
}


// public methods of the CarFuelObject Class
void CarFuelObject::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("car_powerup.png"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin((float)textureSize.x / 2, (float)textureSize.y / 2);
	this->sprite->setScale(0.6f, 0.6f);


	// audio
	sf::SoundBuffer* buffer = SFXManager::getInstance()->getAudio("GainedScore");
	this->scoreTune = new sf::Sound();
	this->scoreTune->setBuffer(*buffer);


	// init components
	Renderer* renderer = new Renderer("CarFuelRenderer");
	this->attachComponent(renderer);
	renderer->attachOwner(this);
	renderer->assignDrawable(sprite);

	CarFuelBehavior* logicComponent = new CarFuelBehavior("CarFuelBehavior");
	this->attachComponent(logicComponent);
	logicComponent->attachOwner(this);

	this->collider = new Collider("CarFuelCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(collider);
}


void CarFuelObject::playTune()
{
	this->scoreTune->play();
}


void CarFuelObject::onRelease()
{
	// update physics managers
	PhysicsManager::getInstance()->untrackObject(this->collider);
}


void CarFuelObject::onActivate()
{

}


APoolable* CarFuelObject::clone()
{
	APoolable* copyObj = new CarFuelObject(this->name);
	return copyObj;
}


bool CarFuelObject::hasBeenCrashed()
{
	return this->crashed;
}


void CarFuelObject::onCollisionEnter(AGameObject* contact)
{
	// if crashed onto player, do default car-crash updates
	if (contact->getName().find("Player") != std::string::npos && !crashed)
	{
		crashed = true;
	}

	// else if the fuel-car crashed onto other poolable objects, update collider settings
	else if (contact->getName().find("EnemyCar") != std::string::npos || contact->getName().find("Obstacle") != std::string::npos)
	{
		this->collider->setAlreadyCollided(false);
	}
}


void CarFuelObject::onCollisionExit(AGameObject* gameObject)
{
	crashed = false;
}