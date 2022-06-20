#include "stdafx.h"
#include "GameObjectPool.h"


// constructor and destructor of the GameObjectPool Class
GameObjectPool::GameObjectPool(std::string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent)
{
	this->tag = tag;
	this->objectCopy = poolableCopy;
	this->maxPoolSize = poolableSize;
	this->parent = parent;
}


GameObjectPool::~GameObjectPool()
{
	delete this->objectCopy;
	this->objectCopy = NULL;
	this->parent = NULL;
}


// public methods of the GameObjectPool Class
void GameObjectPool::initialize()
{
	for (int i = 0; i < this->maxPoolSize; i++)
	{
		APoolable* poolableObject = this->objectCopy->clone();

		// instantiate object but disable it first
		if (this->parent != NULL)
		{
			this->parent->attachChild(poolableObject);
		}
		else
		{
			GameObjectManager::getInstance()->addObject(poolableObject);
		}

		poolableObject->setEnabled(false);
		this->availableObjects.push_back(poolableObject);
	}
}


bool GameObjectPool::hasObjectAvailable(int requestSize)
{
	return requestSize <= this->availableObjects.size();
}


APoolable* GameObjectPool::requestPoolable()
{
	if (this->hasObjectAvailable(1))
	{
		size_t availableListSize = this->availableObjects.size();

		APoolable* poolableObject = this->availableObjects[availableListSize - 1];
		this->availableObjects.erase(this->availableObjects.begin() + availableListSize - 1);
		this->usedObjects.push_back(poolableObject);
		//std::cout << "Request Object. Available: " << availableListSize - 1 << "   Used: " << this->usedObjects.size() << std::endl;

		this->setEnabled(poolableObject, true);
		return poolableObject;
	}
	else
	{
		//std::cout << "No more poolable " + this->objectCopy->getName() + " available! \n";

		return NULL;
	}
}


ObjectList GameObjectPool::requestPoolableBatch(int size)
{
	ObjectList returnList;

	if (this->hasObjectAvailable(size))
	{
		for (int i = 0; i < size; i++)
		{
			returnList.push_back(this->requestPoolable());
		}
	}
	else
	{
		std::cout << "Insufficient " + this->objectCopy->getName() + " available in pool.\nCount is " << this->availableObjects.size() << " while requested is " << size << std::endl;
	}

	return returnList;
}


void GameObjectPool::releasePoolable(APoolable* poolableObject)
{
	for (size_t i = 0; i < this->usedObjects.size(); i++)
	{
		if (this->usedObjects[i] == poolableObject)
		{
			this->usedObjects.erase(this->usedObjects.begin() + i);
			this->availableObjects.push_back(poolableObject);
			this->setEnabled(poolableObject, false);
		}
	}
}


void GameObjectPool::releasePoolableBatch(ObjectList objectList)
{
	for (size_t i = 0; i < objectList.size(); i++)
	{
		this->releasePoolable(objectList[i]);
	}
}


std::string GameObjectPool::getTag()
{
	return this->tag;
}


// private methods of the GameObjectPool Class
void GameObjectPool::setEnabled(APoolable* poolableObject, bool flag)
{
	if (flag)
	{
		poolableObject->setEnabled(true);
		poolableObject->onActivate();
	}
	else
	{
		poolableObject->setEnabled(false);
		poolableObject->onRelease();
	}
}