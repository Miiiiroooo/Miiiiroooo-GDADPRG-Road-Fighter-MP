#include "stdafx.h"
#include "BlackScreen.h"
#include "Game.h"
#include "SceneManager.h"
#include "ScreenTransitionBehavior.h"


// constructor and destructor of the BlackScreen Class
BlackScreen::BlackScreen(std::string name, std::string screenToTransition) : AGameObject(name)
{
	this->screenToTransition = screenToTransition;
}


BlackScreen::~BlackScreen()
{

}


// public methods of the BlackScreen Class
void BlackScreen::initialize()
{
	this->sprite = NULL;
	this->blackScreen = new sf::RectangleShape();
	this->blackScreen->setFillColor(sf::Color::Black);
	this->blackScreen->setSize(sf::Vector2f(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 2));
	this->setPosition(-Game::WINDOW_WIDTH, 0);

	// init components;
	Renderer* renderer = new Renderer("BlackScreen");
	this->attachComponent(renderer);
	renderer->attachOwner(this);
	renderer->assignDrawable(blackScreen);

	ScreenTransitionBehavior* logicComponent = new ScreenTransitionBehavior("Transition", screenToTransition);
	this->attachComponent(logicComponent);
}