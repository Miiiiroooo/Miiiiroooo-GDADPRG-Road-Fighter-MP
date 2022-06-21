#pragma once

#include "AGameObject.h"

class GameScreen : public AGameObject
{
public:
	GameScreen(std::string name);
	~GameScreen();

	void initialize();
	void onGameOver();
	void onTrasition();


private:
	bool isGameOver = false;
};

