#include "stdafx.h"
#include "EnemyCarBehavior.h"
#include "GameObjectManager.h"
#include "EnemyCarObject.h"
#include "ObjectPoolHolder.h"


// constructor and destructor of the EnemyCarBehavior Class
EnemyCarBehavior::EnemyCarBehavior(std::string name) : AComponent(name, Script)
{

}


EnemyCarBehavior::~EnemyCarBehavior()
{

}


// oublic methods of the EnemyCarBehavior Class
void EnemyCarBehavior::perform()
{
	gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
	EnemyCarObject* enemyCar = (EnemyCarObject*)this->getOwner();

	// check for car crash
	if (enemyCar->hasBeenCrashed())
	{
		crashDuration += deltaTime.asSeconds();

		if (crashDuration > 2.0f)
		{
			GameObjectPool* obstaclePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG);
			obstaclePool->releasePoolable(enemyCar);

			crashDuration = 0.0f;
			enemyCar->onCollisionExit(NULL);
		}
	}

	// check if enemy car is out of bounds
	else if (enemyCar->getTransformable()->getPosition().y >= 750)
	{
		GameObjectPool* obstaclePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG);
		obstaclePool->releasePoolable(enemyCar);
	}

	// check if car stopped before spawning an object
	else if (!gameManager->crashed() && gameManager->getSpeed() != 0)
	{
		float SPEED_MULTIPLIER = gameManager->getSpeed();
		float scrollSpeed;

		if (SPEED_MULTIPLIER < 0)
		{
			scrollSpeed = 0;
		}
		else
		{
			scrollSpeed = pow(SPEED_MULTIPLIER, 0.9);
		}

		enemyCar->getTransformable()->move(0, scrollSpeed * deltaTime.asSeconds());
	}
}