#include "stdafx.h"
#include "UIText.h"


// constructor and destructor of the UIText Class
UIText::UIText(std::string name) : AGameObject(name)
{
	this->text = new sf::Text();
}


UIText::~UIText()
{
	AGameObject::~AGameObject();
}


// public methods of the UIText Class
void UIText::initialize()
{
	sf::Font* font = FontManager::getInstance()->getFont("default");
	text->setFont(*font);
	text->setFillColor(sf::Color::White);
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(4.0f);
	this->setSize(40);
	this->setText("<Using placeholder!>");

	Renderer* renderer = new Renderer("Button");
	renderer->assignDrawable(text);
	this->attachComponent(renderer);
}


void UIText::setText(std::string text)
{
	this->text->setString(text);
	sf::FloatRect bounds = this->text->getLocalBounds();

	// Align center, you can put other alignments here
	this->text->setOrigin(bounds.width / 2, bounds.height / 2);
}


std::string UIText::getText()
{
	return this->text->getString();
}


void UIText::setSize(unsigned int size)
{
	this->text->setCharacterSize(size);
}