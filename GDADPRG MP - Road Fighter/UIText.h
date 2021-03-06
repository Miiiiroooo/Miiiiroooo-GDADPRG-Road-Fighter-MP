#pragma once

#include "AGameObject.h"
#include "FontManager.h"

class UIText : public AGameObject
{
// methods
public:
	UIText(std::string name);
	~UIText();

	void initialize();
	void setText(std::string text);
	sf::Text* getText();
	std::string getString();
	void setSize(unsigned int size);


// attributes
private:
	sf::Text* text;
};