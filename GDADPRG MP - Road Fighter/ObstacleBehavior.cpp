#include "stdafx.h"
#include "ObstacleBehavior.h"
#include "GameObjectManager.h"
#include "ObstacleObject.h"
#include "ObjectPoolHolder.h"


// constructor and destructor of the ObstacleBehavior Class
ObstacleBehavior::ObstacleBehavior(std::string name) : AComponent(name, Script)
{

}


ObstacleBehavior::~ObstacleBehavior()
{

}


// public methods of the ObstacleBehavior class
void ObstacleBehavior::perform()
{
	gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
	ObstacleObject* obstacle = (ObstacleObject*)this->getOwner();

	// check any car crash crashed on the obstacle
	if (obstacle->hasBeenCrashed())
	{
		crashDuration += deltaTime.asSeconds();

		if (crashDuration > 2.0f)
		{
			GameObjectPool* obstaclePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::OBSTACLE_POOL_TAG);
			obstaclePool->releasePoolable(obstacle);

			crashDuration = 0.0f;
			obstacle->onCollisionExit(NULL);
		}
	}

	// check if obstacle is out of bounds
	else if (obstacle->getTransformable()->getPosition().y >= 750)
	{
		GameObjectPool* obstaclePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::OBSTACLE_POOL_TAG);
		obstaclePool->releasePoolable(obstacle);
	}

	// check if player has been crashed already before spawning an object
	else if (!gameManager->crashed() && gameManager->getSpeed() != 0)
	{
		float SPEED_MULTIPLIER = gameManager->getSpeed();
		float scrollSpeed;

		if (SPEED_MULTIPLIER <= 0)
		{
			scrollSpeed = 0;
		}
		else
		{
			scrollSpeed = (float)pow(SPEED_MULTIPLIER, 1.2);
		}

		obstacle->getTransformable()->move(0, scrollSpeed * deltaTime.asSeconds());
	}
}