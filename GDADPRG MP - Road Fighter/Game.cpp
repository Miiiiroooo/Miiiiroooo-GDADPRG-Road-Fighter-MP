#include "stdafx.h"
#include "Game.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "GameScene_2.h"
#include "LoadingScene.h"
#include "ApplicationManager.h"

// constructor and destructor of the Game Class
Game::Game() : m_Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Road Fighter")
{
	m_Window.setFramerateLimit(60);
	srand(time(NULL));

	ApplicationManager::getInstance()->initialize(&m_Window);
	TextureManager::getInstance()->loadAll();
	FontManager::getInstance()->loadAll();
	TextureManager::getInstance()->loadSpriteSheet();
	SFXManager::getInstance()->loadAll();

	SceneManager::getInstance()->registerScene(new LoadingScene());
	SceneManager::getInstance()->registerScene(new MainMenuScene());
	SceneManager::getInstance()->registerScene(new GameScene());
	SceneManager::getInstance()->registerScene(new GameScene_2());

	//SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCREEN_NAME);
	SceneManager::getInstance()->loadScene(SceneManager::COURSE_TWO_NAME);
}


Game::~Game()
{

}


// public methods of the Game Class
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_Window.isOpen())
	{
		processInputs();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInputs();
			update(TimePerFrame);
		}

		render();
		SceneManager::getInstance()->checkLoadScene();
	}
}


// private methods of the Game Class
void Game::processInputs()
{
	sf::Event event;

	while (m_Window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Window.close();
			break;
		default:
			GameObjectManager::getInstance()->processInput(event);
			break;
		}
	}
}


void Game::update(sf::Time deltaTime)
{
	GameObjectManager::getInstance()->update(deltaTime);
}


void Game::render()
{
	m_Window.clear();

	GameObjectManager::getInstance()->draw(&m_Window);

	m_Window.display();
}