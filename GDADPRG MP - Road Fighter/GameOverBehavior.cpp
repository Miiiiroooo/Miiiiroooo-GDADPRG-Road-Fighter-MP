#include "stdafx.h"
#include "GameOverBehavior.h"
#include "GameScreen.h"
#include "SFXManager.h"


// constructor and destructor of the GameOverBehavior Class
GameOverBehavior::GameOverBehavior(std::string name) : AComponent(name, Script)
{

}


GameOverBehavior::~GameOverBehavior()
{

}


// public methods of the GameOverBehavior Class
void GameOverBehavior::perform()
{
	elapsedGameOver += this->deltaTime;

	/*
	if (!isAudioPlayed)
	{
		sf::SoundBuffer* buffer = SFXManager::getInstance()->getAudio("GameOver");
		sf::Sound gameOverTune;
		gameOverTune.setBuffer(*buffer);
		gameOverTune.play();  // fix audio, possible interruptions from game loop

		isAudioPlayed = true;
	}
	*/

	if (elapsedGameOver > gameOverDuration)
	{
		GameScreen* owner = (GameScreen*)this->getOwner();
		owner->onTrasition();
	}
}