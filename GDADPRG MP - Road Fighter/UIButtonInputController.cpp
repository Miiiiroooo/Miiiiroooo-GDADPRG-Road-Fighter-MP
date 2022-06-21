#include "stdafx.h"
#include "UIButtonInputController.h"


// constructor and destructor of the UIButtonInputController
UIButtonInputController::UIButtonInputController(std::string name, ButtonListener* listener) : GenericInputController(name)
{
	this->buttonListener = listener;
}


UIButtonInputController::~UIButtonInputController()
{
	AComponent::~AComponent();
}


// public methods of the UIButtonInputController
void UIButtonInputController::perform()
{
	UIButton* button = (UIButton*)this->getOwner();

	
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && this->pressed)
	{
		this->pressed = false;
		button->changeButtonToNormal();
		this->buttonListener->onButtonReleased(button);
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		// check if button is within mouse coords
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		sf::FloatRect bounds = button->getGlobalBounds();

		/*
		std::cout << "Mouse X: " << mousePos.x << "   Y: " << mousePos.y << std::endl;
		std::cout << "Bounds X: " << bounds.left << "   Y: " << bounds.top << std::endl;
		*/

		if (bounds.contains(mousePos))
		{
			this->pressed = true;
			button->changeButtonToPressed();
			this->buttonListener->onButtonClick(button);
		}
	}

	

}