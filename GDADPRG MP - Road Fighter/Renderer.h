#pragma once

#include "AComponent.h"

class Renderer : public AComponent
{
// methods
public:
	Renderer(std::string name);
	~Renderer();

	void assignTargetWindow(sf::RenderWindow* window);
	void assignDrawable(sf::Drawable* drawable);
	void setRenderStates(sf::RenderStates renderStates);

	void perform();


// attributes
private:
	sf::RenderWindow* targetWindow;
	sf::Drawable* drawable;
	sf::RenderStates renderStates;
};

