#pragma once

#include "AComponent.h"
#include "GameManager.h"

class EnemyCarSpawner : public AComponent
{
public:
	EnemyCarSpawner(std::string name, int numCars);
	~EnemyCarSpawner();

	void perform();
	void setRoadEdges(int left, int right);


private:
	const float MAX_DISTANCE_SPAWN = 650.0f;
	float posLastSpawn = 0.0f;   // position of the last object spawned

	int leftEdge = 0;
	int rightEdge = 0;

	GameManager* gameManager;
};

