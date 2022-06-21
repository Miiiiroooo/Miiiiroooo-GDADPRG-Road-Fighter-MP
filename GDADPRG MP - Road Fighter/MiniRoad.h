#pragma once

#include "AGameObject.h"

class MiniRoad : public AGameObject
{
public:
	MiniRoad(std::string name);
	~MiniRoad();

	void initialize();
};

