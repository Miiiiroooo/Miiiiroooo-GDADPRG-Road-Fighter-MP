#include "stdafx.h"
#include "AComponent.h"

// constructor and destructor of the AComponent Class
AComponent::AComponent(std::string name, ComponentType type)
{
	this->name = name;
	this->owner = NULL;
	this->type = type;
}

AComponent::~AComponent()
{
	this->owner = NULL;
	this->type = NotSet;
}


// public methods of the AComponent Class
void AComponent::attachOwner(AGameObject* object)
{
	this->owner = object;
}


void AComponent::detachOwner()
{
	delete this;
}


AGameObject* AComponent::getOwner()
{
	return this->owner;
}


AComponent::ComponentType AComponent::getType()
{
	return this->type;
}


std::string AComponent::getName()
{
	return this->name;
}


void AComponent::setDeltaTime(sf::Time deltaTime)
{
	this->deltaTime = deltaTime;
}