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

	// check for self-car crash
	if (enemyCar->hasBeenCrashed())
	{
		crashDuration += deltaTime.asSeconds();

		if (crashDuration > 2.0f)
		{
			GameObjectPool* enemyCarPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG);
			enemyCarPool->releasePoolable(enemyCar);

			crashDuration = 0.0f;
			enemyCar->onCollisionExit(NULL);
		}
	}

	// check if enemy car is out of bounds
	else if (enemyCar->getTransformable()->getPosition().y >= 1200 || enemyCar->getTransformable()->getPosition().y <= -100)
	{
		this->sideTicks = 0;
		GameObjectPool* enemyCarPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG);
		enemyCarPool->releasePoolable(enemyCar);
	}

	// check if player has already crashed before spawning an object
	else if (!gameManager->crashed())
	{
		float player_speed = gameManager->getSpeed();
		float car_speed = 2 * player_speed - enemyCar->getCarSpeed();

		if (this->getOwner()->getSprite()->getTexture() == TextureManager::getInstance()->getTexture("enemy_red_0.png") || 
			this->getOwner()->getSprite()->getTexture() == TextureManager::getInstance()->getTexture("enemy_red_1.png"))
		{
			Player* player = (Player*)GameObjectManager::getInstance()->findObjectByName("Player");
			
			if (enemyCar->getTransformable()->getPosition().y > 600)
			{
				//cout <<  << endl;
				if (enemyCar->getTransformable()->getPosition().x > player->getTransformable()->getPosition().x)
				{
					
					
					if (sideTicks < 1.f)
					{
						enemyCar->getTransformable()->move(-deltaTime.asSeconds() * 100, 0);
						sideTicks += deltaTime.asSeconds();
					}
				}
				else if (enemyCar->getTransformable()->getPosition().x < player->getTransformable()->getPosition().x)
				{
					
					if (sideTicks < 1.f)
					{
						enemyCar->getTransformable()->move(deltaTime.asSeconds() * 100, 0);
						sideTicks += deltaTime.asSeconds();
					}
				}
			}
			
		}
		
		enemyCar->getTransformable()->move(0, car_speed * deltaTime.asSeconds());
	}
}