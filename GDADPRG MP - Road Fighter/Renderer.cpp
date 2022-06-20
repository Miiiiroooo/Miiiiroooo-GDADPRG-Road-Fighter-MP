#include "stdafx.h"
#include "Renderer.h"


// constructor and destructor of the Renderer Class
Renderer::Renderer(std::string name) : AComponent(name, AComponent::ComponentType::Renderer)
{
	this->targetWindow = NULL;
	this->drawable = NULL;
	this->renderStates = sf::RenderStates::Default;
}


Renderer::~Renderer()
{
	delete this->drawable;
	AComponent::~AComponent();
}


// public methods of the Renderer Class
void Renderer::assignTargetWindow(sf::RenderWindow* window)
{
	this->targetWindow = window;
}


void Renderer::assignDrawable(sf::Drawable* drawable)
{
	this->drawable = drawable;
}


void Renderer::setRenderStates(sf::RenderStates renderStates)
{
	this->renderStates = renderStates;
}


void Renderer::perform()
{
	this->targetWindow->draw(*this->drawable, this->renderStates);
}