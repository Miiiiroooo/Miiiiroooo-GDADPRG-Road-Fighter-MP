#pragma once

#include "AComponent.h"

class FadingTextBehavior : public AComponent
{
public:
	FadingTextBehavior(std::string name);
	~FadingTextBehavior();

	void perform();


private:
	sf::Time elapsed;
	int decrement;
	int reduction;
	bool isFadingOut;
};

