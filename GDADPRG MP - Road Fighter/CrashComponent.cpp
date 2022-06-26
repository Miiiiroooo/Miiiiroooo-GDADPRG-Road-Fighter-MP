#include "stdafx.h"
#include "CrashComponent.h"
#include "Player.h"
#include "GameManager.h"
#include "PhysicsManager.h"

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

	//cout << player->getTransformable()->getPosition().x << endl;

	if (player->getTransformable()->getPosition().x > rightEdge || player->getTransformable()->getPosition().x < leftEdge || gameManager->crashed())
	{
		//crash
		ticks += deltaTime.asSeconds();
		gameManager->setCrashState(true);
		player->setCrashedTexture();

		//collider
		if (!hasUntracked)
		{
			Collider* collider = (Collider*)player->findComponentByName("PlayerCollider");
			PhysicsManager::getInstance()->untrackObject(collider);
			hasUntracked = true;
		}

		// death duration
		if (ticks > 2.f)
		{
			ticks = 0.f;
			hasUntracked = false;

			gameManager->resetPlayer();
			player->onCollisionExit(NULL);
			gameManager->setCrashState(false);
		}
	}
}

void CrashComponent::setRoadEdges(int left, int right)
{
	this->leftEdge = left;
	this->rightEdge = right;
}
