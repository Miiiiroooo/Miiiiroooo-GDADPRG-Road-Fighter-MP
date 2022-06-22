#pragma once
#include "AGameObject.h"
#include "GameManager.h"

class Background : public AGameObject
{
public:
	Background(std::string name);
	~Background();

	void initialize();
	void setTexture(sf::Texture* texture);


private:
	

};

