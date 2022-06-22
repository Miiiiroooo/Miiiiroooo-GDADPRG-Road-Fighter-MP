#pragma once
#include "AComponent.h"
#include "stdafx.h"
#include "Player.h"
#include "PlayerInput.h"
#include "SFXManager.h"
#include "GameObjectManager.h"



class PlayerSoundHandler : public AComponent
{
public:
	PlayerSoundHandler(std::string name);
	~PlayerSoundHandler();

	void perform();

	void EnableSound(bool value);

private:
	bool firstTime = true;
	bool soundEnabled = true;
	
	float pitchAdd = 0;

	sf::Sound* engineSound = new sf::Sound();
	sf::Sound* crashSound = new sf::Sound();

};

