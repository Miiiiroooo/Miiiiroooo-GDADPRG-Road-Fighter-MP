#pragma once

#include "AComponent.h"

class GameOverBehavior : public AComponent
{
public:
	GameOverBehavior(std::string name);
	~GameOverBehavior();

	void perform();


private:
	bool isAudioPlayed = false;
	const sf::Time gameOverDuration = sf::seconds(5);
	sf::Time elapsedGameOver = sf::seconds(0);
};

