#include "stdafx.h"
#include "GameScreen_2.h"

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
#include "CrashComponent.h"
#include "CarFuelSpawner.h"
#include "PlayerSoundHandler.h"


// constructor and destructor of the GameScreen Class
GameScreen_2::GameScreen_2(std::string name) : AGameObject(name)
{

}


GameScreen_2::~GameScreen_2()
{
	if (this->goalTune != NULL)
	{
		delete this->goalTune;
		this->goalTune = NULL;
	}

	if (this->gameOverTune != NULL)
	{
		delete this->gameOverTune;
		this->gameOverTune = NULL;
	}
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

	CarFuelSpawner* fuelSpawner = new CarFuelSpawner("Fuel Spawner", 2);
	spawner->attachComponent(fuelSpawner);
	fuelSpawner->attachOwner(spawner);


	//set road hitbox
	CrashComponent* crashComponent = (CrashComponent*)player->findComponentByName("CrashComponent");
	crashComponent->setRoadEdges(860, 1060);
	obstacleSpawner->setRoadEdges(885, 1035);
	enemyCarSpawner->setRoadEdges(885, 1035);
	fuelSpawner->setRoadEdges(885, 1035);

	
	// init Physics
	EmptyGameObject* physicsManager = new EmptyGameObject("PhysicsManager");
	this->attachChild(physicsManager);
	PhysicsManager::getInstance()->initialize("physics_script", physicsManager);

	Collider* playerCollider = (Collider*)player->findComponentByName("PlayerCollider");
	PhysicsManager::getInstance()->trackObject(playerCollider);
}


void GameScreen_2::update(sf::Time deltaTime)
{
	// check if player has reached a certain distance to spawn the goal line
	if (gameManager->getDistance() > 55000 && !isGoalLineSpawned)
	{
		spawnGoalLine();
	}


	// check if game is still running
	if (!gameManager->checkGameOver() && !gameManager->checkGoal())
	{
		for (size_t i = 0; i < childList.size(); i++)
		{
			childList[i]->update(deltaTime);
		}
	}
	// check if player reached goal
	else if (gameManager->checkGoal())
	{
		if (elapsedGoal > goalDuration)
		{
			onTrasition();
		}
		else
		{
			elapsedGoal += deltaTime;
			onGoal();
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


void GameScreen_2::spawnGoalLine()
{
	GoalLineObject* goalLine = new GoalLineObject("GoalLine", 0.7f);
	GameObjectManager::getInstance()->addObject(goalLine);
	goalLine->getTransformable()->setPosition(Game::WINDOW_WIDTH / 2, -500);

	isGoalLineSpawned = true;
}


void GameScreen_2::onGoal()
{
	if (!isGoal) // a flag that prevents repetitive declarations of the following objects and components
	{
		// init audio
		sf::SoundBuffer* buffer = SFXManager::getInstance()->getAudio("Goal");
		this->goalTune = new sf::Sound();
		goalTune->setBuffer(*buffer);
		goalTune->play();


		PlayerSoundHandler* soundHandler = (PlayerSoundHandler*)GameObjectManager::getInstance()->findObjectByName("Player")->findComponentByName("SoundHandler");
		if (soundHandler == nullptr)
		{
			cout << "null";
		}
		soundHandler->EnableSound(false);


		// init goal UI
		this->goalUI = new BasicUIObject("GoalUI", "GoalHUD", 0.8f);
		GameObjectManager::getInstance()->addObject(goalUI);
		goalUI->setParent(this);
		goalUI->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 - 200);


		// update score and goal flag
		int fuelScore = gameManager->getFuel() * 100;
		ScoreManager::getInstance()->updateScore(gameManager->getScore() + fuelScore);
		ScoreManager::getInstance()->decideHighScore();
		ScoreManager::getInstance()->updateFile();

		isGoal = true;
	}
}


void GameScreen_2::onGameOver()
{
	if (!isGameOver) // a flag that prevents repetitive declarations of the following objects and components
	{
		// init audio
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


		// init gameover text
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


void GameScreen_2::onTrasition()
{
	if (!isTransitioning)
	{
		BlackScreen* blackScreen = new BlackScreen("BlackScreen", SceneManager::SCORE_SCREEN_NAME);
		GameObjectManager::getInstance()->addObject(blackScreen);

		isTransitioning = true;
	}
}