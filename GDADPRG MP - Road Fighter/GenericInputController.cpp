#include "stdafx.h"
#include "GenericInputController.h"


// constructor and destructor of the GenericInputController Class
GenericInputController::GenericInputController(std::string name) : AComponent(name, AComponent::ComponentType::Input)
{
	this->type = AComponent::ComponentType::Input;
}


GenericInputController::~GenericInputController()
{
	AComponent::~AComponent();
}


// public methods of the GenericInputController Class
void GenericInputController::perform()
{

}


void GenericInputController::assignEvent(sf::Event event)
{
	this->event = event;
}