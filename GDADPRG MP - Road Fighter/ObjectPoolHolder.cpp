#include "stdafx.h"
#include "ObjectPoolHolder.h"


// static declarations of the ObjectPoolHolder Class
ObjectPoolHolder* ObjectPoolHolder::sharedInstance = NULL;

ObjectPoolHolder* ObjectPoolHolder::getInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new ObjectPoolHolder();
	}

	return sharedInstance;
}


// public methods of the ObjectPoolHolder Class
void ObjectPoolHolder::registerObjectPool(GameObjectPool* pool)
{
	this->poolMap[pool->getTag()] = pool;
}


void ObjectPoolHolder::unregisterObjectPool(GameObjectPool* pool)
{
	this->poolMap.erase(pool->getTag());
	delete pool;
}


GameObjectPool* ObjectPoolHolder::getPool(std::string tag)
{
	return this->poolMap[tag];
}