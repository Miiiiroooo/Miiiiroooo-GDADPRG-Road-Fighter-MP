#pragma once

#include "AComponent.h"
#include "GameManager.h"

class ObstacleSpawner : public AComponent
{
public:
	ObstacleSpawner(std::string name, int numObstacles);
	~ObstacleSpawner();

	void perform();
	void setRoadEdges(int left, int right);


private:
	const float MAX_DISTANCE_SPAWN = 1450.0f;
	float posLastSpawn = 0.0f;   // position of the last object spawned

	int leftEdge = 0;
	int rightEdge = 0;

	GameManager* gameManager;
};

