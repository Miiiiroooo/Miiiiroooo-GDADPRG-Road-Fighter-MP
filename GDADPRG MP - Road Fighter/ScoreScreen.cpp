#include "stdafx.h"
#include "ScoreScreen.h"
#include "ScoreManager.h"
#include "Game.h"
#include "BlackScreen.h"


// constructor and destructor of the ScoreScreen Class
ScoreScreen::ScoreScreen(std::string name) : AGameObject(name)
{

}


ScoreScreen::~ScoreScreen()
{

}


// public methods of the ScoreScreen Class
void ScoreScreen::initialize()
{
	// init score
	this->scoreText = new UIText("ScoreText");
	this->scoreText->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 - 100);
	this->attachChild(this->scoreText);
	this->scoreText->setSize(120);

	int score = ScoreManager::getInstance()->getScore();
	std::string scoreString = "Score  " + std::to_string(score);
	this->scoreText->setText(scoreString);


	// init highscore
	this->highscoreText = new UIText("HighscoreText");
	this->highscoreText->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 + 100);
	this->attachChild(this->highscoreText);
	this->highscoreText->setSize(120);

	int highscore = ScoreManager::getInstance()->getHighScore();
	std::string highscoreString = "HighScore  " + std::to_string(highscore);
	this->highscoreText->setText(highscoreString);
}


void ScoreScreen::update(sf::Time deltaTime)
{
	ScoreManager::getInstance()->updateScore(0);

	if (elapsed < screenDuration)
	{
		elapsed += deltaTime.asSeconds();
	}
	else
	{
		onTransition();
	}
}


void ScoreScreen::onTransition()
{
	if (!isTransitioning)
	{
		BlackScreen* blackScreen = new BlackScreen("BlackScreen", SceneManager::MAIN_MENU_SCREEN_NAME);
		GameObjectManager::getInstance()->addObject(blackScreen);

		isTransitioning = true;
	}
}