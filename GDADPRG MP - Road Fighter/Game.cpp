#include "stdafx.h"
#include "Game.h"


// constructor and destructor of the Game Class
Game::Game() : m_Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Road Fighter")
{
	m_Window.setFramerateLimit(60);
	srand(time(NULL));
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
		//SceneManager::getInstance()->checkLoadScene();
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
			//GameManager::getInstance()->processInputs(event);
			break;
		}
	}
}


void Game::update(sf::Time deltaTime)
{
	//GameObjectManager::getInstance()->update(deltaTime);
}


void Game::render()
{
	m_Window.clear();

	//GameObjectManager::getInstance()->draw(&m_Window);

	m_Window.display();
}