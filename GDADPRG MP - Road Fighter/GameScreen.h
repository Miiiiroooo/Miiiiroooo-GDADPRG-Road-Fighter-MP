#pragma once

#include "AGameObject.h"
#include "GameManager.h"
#include "BasicUIObject.h"
#include "UIText.h"

class GameScreen : public AGameObject
{
public:
	GameScreen(std::string name);
	~GameScreen();

	void initialize();
	void spawnGoalLine();
	void update(sf::Time deltaTime);

	void onCheckpoint();
	void onGameOver();
	void onTrasition();


private:
	GameManager* gameManager = NULL;

	// checkpoint
	bool isGoalLineSpawned = false;

	const sf::Time checkpointDuration = sf::seconds(7.0f);
	sf::Time elapsedCheckpoint = sf::seconds(0.0f);
	bool isCheckpoint = false;

	sf::Sound* checkpointTune = NULL;
	BasicUIObject* checkpointUI = NULL;

	// gameover
	const sf::Time gameOverDuration = sf::seconds(5.0f);
	sf::Time elapsedGameOver = sf::seconds(0.0f);

	bool isGameOver = false;
	sf::Sound* gameOverTune = NULL;
	UIText* gameOverText = NULL;

	// transition
	bool isTransition = false;
};

