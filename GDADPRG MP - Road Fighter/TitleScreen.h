#pragma once
#include "AGameObject.h"
#include "ButtonListener.h"
#include "UIButton.h"
#include "UIText.h"
#include "stdafx.h"

using namespace std;

class TitleScreen : public AGameObject, public ButtonListener
{
public:
	TitleScreen(string name);
	~TitleScreen();

	void initialize();

	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
	
private:
	AGameObject* levelSelect = NULL;
};

