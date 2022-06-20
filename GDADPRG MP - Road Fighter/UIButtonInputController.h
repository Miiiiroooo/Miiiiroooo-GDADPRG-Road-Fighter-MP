#pragma once

#include "GenericInputController.h"
#include "ButtonListener.h"
#include "UIButton.h"

class UIButtonInputController : public GenericInputController
{
// methods
public:
	UIButtonInputController(std::string name, ButtonListener* listener);
	~UIButtonInputController();

	void perform();


// attributes
private:
	ButtonListener* buttonListener;
	bool pressed = false;
};