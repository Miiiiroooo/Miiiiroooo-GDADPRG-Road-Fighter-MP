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

	//std::cout << "TRACKED: " << trackedObjects.back()->getOwner()->getName() << "  " << trackedObjects.size() << std::endl;
}


void PhysicsManager::untrackObject(Collider* object)
{
	this->forCleaningObjects.push_back(object);

	//std::cout << "CLEANED: " <<  forCleaningObjects.back()->getOwner()->getName() << "  " << forCleaningObjects.size() << std::endl;
}


void PhysicsManager::perform()
{
	for (size_t i = 0; i < this->trackedObjects.size(); i++)
	{
		for (size_t j = 0; j < this->trackedObjects.size(); j++)
		{
			if (this->trackedObjects[i] != this->trackedObjects[j] && this->trackedObjects[i]->getOwner()->isEnabled() && this->trackedObjects[j]->getOwner()->isEnabled())
			{
				// check collision between two objects 
				if (this->trackedObjects[i]->willCollide(this->trackedObjects[j]) && !this->trackedObjects[i]->alreadyCollided() && !this->trackedObjects[j]->alreadyCollided())
				{
					this->trackedObjects[i]->setAlreadyCollided(true);
					this->trackedObjects[j]->setAlreadyCollided(true);

					this->trackedObjects[i]->collisionEnter(this->trackedObjects[j]->getOwner());
					this->trackedObjects[j]->collisionEnter(this->trackedObjects[i]->getOwner());
				}
				else if (!this->trackedObjects[i]->willCollide(this->trackedObjects[j]) && this->trackedObjects[i]->alreadyCollided() && this->trackedObjects[j]->alreadyCollided())
				{
					this->trackedObjects[i]->setAlreadyCollided(false);
					this->trackedObjects[j]->setAlreadyCollided(false);

					this->trackedObjects[i]->collisionExit(this->trackedObjects[j]->getOwner());
					this->trackedObjects[j]->collisionExit(this->trackedObjects[i]->getOwner());
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
		for (size_t j = 0; j < this->trackedObjects.size(); j++)
		{
			if (forCleaningObjects[i] == trackedObjects[j])
			{
				//std::cout << this->forCleaningObjects[i]->getOwner()->getName() << " has been cleaned" << std::endl;
				this->trackedObjects.erase(this->trackedObjects.begin() + j);
			}
		}
	}

	this->forCleaningObjects.clear();
	//std::cout << "size of tracked objects: " << trackedObjects.size() << std::endl;
	//std::cout << "size of cleaned objects: " << forCleaningObjects.size() << std::endl;
}