#pragma once

#include "GameObjectPool.h"

typedef std::unordered_map<std::string, GameObjectPool*> PoolMap;

class ObjectPoolHolder : sf::NonCopyable
{
// Methods
public:
	static ObjectPoolHolder* getInstance();

	void registerObjectPool(GameObjectPool* pool);
	void unregisterObjectPool(GameObjectPool* pool);
	GameObjectPool* getPool(std::string tag);

private:
	ObjectPoolHolder() {};


// Attributes
public:
	// pool names
	//
	//

private:
	static ObjectPoolHolder* sharedInstance;

	PoolMap poolMap;
};