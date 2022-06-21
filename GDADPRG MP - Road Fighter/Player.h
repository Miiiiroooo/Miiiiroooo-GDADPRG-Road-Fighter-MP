#pragma once
#include "AGameObject.h"
class Player : public AGameObject
{
public:
	Player(std::string name);
	void initialize();

	void setNormalTexture();
	void setCrashedTexture();

	

private:
	const float SPEED_MULTIPLIER = 100.0f;
	sf::Texture* normalTexture;
	sf::Texture* crashedTexture;
		
};

