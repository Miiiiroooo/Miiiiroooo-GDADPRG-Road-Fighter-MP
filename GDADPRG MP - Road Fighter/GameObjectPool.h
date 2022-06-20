#pragma once

#include "APoolable.h"
#include "GameObjectManager.h"

typedef std::vector<APoolable*> ObjectList;

class GameObjectPool
{
// methods
public:
	GameObjectPool(std::string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent);
	~GameObjectPool();

	void initialize();
	bool hasObjectAvailable(int requestSize);
	APoolable* requestPoolable();
	ObjectList requestPoolableBatch(int size);
	void releasePoolable(APoolable* poolableObject);
	void releasePoolableBatch(ObjectList objectList);

	std::string getTag();

private:
	void setEnabled(APoolable* poolableObject, bool flag);


// attributes
private:
	std::string tag;
	APoolable* objectCopy = NULL;
	AGameObject* parent = NULL;
	int maxPoolSize = 20;
	ObjectList availableObjects;
	ObjectList usedObjects;
};