#include "stdafx.h"
#include "ScreenTransitionBehavior.h"
#include "SceneManager.h"


// constructor and destructor of the ScreenTransitionBehavior Class
ScreenTransitionBehavior::ScreenTransitionBehavior(std::string name, std::string screenToTransition) : AComponent(name, Script)
{
	this->screenToTransition = screenToTransition;
}


ScreenTransitionBehavior::~ScreenTransitionBehavior()
{

}


// public methods of the ScreenTransitionBehavior Class
void ScreenTransitionBehavior::perform()
{
	// move the black screen from the left to the right, covering the entire screen

	this->blackScreen = (BlackScreen*)this->getOwner();

	if (blackScreen->getTransformable()->getPosition().x < -0)
	{
		float displacement = SPEED_MULTIPLIER * deltaTime.asSeconds();

		blackScreen->getTransformable()->move(sf::Vector2f(displacement, 0));
	}
	else
	{
		blackScreen->getTransformable()->setPosition(0, 0);
		SceneManager::getInstance()->loadScene(screenToTransition);
	}
}