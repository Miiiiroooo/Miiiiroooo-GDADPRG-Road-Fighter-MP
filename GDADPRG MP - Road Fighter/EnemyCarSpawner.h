#pragma once

#include "AComponent.h"
#include "GameManager.h"

class EnemyCarSpawner : public AComponent
{
public:
	EnemyCarSpawner(std::string name, int numCars);
	~EnemyCarSpawner();

	void perform();


private:
	const float MAX_DISTANCE_SPAWN = 1000.0f;
	float posLastSpawn = 0.0f;   // position of the last object spawned

	GameManager* gameManager;
};

