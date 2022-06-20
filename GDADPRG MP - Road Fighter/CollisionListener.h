#pragma once

#include "AGameObject.h"

class CollisionListener
{
public:
	virtual void onCollisionEnter(AGameObject* gameObject) = 0;
	virtual void onCollisionExit(AGameObject* gameObject) = 0;

protected:
	CollisionListener() {};
};