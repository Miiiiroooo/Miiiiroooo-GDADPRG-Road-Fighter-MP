#pragma once

#include "AComponent.h"

class GenericInputController : public AComponent
{
// methods
public:
	GenericInputController(std::string name);
	~GenericInputController();

	void perform();
	void assignEvent(sf::Event event);


// attributes
protected:
	sf::Event event;
};

