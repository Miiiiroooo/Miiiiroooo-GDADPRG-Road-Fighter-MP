#pragma once

#include "AGameObject.h"
#include "UIText.h"

class ScoreScreen : public AGameObject
{
public:
	ScoreScreen(std::string name);
	~ScoreScreen();

	void initialize();
	void update(sf::Time deltaTime);

private:
	void onTransition();


private:
	UIText* scoreText = NULL;
	UIText* highscoreText = NULL;

	bool isTransitioning = NULL;
	const float screenDuration = 5.0f;
	float elapsed = 0.0f;
};

