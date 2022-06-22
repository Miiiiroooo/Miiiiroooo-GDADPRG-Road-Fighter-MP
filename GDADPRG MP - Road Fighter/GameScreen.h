#pragma once

#include "AGameObject.h"
#include "GameManager.h"

class GameScreen : public AGameObject
{
public:
	GameScreen(std::string name);
	~GameScreen();

	void initialize();
	void update(sf::Time deltaTime);

	void onGameOver();
	void onTrasition();


private:
	GameManager* gameManager = NULL;

	sf::Sound* gameOverTune = NULL;
	const sf::Time gameOverDuration = sf::seconds(5.0f);
	sf::Time elapsedGameOver = sf::seconds(0.0f);
	bool isGameOver = false;
};

