#include "stdafx.h"
#include "LoadingScreen.h"
#include "UIText.h"
#include "Game.h"
#include "FadingTextBehavior.h"


// constructor and destructor of the LoadingScreen Class
LoadingScreen::LoadingScreen(std::string name) : AGameObject(name)
{
	this->blackBox = NULL;
}


LoadingScreen::~LoadingScreen()
{
	this->blackBox = NULL;
}


// public methods of the LoadingScreen Class
void LoadingScreen::initialize()
{
	this->sprite = NULL;
	this->blackBox = new sf::RectangleShape();
	this->blackBox->setFillColor(sf::Color::Black);
	this->blackBox->setSize(sf::Vector2f((float)Game::WINDOW_WIDTH, (float)Game::WINDOW_HEIGHT));
	sf::Vector2f boxSize = this->blackBox->getSize();
	this->blackBox->setOrigin(boxSize.x / 2, boxSize.y / 2);
	

	// init components and child objects
	Renderer* renderer = new Renderer("LoadingScreen");
	renderer->assignDrawable(blackBox);
	this->attachComponent(renderer);
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);


	UIText* loadingText = new  UIText("LoadingText");
	this->attachChild(loadingText);
	loadingText->setParent(this);
	loadingText->setSize(100);
	loadingText->setText("loading");
	loadingText->setPosition(0, -50);

	FadingTextBehavior* logicComponent = new FadingTextBehavior("FadingComponent");
	loadingText->attachComponent(logicComponent);
}