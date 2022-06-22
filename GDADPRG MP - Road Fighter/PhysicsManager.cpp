#include "stdafx.h"
#include "PhysicsManager.h"

#include<iostream>

using namespace std;


// static declaration of the PhysicsManager Class
PhysicsManager* PhysicsManager::sharedInstance = NULL;

void PhysicsManager::initialize(std::string name, AGameObject* parent)
{
	sharedInstance = new PhysicsManager(name);
	parent->attachComponent(sharedInstance);
}


void PhysicsManager::destroy()
{
	delete sharedInstance;
}


PhysicsManager* PhysicsManager::getInstance()
{
	return sharedInstance;
}


// public methods of the PhysicsManager Class
void PhysicsManager::trackObject(Collider* object)
{
	object->setAlreadyCollided(false);

	this->trackedObjects.push_back(object);
}


void PhysicsManager::untrackObject(Collider* object)
{
	this->forCleaningObjects.push_back(object);
}


void PhysicsManager::perform()
{
	for (size_t i = 0; i < this->trackedObjects.size(); i++)
	{
		for (size_t j = 0; j < this->trackedObjects.size(); j++)
		{
			
			cout << trackedObjects[i]->getName() << endl;
			

			if (this->trackedObjects[i] != this->trackedObjects[j] && this->trackedObjects[i]->getOwner()->isEnabled() && this->trackedObjects[j]->getOwner()->isEnabled())
			{
				//std::cout << this->trackedObjects.size() << " " << this->trackedObjects[i]->willCollide(this->trackedObjects[j]) << " " << !this->trackedObjects[i]->alreadyCollided() << " " << !this->trackedObjects[j]->alreadyCollided() << std::endl;
				

				// check collision between two objects 
				if (this->trackedObjects[i]->willCollide(this->trackedObjects[j]) && !this->trackedObjects[i]->alreadyCollided() && !this->trackedObjects[j]->alreadyCollided())
				{
					this->trackedObjects[i]->collisionEnter(this->trackedObjects[j]->getOwner());
					this->trackedObjects[j]->collisionEnter(this->trackedObjects[i]->getOwner());

					this->trackedObjects[i]->setAlreadyCollided(true);
					this->trackedObjects[j]->setAlreadyCollided(true);
				}
				else if (!this->trackedObjects[i]->willCollide(this->trackedObjects[j]) && this->trackedObjects[i]->alreadyCollided() && this->trackedObjects[j]->alreadyCollided())
				{
					this->trackedObjects[i]->collisionExit(this->trackedObjects[j]->getOwner());
					this->trackedObjects[j]->collisionExit(this->trackedObjects[i]->getOwner());

					this->trackedObjects[i]->setAlreadyCollided(false);
					this->trackedObjects[j]->setAlreadyCollided(false);
				}
			}
		}
	}


	for (size_t i = 0; i < this->trackedObjects.size(); i++)
	{
		//std::cout << this->trackedObjects[i]->getOwner()->getName() << std::endl;
		this->trackedObjects[i]->setChecked(false);
	}

	this->cleanUpObjects();
}


// private methods of the PhysicsManager Class
void PhysicsManager::cleanUpObjects()
{
	for (size_t i = 0; i < this->forCleaningObjects.size(); i++)
	{
		//std::cout << this->trackedObjects[i]->getOwner()->getName() << " has been cleaned" << std::endl;
		this->trackedObjects.erase(this->trackedObjects.begin() + i);
	}

	this->forCleaningObjects.clear();
}