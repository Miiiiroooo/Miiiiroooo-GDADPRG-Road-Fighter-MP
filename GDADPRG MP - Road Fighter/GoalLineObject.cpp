#include "stdafx.h"
#include "GoalLineObject.h"
#include "GoalLineMovement.h"
#include "PhysicsManager.h"


// constructor and destructor of the GoalLineObject Class
GoalLineObject::GoalLineObject(std::string name, float scaleValue) : AGameObject(name)
{
	this->scaleValue = scaleValue;
}


GoalLineObject::~GoalLineObject()
{

}


// public methods of the GoalLineObject Class
void GoalLineObject::initialize()
{
	// init sprite
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("goal_line.png"));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->sprite->setScale(scaleValue, scaleValue);


	// init components
	Renderer* renderer = new Renderer(this->name);
	this->attachComponent(renderer);
	renderer->attachOwner(this);
	renderer->assignDrawable(this->sprite);

	GoalLineMovement* logicComponent = new GoalLineMovement("GoalLineMovement");
	this->attachComponent(logicComponent);
	logicComponent->attachOwner(this);

	this->collider = new Collider("GoalLineCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(collider);
}


void GoalLineObject::onCollisionEnter(AGameObject* contact)
{
	if (contact->getName().find("EnemyCar") != std::string::npos ||
		contact->getName().find("Obstacle") != std::string::npos ||
		contact->getName().find("CarFuel") != std::string::npos)
	{
		this->collider->setAlreadyCollided(false);
	}
}


void GoalLineObject::onCollisionExit(AGameObject* gameOBject)
{
	PhysicsManager::getInstance()->untrackObject(this->collider);
}