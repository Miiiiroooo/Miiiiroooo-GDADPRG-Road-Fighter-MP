#pragma once

#include "AGameObject.h"
#include "GameManager.h"
#include "BasicUIObject.h"
#include "UIText.h"

class GameScreen_2 : public AGameObject
{
public:
	GameScreen_2(std::string name);
	~GameScreen_2();

	void initialize();
	void update(sf::Time deltaTime);

	void onGoal();
	void onGameOver();
	void onTrasition();


private:
	GameManager* gameManager = NULL;

	// Goal
	const sf::Time goalDuration = sf::seconds(12.0f);
	sf::Time elapsedGoal = sf::seconds(0.0f);
	bool isGoal = false;

	sf::Sound* goalTune = NULL;
	BasicUIObject* goalUI = NULL;

	// Gameover
	const sf::Time gameOverDuration = sf::seconds(5.0f);
	sf::Time elapsedGameOver = sf::seconds(0.0f);
	
	bool isGameOver = false;
	sf::Sound* gameOverTune = NULL;
	UIText* gameOverText = NULL;

	// transition
	bool isTransition = false;
};

