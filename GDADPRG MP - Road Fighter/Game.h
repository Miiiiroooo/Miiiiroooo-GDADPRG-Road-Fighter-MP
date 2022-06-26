#pragma once

#include "SceneManager.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "SFXManager.h"
#include "PhysicsManager.h"
#include "FontManager.h"
#include "ScoreManager.h"

class Game
{
// methods of the Game Class
public:
	Game();
	~Game();

	void run();

private:
	void processInputs();
	void update(sf::Time);
	void render();
	
// attributes of the Game Class
public:
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

private:
	const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
	sf::RenderWindow m_Window;
};

