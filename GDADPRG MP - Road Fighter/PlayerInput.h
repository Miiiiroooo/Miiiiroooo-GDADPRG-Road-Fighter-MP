#pragma once
#include "GenericInputController.h"
class PlayerInput : public GenericInputController
{
public:
	PlayerInput(std::string name);
	~PlayerInput();

	void perform();
	
	bool isW();
	bool isS();
	bool isA();
	bool isD();

private:
	bool W = false;
	bool S = false;
	bool D = false;
	bool A = false;
	
};

