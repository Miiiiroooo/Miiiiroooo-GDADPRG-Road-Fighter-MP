#pragma once

#include "AGameObject.h"
#include "Collider.h"
#include "CollisionListener.h"

class GoalLineObject : public AGameObject, public CollisionListener
{
public:
	GoalLineObject(std::string name, float scaleValue);
	~GoalLineObject();

	void initialize();

	void onCollisionEnter(AGameObject* contact);
	void onCollisionExit(AGameObject* gameObject);


private:
	float scaleValue = 0.0f;

	Collider* collider = NULL;
};

