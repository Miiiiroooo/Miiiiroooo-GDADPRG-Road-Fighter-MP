#pragma once

class ApplicationManager : public sf::NonCopyable
{
public:
	static ApplicationManager* getInstance();
	void initialize(sf::RenderWindow* targetWindow);
	void applicationQuit();
	void pauseApplication();
	void resumeApplication();
	bool isPaused();

private:
	ApplicationManager();


public:
	enum GameState { Running = 0, Paused = 1 };

private:
	static ApplicationManager* sharedInstance;
	sf::RenderWindow* window;
	GameState state;
};