#include "stdafx.h"
#include "GoalLineMovement.h"
#include "GameObjectManager.h"
#include "BasicUIObject.h"


// constructor and destructor of the GoalLineMovement Class
GoalLineMovement::GoalLineMovement(std::string name) : AComponent(name, Script)
{
	gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
}


GoalLineMovement::~GoalLineMovement()
{

}


// public methods fo the GoalLineMovement Class
void GoalLineMovement::perform()
{
	BasicUIObject* goalLine = (BasicUIObject*)this->getOwner();
	
	if (!gameManager->crashed())
	{
		float speed = std::pow(gameManager->getSpeed(), 1.2);
		goalLine->getTransformable()->move(0, speed * deltaTime.asSeconds());
	}
}