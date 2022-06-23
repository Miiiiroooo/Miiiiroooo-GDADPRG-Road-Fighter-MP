#include "stdafx.h"
#include "EnemyCarSpawner.h"
#include "ObjectPoolHolder.h"
#include "EnemyCarObject.h"
#include "PhysicsManager.h"


// constructor and desctructor of the EnemyCarSpawner Class
EnemyCarSpawner::EnemyCarSpawner(std::string name, int numCars) : AComponent(name, Script)
{
	GameObjectPool* obstaclePool = new GameObjectPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG, new EnemyCarObject("EnemyCar"), numCars, this->getOwner());
	obstaclePool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(obstaclePool);

	gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
}


EnemyCarSpawner::~EnemyCarSpawner()
{

}


// public methods of the EnemyCarSpawner Class
void EnemyCarSpawner::perform()
{
	GameObjectPool* enemyCarPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG);

	bool ifSpawn = (gameManager->getDistance() - posLastSpawn) > MAX_DISTANCE_SPAWN;
	if (ifSpawn && !gameManager->crashed() && gameManager->getSpeed() != 0)
	{
		int randNum = rand() % 10;

		if (randNum < 4)  // 40 % chance obstacle spawn after cooldown
		{
			posLastSpawn += gameManager->getDistance() - posLastSpawn;
			APoolable* poolableObj = enemyCarPool->requestPoolable();

			if (poolableObj != NULL) 
			{
				// set position of the poolable object
				int randX = rand() % (rightEdge - leftEdge) + leftEdge;
				poolableObj->setPosition((float)randX, -75.0f);


				// update phsyics manager
				Collider* collider = (Collider*)poolableObj->findComponentByName("EnemyCarCollider");
				PhysicsManager::getInstance()->trackObject(collider);
			}
		}
	}
}


void EnemyCarSpawner::setRoadEdges(int left, int right)
{
	this->leftEdge = left;
	this->rightEdge = right;
}