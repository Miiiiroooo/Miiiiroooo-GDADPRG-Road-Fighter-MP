#pragma once

#include "AGameObject.h"
#include "CollisionListener.h"
#include "Collider.h"

class Player : public AGameObject, public CollisionListener
{
public:
	Player(std::string name);
	void initialize();

	void setNormalTexture();
	void setCrashedTexture();

	bool hasCarCrashed();

	void onCollisionEnter(AGameObject* contact);
	void onCollisionExit(AGameObject* gameObject);

private:
	const float SPEED_MULTIPLIER = 100.0f;
	sf::Texture* normalTexture;
	sf::Texture* crashedTexture;
		
	bool carCrash = false;
	Collider* collider;
};

