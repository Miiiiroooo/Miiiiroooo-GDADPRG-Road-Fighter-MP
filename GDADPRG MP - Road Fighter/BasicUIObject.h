#pragma once

#include "AGameObject.h"

// UI Object only for displaying a sprite and does not require more components other than the Renderer component
class BasicUIObject : public AGameObject
{
public:
	BasicUIObject(std::string name, std::string textureKey, float scaleValue);
	~BasicUIObject();

	void initialize();


private:
	std::string textureKey;
	float scaleValue;
};

