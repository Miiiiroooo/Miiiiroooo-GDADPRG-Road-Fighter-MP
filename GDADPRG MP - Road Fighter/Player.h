#pragma once

#include "AGameObject.h"
#include "CollisionListener.h"
#include "Collider.h"
#include "PlayerSoundHandler.h"

class Player : public AGameObject, public CollisionListener
{
public:
	Player(std::string name);
	void initialize();

	void setNormalTexture();
	void setCrashedTexture();

	void removeRenderer();
	void attachRenderer();

	void onCollisionEnter(AGameObject* contact);
	void onCollisionExit(AGameObject* gameObject);


private:
	const float SPEED_MULTIPLIER = 100.0f;
	sf::Texture* normalTexture = NULL;
	sf::Texture* crashedTexture = NULL;

	Renderer* renderComponent = NULL;
	bool hasRenderer = false;
	
	Collider* collider = NULL;
};

