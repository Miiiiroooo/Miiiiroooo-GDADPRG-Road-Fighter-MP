#pragma once

#include "AComponent.h"
#include "GameManager.h"

class CarFuelSpawner : public AComponent
{
public:
	CarFuelSpawner(std::string name, int numCars);
	~CarFuelSpawner();

	void perform();
	void setRoadEdges(int left, int right);


private:
	const float MAX_DISTANCE_SPAWN = 2750.0f;
	float posLastSpawn = 0.0f;   // position of the last object spawned

	int leftEdge = 0;
	int rightEdge = 0;

	GameManager* gameManager;
};

