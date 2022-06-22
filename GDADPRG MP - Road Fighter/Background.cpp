#include "stdafx.h"
#include "Background.h"
#include "Game.h"
#include "PlayerInput.h"
#include "BackgroundScroll.h"

#include <iostream>
using namespace std;

Background::Background(std::string name) : AGameObject(name)
{

}

Background::~Background()
{
	AGameObject::~AGameObject();
}

void Background::initialize()
{
	//std::cout << "Declared as " << this->name << endl;
	
	//sprite->setTexture(*TextureManager::getInstance()->getTexture("background"));
	

	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x , Game::WINDOW_HEIGHT * 8));
	sprite->setScale(4.f, 4.f);
	sprite->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

	
	BackgroundScroll* backgroundScroll = new BackgroundScroll("MovementComponent_1");
	this->attachComponent(backgroundScroll);
	

	Renderer* render = new Renderer("BG");
	render->assignDrawable(sprite);
	this->attachComponent(render);
}

void Background::setTexture(sf::Texture* texture)
{
	sprite = new sf::Sprite();
	texture->setRepeated(true);
	sprite->setTexture(*texture);
}
