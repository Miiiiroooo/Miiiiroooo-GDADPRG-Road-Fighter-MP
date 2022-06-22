#pragma once

#include "APoolable.h"
#include "Collider.h"
#include "CollisionListener.h"

class EnemyCarObject : public APoolable, public CollisionListener
{
public:
	EnemyCarObject(std::string name);
	~EnemyCarObject();

	void initialize();
	void initTexture();

	void onRelease();
	void onActivate();
	APoolable* clone();

	bool hasBeenCrashed();
	void onCollisionEnter(AGameObject* contact);
	void onCollisionExit(AGameObject* gameObject);


private:
	std::vector<sf::Texture*> enemyCarsTextureList;
	bool crashed = false;
	Collider* collider = NULL;
};

