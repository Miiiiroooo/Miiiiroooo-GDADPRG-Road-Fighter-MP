#include "stdafx.h"
#include "TitleScreen.h"
#include "Game.h"

TitleScreen::TitleScreen(string name) : AGameObject(name), ButtonListener()
{

}

TitleScreen::~TitleScreen()
{

}

void TitleScreen::initialize()
{
	std::cout << "Declared as " << this->name << endl;
	sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("GameLogo"));

	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	this->setPosition(Game::WINDOW_WIDTH / 2, (Game::WINDOW_HEIGHT / 2) - 100);
	//sprite->setScale((float)Game::WINDOW_WIDTH / textureSize.x, (float)Game::WINDOW_HEIGHT / textureSize.y);

	Renderer* render = new Renderer("TitleScreen");
	render->assignDrawable(sprite);
	this->attachComponent(render);

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("button_pressed");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("button_unpressed");

	
	UIButton* button1 = new UIButton("play_button", btnNormal, btnPressed);
	this->attachChild(button1);
	button1->setParent(this);
	button1->setButtonListener(this);
	button1->setPosition(0, 225);
	button1->getTransformable()->setScale(0.3f, 0.3f);

	UIText* button1_Text = new UIText("text_1");
	button1->attachChild(button1_Text);
	button1_Text->setParent(button1);
	button1_Text->setPosition(0, -40);
	button1_Text->setSize(100);
	button1_Text->setText("PLAY");

	UIButton* button2 = new UIButton("exit_button", btnNormal, btnPressed);
	this->attachChild(button2);
	button2->setParent(this);
	button2->setButtonListener(this);
	button2->setPosition(0, 300);
	button2->getTransformable()->setScale(0.3f, 0.3f);

	UIText* button2_Text = new UIText("text_1");
	button2->attachChild(button2_Text);
	button2_Text->setParent(button2);
	button2_Text->setPosition(0, -40);
	button2_Text->setSize(100);
	button2_Text->setText("EXIT");
	
}

void TitleScreen::onButtonClick(UIButton* button)
{
	cout << button->getName() << " pressed!" << endl;
}

void TitleScreen::onButtonReleased(UIButton* button)
{
	cout << button->getName() << " release!" << endl;
}
