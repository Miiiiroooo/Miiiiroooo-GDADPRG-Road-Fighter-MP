#pragma once

#include "APoolable.h"
#include "Collider.h"
#include "CollisionListener.h"

class ObstacleObject : public APoolable, public CollisionListener
{
public:
	ObstacleObject(std::string name);
	~ObstacleObject();

	void initialize();
	void initTexture();

	void onRelease();
	void onActivate();
	APoolable* clone();

	bool hasBeenCrashed();
	void onCollisionEnter(AGameObject* contact);
	void onCollisionExit(AGameObject* gameObject);


private:
	std::vector<sf::Texture*> obstacleTextureList;
	bool crashed = false;
	Collider* collider = NULL;
};

