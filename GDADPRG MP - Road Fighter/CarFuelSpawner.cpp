#include "stdafx.h"
#include "CarFuelSpawner.h"
#include "ObjectPoolHolder.h"
#include "CarFuelObject.h"
#include "PhysicsManager.h"


// constructor and desctructor of the CarFuelSpawner Class
CarFuelSpawner::CarFuelSpawner(std::string name, int numCars) : AComponent(name, Script)
{
	GameObjectPool* carFuelPool = new GameObjectPool(ObjectPoolHolder::CAR_FUEL_POOL_TAG, new CarFuelObject("CarFuel"), numCars, this->getOwner());
	carFuelPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(carFuelPool);

	gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
}


CarFuelSpawner::~CarFuelSpawner()
{

}


// public methods of the CarFuelSpawner Class
void CarFuelSpawner::perform()
{
	GameObjectPool* carFuelPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::CAR_FUEL_POOL_TAG);

	bool ifSpawn = (gameManager->getDistance() - posLastSpawn) > MAX_DISTANCE_SPAWN;
	if (ifSpawn && !gameManager->crashed() && gameManager->getSpeed() != 0)
	{
		posLastSpawn += gameManager->getDistance() - posLastSpawn;
		APoolable* poolableObj = carFuelPool->requestPoolable();

		if (poolableObj != NULL)
		{
			// set position of the poolable object
			int randX = rand() % (rightEdge - leftEdge) + leftEdge;
			poolableObj->setPosition((float)randX, -30.0f);


			// update phsyics manager
			Collider* collider = (Collider*)poolableObj->findComponentByName("CarFuelCollider");
			PhysicsManager::getInstance()->trackObject(collider);
		}
	}
}


void CarFuelSpawner::setRoadEdges(int left, int right)
{
	this->leftEdge = left;
	this->rightEdge = right;
}