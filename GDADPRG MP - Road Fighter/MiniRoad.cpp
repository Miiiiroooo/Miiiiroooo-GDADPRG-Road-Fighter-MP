#include "stdafx.h"
#include "MiniRoad.h"
#include "Game.h"


// constructor and destructor of the MiniRoad Class
MiniRoad::MiniRoad(std::string name) : AGameObject(name)
{

}


MiniRoad::~MiniRoad()
{

}


// public methods of the MiniRoad Class
void MiniRoad::initialize()
{
	this->sprite = new sf::Sprite();
	TextureManager::getInstance()->getTexture("MiniRoad")->setRepeated(true);
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("MiniRoad"));

	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x, Game::WINDOW_HEIGHT * 2));
	this->sprite->setScale(1.1f, 1.1f);
	

	// init components
	Renderer* renderer = new Renderer("MiniRoad");
	this->attachComponent(renderer);
	renderer->attachOwner(this);
	renderer->assignDrawable(sprite);
}