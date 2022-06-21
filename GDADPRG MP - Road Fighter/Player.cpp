#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "PlayerInput.h"
#include "PlayerMovement.h"
#include<iostream>

using namespace std;

Player::Player(std::string name) : AGameObject(name)
{

}

void Player::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("player_car_0.png"));

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->sprite->setScale(0.5f, 0.5f);
	this->transformable.setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2 + 200);

	
	PlayerInput* playerInput = new PlayerInput("input_control");
	this->attachComponent(playerInput);

	
	PlayerMovement* playerMovement = new PlayerMovement("player_movement");
	this->attachComponent(playerMovement);
	
	Renderer* renderComponent = new Renderer("BGSprite");
	renderComponent->assignDrawable(sprite);
	this->attachComponent(renderComponent);
}
