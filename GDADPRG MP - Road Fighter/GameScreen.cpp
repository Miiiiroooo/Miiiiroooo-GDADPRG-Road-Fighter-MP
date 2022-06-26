#include "stdafx.h"
#include "GameScreen.h"

// Managers
#include "Game.h"
#include "GameManager.h"
#include "UIGameManager.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "SFXManager.h"
#include "PhysicsManager.h"
#include "ScoreManager.h"

// Objects
#include "Player.h"
#include "Background.h"
#include "BlackScreen.h"
#include "EmptyGameObject.h"
#include "GoalLineObject.h"

// Scripts
#include "ObstacleSpawner.h"
#include "EnemyCarSpawner.h"
#include "CarFuelSpawner.h"
#include "CrashComponent.h"
#include "PlayerSoundHandler.h"


// constructor and destructor of the GameScreen Class
GameScreen::GameScreen(std::string name) : AGameObject(name)
{

}


GameScreen::~GameScreen()
{
	if (this->checkpointTune != NULL)
	{
		delete this->checkpointTune;
		this->checkpointTune = NULL;
	}

	if (this->gameOverTune != NULL)
	{
		delete this->gameOverTune;
		this->gameOverTune = NULL;
	}
}


// public methods of the GameScreen Class
void GameScreen::initialize()
{
	// basic objects needed for gameplay
	this->gameManager = new GameManager("GameManager");
	GameObjectManager::getInstance()->addObject(gameManager);

	Background* background = new Background("Background");
	background->setTexture(TextureManager::getInstance()->getTexture("background"));
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

	EnemyCarSpawner* enemyCarSpawner = new EnemyCarSpawner("EnemyCarSpawner", 12);
	spawner->attachComponent(enemyCarSpawner);
	enemyCarSpawner->attachOwner(spawner);

	CarFuelSpawner* fuelSpawner = new CarFuelSpawner("Fuel Spawner", 2);
	spawner->attachComponent(fuelSpawner);
	fuelSpawner->attachOwner(spawner);

	//set road hitbox
	CrashComponent* crashComponent = (CrashComponent*)player->findComponentByName("CrashComponent");
	crashComponent->setRoadEdges(820, 1100);
	obstacleSpawner->setRoadEdges(845, 1075);
	enemyCarSpawner->setRoadEdges(845, 1075);
	fuelSpawner->setRoadEdges(845, 1075);

	// init Physics
	EmptyGameObject* physicsManager = new EmptyGameObject("PhysicsManager");
	this->attachChild(physicsManager);
	PhysicsManager::getInstance()->initialize("physics_script", physicsManager);

	Collider* playerCollider = (Collider*)player->findComponentByName("PlayerCollider");
	PhysicsManager::getInstance()->trackObject(playerCollider);
}


void GameScreen::update(sf::Time deltaTime)
{
	// check if player has reached a certain distance to spawn the goal line
	if (gameManager->getDistance() > 55000 && !isGoalLineSpawned)
	{
		spawnGoalLine();
	}


	// check if game still ongoing
	if (!gameManager->checkGameOver() && !gameManager->checkGoal())
	{
		for (size_t i = 0; i < childList.size(); i++)
		{
			childList[i]->update(deltaTime);
		}
	}
	// check if player reached checkpoint
	else if (gameManager->checkGoal())
	{
		if (elapsedCheckpoint > checkpointDuration)
		{
			onTrasition();
		}
		else
		{
			elapsedCheckpoint += deltaTime;
			onCheckpoint();
		}
	}
	// check if gameover
	else if (gameManager->checkGameOver())
	{
		if (elapsedGameOver > gameOverDuration)
		{
			onTrasition();
		}
		else
		{
			elapsedGameOver += deltaTime;
			onGameOver();
		}
	}
}


void GameScreen::spawnGoalLine()
{
	GoalLineObject* goalLine = new GoalLineObject("GoalLine", 0.8f);
	GameObjectManager::getInstance()->addObject(goalLine);
	goalLine->getTransformable()->setPosition(Game::WINDOW_WIDTH / 2, -500);

	isGoalLineSpawned = true;
}


void GameScreen::onCheckpoint()
{
	if (!isCheckpoint)  // a flag that prevents repetitive declarations of the following objects and components
	{
		sf::SoundBuffer* buffer = SFXManager::getInstance()->getAudio("Checkpoint");
		this->checkpointTune = new sf::Sound();
		checkpointTune->setBuffer(*buffer);
		checkpointTune->play();


		PlayerSoundHandler* soundHandler = (PlayerSoundHandler*)GameObjectManager::getInstance()->findObjectByName("Player")->findComponentByName("SoundHandler");
		if (soundHandler == nullptr)
		{
			cout << "null";
		}
		soundHandler->EnableSound(false);


		this->checkpointUI = new BasicUIObject("CheckpointUI", "CheckpointHUD", 0.8f);
		GameObjectManager::getInstance()->addObject(checkpointUI);
		checkpointUI->setParent(this);
		checkpointUI->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 - 200);


		// update score and checkpoint flag
		int fuelScore = gameManager->getFuel() * 100;
		ScoreManager::getInstance()->updateScore(gameManager->getScore() + fuelScore);

		isCheckpoint = true;
	}
}


void GameScreen::onGameOver()
{
	if (!isGameOver) // a flag that prevents repetitive declarations of the following objects and components
	{
		// init game over tune
		sf::SoundBuffer* buffer = SFXManager::getInstance()->getAudio("GameOver");
		this->gameOverTune = new sf::Sound();
		gameOverTune->setBuffer(*buffer);
		gameOverTune->play();


		PlayerSoundHandler* soundHandler = (PlayerSoundHandler*)GameObjectManager::getInstance()->findObjectByName("Player")->findComponentByName("SoundHandler");
		if (soundHandler == nullptr)
		{
			cout << "null";
		}
		soundHandler->EnableSound(false);


		// init game over text
		this->gameOverText = new UIText("GameOver");
		GameObjectManager::getInstance()->addObject(gameOverText);
		gameOverText->setParent(this);
		gameOverText->setSize(100);
		gameOverText->setText("GAME\nOVER");
		gameOverText->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);		


		// update score and gameover flag
		ScoreManager::getInstance()->updateScore(gameManager->getScore());
		ScoreManager::getInstance()->decideHighScore();
		ScoreManager::getInstance()->updateFile();

		isGameOver = true;
	}
}


void GameScreen::onTrasition()
{
	std::string sceneToChange;
	if (gameManager->checkGoal())
		sceneToChange = SceneManager::COURSE_TWO_NAME;
	else if (gameManager->checkGameOver())
		sceneToChange = SceneManager::SCORE_SCREEN_NAME;


	if (!isTransitioning)
	{
		BlackScreen* blackScreen = new BlackScreen("BlackScreen", sceneToChange);
		GameObjectManager::getInstance()->addObject(blackScreen);

		isTransitioning = true;
	}
}