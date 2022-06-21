#include "stdafx.h"
#include "GameScreen.h"

#include "Game.h"
#include "GameManager.h"
#include "UIGameManager.h"
#include "GameObjectManager.h"
#include "SceneManager.h"

#include "Player.h"
#include "Background.h"
#include "BlackScreen.h"

#include "GameOverBehavior.h"

// constructor and destructor of the GameScreen Class
GameScreen::GameScreen(std::string name) : AGameObject(name)
{

}


GameScreen::~GameScreen()
{

}


// public methods of the GameScreen Class
void GameScreen::initialize()
{
	GameManager* gameManager = new GameManager("GameManager");
	GameObjectManager::getInstance()->addObject(gameManager);

	UIGameManager* UIManager = new UIGameManager("UIGameManager");
	GameObjectManager::getInstance()->addObject(UIManager);

	Background* background = new Background("Background");
	GameObjectManager::getInstance()->addObject(background);

	Player* player = new Player("Player");
	GameObjectManager::getInstance()->addObject(player);

	gameManager->setPlayer(player);
}


void GameScreen::onGameOver()
{
	if (!isGameOver) // a flag that prevents repetitive declarations of the following objects and components
	{
		UIText* gameOverText = new UIText("GameOver");
		GameObjectManager::getInstance()->addObject(gameOverText);
		gameOverText->setParent(this);
		gameOverText->setSize(100);
		gameOverText->setText("GAME\nOVER");
		gameOverText->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

		GameOverBehavior* logicComponent = new GameOverBehavior("GameOver");
		this->attachComponent(logicComponent);
		logicComponent->attachOwner(this);

		isGameOver = true;
	}
}


void GameScreen::onTrasition()
{
	BlackScreen* blackScreen = new BlackScreen("BlackScreen", SceneManager::MAIN_MENU_SCREEN_NAME);
	GameObjectManager::getInstance()->addObject(blackScreen);
}