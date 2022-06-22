#pragma once

#include "AComponent.h"
#include "GameManager.h"

class ObstacleSpawner : public AComponent
{
public:
	ObstacleSpawner(std::string name, int numObstacles);
	~ObstacleSpawner();

	void perform();


private:
	const float MAX_DISTANCE_SPAWN = 1000.0f;
	float posLastSpawn = 0.0f;   // position of the last object spawned

	GameManager* gameManager;
};

