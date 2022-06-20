#include "stdafx.h"
#include "ApplicationManager.h"


// static declarations of the ApplicationManager Class
ApplicationManager* ApplicationManager::sharedInstance = NULL;

ApplicationManager* ApplicationManager::getInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new ApplicationManager();

	return sharedInstance;
}


// constructor of the ApplicationManager Class
ApplicationManager::ApplicationManager()
{
	this->state = GameState::Running;
}


// public methods of the ApplicationManager Class
void ApplicationManager::initialize(sf::RenderWindow* targetWindow)
{
	this->window = targetWindow;
}


void ApplicationManager::applicationQuit()
{
	this->window->close();
}


void ApplicationManager::pauseApplication()
{
	this->state = GameState::Paused;
}


void ApplicationManager::resumeApplication()
{
	this->state = GameState::Running;
}


bool ApplicationManager::isPaused()
{
	return this->state == GameState::Paused;
}