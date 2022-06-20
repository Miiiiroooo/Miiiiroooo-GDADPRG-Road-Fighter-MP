#pragma once

#include "AGameObject.h"

class EmptyGameObject : public AGameObject
{
public:
	EmptyGameObject(std::string name);
	~EmptyGameObject();
	void initialize();
};