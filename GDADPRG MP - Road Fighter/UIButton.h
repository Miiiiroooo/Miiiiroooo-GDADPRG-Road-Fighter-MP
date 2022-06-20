#pragma once

#include "AGameObject.h"
#include "ButtonListener.h"
#include "UIButtonInputController.h"

class UIButton : public AGameObject
{
// methods
public:
	UIButton(std::string name, sf::Texture* normalTexture, sf::Texture* pressedTexture);
	~UIButton();

	void initialize();
	void changeButtonToNormal();
	void changeButtonToPressed();
	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();
	void setButtonListener(ButtonListener* listener);


// attributes
private:
	sf::Texture* normalTexture;
	sf::Texture* pressedTexture;
	ButtonListener* listener;
};