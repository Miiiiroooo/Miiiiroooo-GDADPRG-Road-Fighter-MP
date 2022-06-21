#include "stdafx.h"
#include "PlayerInput.h"

PlayerInput::PlayerInput(std::string name) : GenericInputController(name)
{

}

PlayerInput::~PlayerInput()
{
	GenericInputController::~GenericInputController();
}

void PlayerInput::perform()
{
	bool keyFlag = false;
	if (event.type == sf::Event::KeyPressed)
		keyFlag = true;
	else if (event.type == sf::Event::KeyReleased)
		keyFlag = false;

	switch (event.key.code)
	{
	case sf::Keyboard::W:
		this->W = keyFlag;
		break;
	case sf::Keyboard::S:
		this->S = keyFlag;
		break;
	case sf::Keyboard::A:
		this->A = keyFlag;
		break;
	case sf::Keyboard::D:
		this->D = keyFlag;
		break;
	}
}

bool PlayerInput::isW()
{
	return W;
}

bool PlayerInput::isS()
{
	return S;
}

bool PlayerInput::isA()
{
	return A;
}

bool PlayerInput::isD()
{
	return D;
}


