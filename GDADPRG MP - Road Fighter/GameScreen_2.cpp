#include "stdafx.h"
#include "GameScreen_2.h"

#include "Game.h"
#include "GameManager.h"
#include "UIGameManager.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "SFXManager.h"
#include "PhysicsManager.h"

#include "Player.h"
#include "Background.h"
#include "BlackScreen.h"
#include "EmptyGameObject.h"

#include "ObstacleSpawner.h"
#include "EnemyCarSpawner.h"

#include "CrashComponent.h"

// constructor and destructor of the GameScreen Class
GameScreen_2::GameScreen_2(std::string name) : AGameObject(name)
{

}


GameScreen_2::~GameScreen_2()
{
	delete this->gameOverTune;
	this->gameOverTune = NULL;
}


// public methods of the GameScreen Class
void GameScreen_2::initialize()
{
	// basic objects needed for gameplay
	this->gameManager = new GameManager("GameManager");
	GameObjectManager::getInstance()->addObject(gameManager);

	Background* background = new Background("Background");
	background->setTexture(TextureManager::getInstance()->getTexture("CourseTwo"));
	GameObjectManager::getInstance()->addObject(background);

	UIGameManager* UIManager = new UIGameManager("UIGameManager");
	GameObjectManager::getInstance()->addObject(UIManager);

	Player* player = new Player("Player");
	GameObjectManager::getInstance()->addObject(player);
	this->gameManager->setPlayer(player);


	// init spawners for enemies and obstacles
	EmptyGameObject* spawner = new EmptyGameObject("Spawner");
	this->attachChild(spawner);

	ObstacleSpawner* obstacleSpawner = new ObstacleSpawner("ObstacleSpawner", 3);
	spawner->attachComponent(obstacleSpawner);
	obstacleSpawner->attachOwner(spawner);

	EnemyCarSpawner* enemyCarSpawner = new EnemyCarSpawner("EnemyCarSpawner", 3);
	spawner->attachComponent(enemyCarSpawner);
	enemyCarSpawner->attachOwner(spawner);


	//set road hitbox
	CrashComponent* crashComponent = (CrashComponent*)player->findComponentByName("CrashComponent");
	crashComponent->setRoadEdges(540, 740);
	obstacleSpawner->setRoadEdges(560, 725);
	enemyCarSpawner->setRoadEdges(560, 725);


	// init Physics
	EmptyGameObject* physicsManager = new EmptyGameObject("PhysicsManager");
	this->attachChild(physicsManager);
	PhysicsManager::getInstance()->initialize("physics_script", physicsManager);
	PhysicsManager::getInstance()->attachOwner(physicsManager);

	Collider* playerCollider = (Collider*)player->findComponentByName("PlayerCollider");
	PhysicsManager::getInstance()->trackObject(playerCollider);
}


void GameScreen_2::update(sf::Time deltaTime)
{
	if (!gameManager->checkGameOver())
	{
		for (size_t i = 0; i < childList.size(); i++)
		{
			childList[i]->update(deltaTime);
		}
	}
	else if (elapsedGameOver > gameOverDuration)
	{
		onTrasition();
	}
	else
	{
		elapsedGameOver += deltaTime;

		onGameOver();
	}
}


void GameScreen_2::onGameOver()
{
	if (!isGameOver) // a flag that prevents repetitive declarations of the following objects and components
	{
		UIText* gameOverText = new UIText("GameOver");
		GameObjectManager::getInstance()->addObject(gameOverText);
		gameOverText->setParent(this);
		gameOverText->setSize(100);
		gameOverText->setText("GAME\nOVER");
		gameOverText->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

		/*
		sf::SoundBuffer* buffer = SFXManager::getInstance()->getAudio("GameOver");
		this->gameOverTune = new sf::Sound();
		gameOverTune->setBuffer(*buffer);
		gameOverTune->play();
		*/

		isGameOver = true;
	}
}


void GameScreen_2::onTrasition()
{
	BlackScreen* blackScreen = new BlackScreen("BlackScreen", SceneManager::MAIN_MENU_SCREEN_NAME);
	GameObjectManager::getInstance()->addObject(blackScreen);
}