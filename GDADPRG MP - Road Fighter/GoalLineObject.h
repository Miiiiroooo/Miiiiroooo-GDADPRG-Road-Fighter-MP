#pragma once

#include "AGameObject.h"

class GoalLineObject : public AGameObject
{
public:
	GoalLineObject(std::string name, float scaleValue);
	~GoalLineObject();

	void initialize();


private:
	float scaleValue = 0.0f;
};

