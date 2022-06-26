#pragma once

class ScoreManager : sf::NonCopyable
{
// methods
public:
	static ScoreManager* getInstance();

	void initialize();
	
	int getScore();
	int getHighScore();

	void updateScore(int score);
	void decideHighScore(); 

	void updateFile();

private:
	ScoreManager() {};


// attributes
private:
	static ScoreManager* sharedInstance;

	int score = 0;
	int highScore = 0;
};

