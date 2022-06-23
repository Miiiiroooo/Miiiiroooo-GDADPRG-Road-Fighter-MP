#pragma once

#include "APoolable.h"
#include "Collider.h"
#include "CollisionListener.h"

class CarFuelObject : public APoolable, public CollisionListener
{
public:
	CarFuelObject(std::string name);
	~CarFuelObject();

	void initialize();

	void playTune();

	void onRelease();
	void onActivate();
	APoolable* clone();

	bool hasBeenCrashed();
	void onCollisionEnter(AGameObject* contact);
	void onCollisionExit(AGameObject* gameObject);


private:
	sf::Sound* scoreTune = NULL;

	Collider* collider = NULL;
	bool crashed = false;
};

