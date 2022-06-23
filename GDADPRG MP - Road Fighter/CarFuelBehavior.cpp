#include "stdafx.h"
#include "CarFuelBehavior.h"
#include "GameObjectManager.h"
#include "CarFuelObject.h"
#include "ObjectPoolHolder.h"


// constructor and destructor of the EnemyCarBehavior Class
CarFuelBehavior::CarFuelBehavior(std::string name) : AComponent(name, Script)
{

}


CarFuelBehavior::~CarFuelBehavior()
{

}


// oublic methods of the EnemyCarBehavior Class
void CarFuelBehavior::perform()
{
	gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
	CarFuelObject* carFuel = (CarFuelObject*)this->getOwner();

	// check for self-car crash or went out-of-bounds
	if (carFuel->hasBeenCrashed() || carFuel->getTransformable()->getPosition().y >= 900 || carFuel->getTransformable()->getPosition().y <= -300)
	{
		if (carFuel->hasBeenCrashed())
			carFuel->playTune();

		gameManager->addFuel(3);
		gameManager->addScore(1000);

		GameObjectPool* carFuelPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::CAR_FUEL_POOL_TAG);
		carFuelPool->releasePoolable(carFuel);
		carFuel->onCollisionExit(NULL);
	}


	// check if player has already crashed before spawning an object
	else if (!gameManager->crashed())
	{
		float player_speed = gameManager->getSpeed();
		float car_speed = 1.6 * player_speed - speed;

		carFuel->getTransformable()->move(0, car_speed * deltaTime.asSeconds());
	}
}