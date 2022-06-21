#include "stdafx.h"
#include "FadingTextBehavior.h"
#include "UIText.h"


// constructor and desctructor of the FadingTextBehavior Class
FadingTextBehavior::FadingTextBehavior(std::string name) : AComponent(name, Script)
{
	this->elapsed = sf::seconds(0.0f);
	this->decrement = 5;
	this->reduction = 10;
	this->isFadingOut = true;
}


FadingTextBehavior::~FadingTextBehavior()
{

}


// public methods of the FadingTextBehavior Class
void FadingTextBehavior::perform()
{
	// set-up reference to the text along with the opacity of the text
	UIText* owner = (UIText*)this->getOwner();
	sf::Text* parentText = owner->getText();
	sf::Color opacity(255, 255, 255, 255 - reduction);


	this->elapsed += this->deltaTime;
	if (this->elapsed > sf::seconds(0.10f))
	{
		parentText->setFillColor(opacity);

		this->reduction += this->decrement; // decrement the reduction value to simulate the "bouncing" effect
		if (this->reduction > 255)
			this->reduction = 255;
		else if (this->reduction < 0)
			this->reduction = 0;

		this->decrement += 3;  // increase decrement value also to help simulate the "bouncing" effect
		this->elapsed = sf::seconds(0.0f);  
	}
	

	if (this->reduction == 0 && !this->isFadingOut) // when text is fully visible, make the text fade out
	{
		this->decrement *= -1;
		this->isFadingOut = true;
	}
	else if (this->reduction == 255 && this->isFadingOut) // when text is fully invisible, make text fade in
	{
		this->decrement *= -1;
		this->isFadingOut = false;
	}
}