#pragma once

#include "AGameObject.h"
#include "GameManager.h"
#include "BasicUIObject.h"
#include "UIText.h"

class UIGameManager : public AGameObject
{
// methods
public:
	UIGameManager(std::string name);
	~UIGameManager();

	void initialize();
	void update(sf::Time deltaTime);

	int getDigits(int num);

	void updateMiniPlayer();
	void updateScore();
	void updateSpeed();
	void updateFuel();

// attributes
private:
	GameManager* gameManager;
	BasicUIObject* miniPlayer = NULL;
	UIText* scoreText = NULL;
	UIText* speedText = NULL;
	UIText* fuelText = NULL;
};

