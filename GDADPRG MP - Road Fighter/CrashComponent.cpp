#include "stdafx.h"
#include "CrashComponent.h"
#include "Player.h"
#include "GameManager.h"

CrashComponent::CrashComponent(string name) : AComponent(name, Script)
{
	gameManager = (GameManager*)GameObjectManager::getInstance()->findObjectByName("GameManager");
}

CrashComponent::~CrashComponent()
{

}

void CrashComponent::perform()
{
	Player* player = (Player*)this->getOwner();

	if (player->getTransformable()->getPosition().x > 790 || player->getTransformable()->getPosition().x < 500 || player->hasCarCrashed())
	{
		//crash
		ticks += deltaTime.asSeconds();
		gameManager->setCrashState(true);
		player->setCrashedTexture();

		if (ticks > 2.f)
		{
			ticks = 0.f;
			gameManager->resetPlayer();

			player->onCollisionExit(NULL);
		}
	}
}