#include "stdafx.h"
#include "BasicUIObject.h"


// constructor and destructor of the BasicUIObject Class
BasicUIObject::BasicUIObject(std::string name, std::string textureKey, float scaleValue) : AGameObject(name)
{
	this->textureKey = textureKey;
	this->scaleValue = scaleValue;
}


BasicUIObject::~BasicUIObject()
{

}


// public methods of the BasicUIObject Class
void BasicUIObject::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture(textureKey));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->sprite->setScale(scaleValue, scaleValue);

	// init components
	Renderer* renderer = new Renderer(this->name);
	this->attachComponent(renderer);
	renderer->attachOwner(this);
	renderer->assignDrawable(this->sprite);
}