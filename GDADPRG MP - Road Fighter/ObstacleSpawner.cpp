#include "stdafx.h"
#include "ObstacleSpawner.h"
#include "ObjectPoolHolder.h"
#include "ObstacleObject.h"
#include "PhysicsManager.h"


// constructor and destructor of the ObstacleSpawner Class
ObstacleSpawner::ObstacleSpawner(std::string name, int numObstacles) : AComponent(name, Script)
{
	GameObjectPool* obstaclePool = new GameObjectPool(ObjectPoolHolder::OBSTACLE_POOL_TAG, new ObstacleObject("Obstacle"), numObstacles, this->getOwner());
	obstaclePool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(obstaclePool);

	gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
}


ObstacleSpawner::~ObstacleSpawner()
{

}


// public methods of the ObstacleSpawner Class

// idea is that the obstacles will spawn on the last third of the course itself
// if player is about to reach end, it increasingly becomes difficult to reach
void ObstacleSpawner::perform()
{
	if (gameManager->getDistance() <= 24000) // if player is still significantly far from the end, dont spawn obstacles yet
	{
		return;
	}

	GameObjectPool* obstaclePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::OBSTACLE_POOL_TAG);

	bool ifSpawn = gameManager->getDistance() - posLastSpawn > MAX_DISTANCE_SPAWN;
	if (ifSpawn && !gameManager->crashed() && gameManager->getSpeed() != 0)
	{
		int randNum = rand() % 10;

		if (randNum < 3)  // 30 % chance obstacle spawn after cooldown
		{
			posLastSpawn += gameManager->getDistance() - posLastSpawn;
			APoolable* poolableObj = obstaclePool->requestPoolable();

			if (poolableObj != NULL) // when obstacle spawn, make PhysicsManager track the object
			{
				Collider* collider = (Collider*)poolableObj->findComponentByName("ObstacleCollider");
				PhysicsManager::getInstance()->trackObject(collider);
			}
		}
	}
}