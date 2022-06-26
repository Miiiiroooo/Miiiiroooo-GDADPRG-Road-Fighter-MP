#pragma once

#include "AComponent.h"
#include "GameManager.h"

class RespawnBehavior : public AComponent
{
public:
	RespawnBehavior(std::string name);
	~RespawnBehavior();

	void perform();
	void reset();


private:
	const float iframeDuration = 5.0f; // invincibility frames before setting up player collider
	float elapsedIframes = 0.0f;

	bool isBlinkingIn = false;
	const float blinkOutDuration = 0.2f;
	float elapsedBlinkOut = 0.0f;

	const float blinkInDuration = 0.4f;
	float elapsedBlinkIn = 0.0f;

	GameManager* gameManager = NULL;
};

