#pragma once

#include "AGameObject.h"

class AScene 
{
// methods of the AScene class
public:
	AScene(std::string sceneName);
	~AScene();

	virtual void onLoadResources() = 0;
	virtual void onLoadObjects() = 0;
	virtual void onUnloadResources() = 0;
	virtual void onUnloadObjects();

	std::string getSceneName();

protected:
	void registerObject(AGameObject* object);


// attributes of the AScene Class
protected:
	std::string sceneName;
};

