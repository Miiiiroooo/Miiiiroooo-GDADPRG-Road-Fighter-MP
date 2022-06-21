#include "stdafx.h"
#include "PlayerMovement.h"
#include "PlayerInput.h"
#include "Player.h"
#include "GameManager.h"
#include "GameObjectManager.h"

PlayerMovement::PlayerMovement(std::string name) : AComponent(name, AComponent::ComponentType::Script)
{
	gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
}


PlayerMovement::~PlayerMovement()
{

}


/* Public Methods of the PlayerMovement Component Class */
void PlayerMovement::perform()
{
	Player* player = (Player*)this->getOwner();
	PlayerInput* inputController = (PlayerInput*)player->getComponentsOfType(AComponent::ComponentType::Input)[0];
	sf::Transformable* playerTransformable = player->getTransformable();

	if (playerTransformable == NULL || inputController == NULL)
	{
		std::cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	if (gameManager->crashed())
	{
		return;
	}

	// movement
	sf::Vector2f offset(0.0f, 0.0f);
	if (inputController->isA() && !gameManager->checkGameOver())
	{
		offset.x -= this->SPEED_MULTIPLIER;
	}
		
	if (inputController->isD() && !gameManager->checkGameOver())
	{
		offset.x += this->SPEED_MULTIPLIER;
	}

	playerTransformable->move(offset * deltaTime.asSeconds());

}